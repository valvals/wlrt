#include "libradtran_ui.h"
#include "ui_libradtran_ui.h"
#include "qfiledialog.h"
#include "libradtran/libradtran_wrapper.h"
#include "pdf_util.h"
#include <QFile>
#include <QDebug>
#include <QProcess>
#include <QDateTime>
#include "message_reporter.h"
#include "version.h"

LibradtranUi::LibradtranUi(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::LibradtranUi) {
  ui->setupUi(this);
  setWindowTitle(QString("WinLibRadTran %1").arg(VER_PRODUCTVERSION_STR));
  ui->label_out_path->setText(QDir::currentPath() + "/libradtran/_out");
  last_choosed_path = "";

  connect(ui->action_LibRadTran, &QAction::triggered, []() {
    show_pdf_doc("libRadtran.pdf");
  });
  connect(ui->action_choose_inp_file, &QAction::triggered, [this]() {
    last_choosed_path = QFileDialog::getOpenFileName(this, tr("Open Libradtran file"),
                                                     last_choosed_path,
                                                     tr("Libradtran files (*.inp)"));

    run_last_choosed_libradtran_input();
  });
  connect(ui->action_result_path, &QAction::triggered, [this]() {
    auto new_path = QFileDialog::getExistingDirectory();
    if (new_path != "")
      ui->label_out_path->setText(new_path);

  });
  connect(ui->action_open_result_dir, &QAction::triggered, [this]() {
    on_pushButton_openFolder_clicked();
  });
}

LibradtranUi::~LibradtranUi() {
  delete ui;
}

QString LibradtranUi::getOutFileName() {
  QString path = ui->label_out_path->text();
  path.append("/%1%2");
  if (ui->lineEdit_file_name->text() == "") {
    return path.arg(QDateTime::currentDateTime().toString("yyyy_MM_dd_hhmmss"), ".txt");
  }
  return path.arg(QString(ui->lineEdit_file_name->text()), "");
}

void LibradtranUi::run_last_choosed_libradtran_input() {
  QFile file(last_choosed_path);
  if (!file.open(QIODevice::ReadOnly)) {
    uts::showWarnigMessage("Файл не найден.");
    return;
  };
  QFile::remove(QDir::currentPath() + lrt::kLibradtran_input_path);
  QFile::copy(last_choosed_path, QDir::currentPath() + lrt::kLibradtran_input_path);
  ui->textBrowser_input_file->clear();
  QTextStream ts(&file);
  ui->textBrowser_input_file->setText(ts.readAll());
  file.close();
  lrt::run_libradtran();
  if (ui->action_is_format->isChecked()) {
    lrt::formatResult();
  }
  QFile::copy("libradtran/_out/libradtran.txt", getOutFileName());
  ui->textBrowser_output_messages->setText(lrt::getLastErrorsMessages());
}



void LibradtranUi::on_pushButton_openFolder_clicked() {
  QString openExplorer = "c:/windows/explorer.exe /n,";
  QString path;
  path = QDir::toNativeSeparators(ui->label_out_path->text());
  openExplorer.append(path);
  QProcess::startDetached(openExplorer);
}


void LibradtranUi::on_pushButton_save_and_rerun_libradtran_clicked() {


  QFile file(last_choosed_path);
  qDebug() << last_choosed_path;
  if (file.open(QIODevice::ReadWrite)) {
    QFile::remove(last_choosed_path);
    file.write(ui->textBrowser_input_file->toPlainText().toLatin1());
    file.close();
  };
  run_last_choosed_libradtran_input();
}
