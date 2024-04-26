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
  m_plot = new QCustomPlot;
  m_plot->addGraph();
  m_plot->setWindowModality(Qt::ApplicationModal);
  m_plot->setMinimumSize(600,600);
  m_plot->yAxis->setLabel("mW/(m2/nm)");
  m_plot->xAxis->setLabel("Wavelenght (nm)");
  setWindowTitle(QString("WinLibRadTran %1").arg(VER_PRODUCTVERSION_STR));
  ui->label_out_path->setText(QDir::currentPath() + "/libradtran/_out");
  m_last_choosed_path = "";

  connect(ui->action_LibRadTran, &QAction::triggered, []() {
    show_pdf_doc("libRadtran.pdf");
  });
  connect(ui->action_choose_inp_file, &QAction::triggered, [this]() {
    m_last_choosed_path = QFileDialog::getOpenFileName(this, tr("Open Libradtran file"),
                                                     m_last_choosed_path,
                                                     tr("Libradtran files (*.inp)"));
    ui->textBrowser_input_file->setToolTip(m_last_choosed_path);
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
  QFile file(m_last_choosed_path);
  if (!file.open(QIODevice::ReadOnly)) {
    uts::showWarnigMessage("Файл не найден.");
    return;
  };
  QFile::remove(QDir::currentPath() + lrt::kLibradtran_input_path);
  QFile::copy(m_last_choosed_path, QDir::currentPath() + lrt::kLibradtran_input_path);
  ui->textBrowser_input_file->clear();
  QTextStream ts(&file);
  ui->textBrowser_input_file->setText(ts.readAll());
  file.close();
  lrt::run_libradtran();
  lrt::getResult(ui->action_is_format->isChecked(),m_waves,m_values);
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


  qDebug()<<"remove: "<<QFile::remove(m_last_choosed_path);
  QFile file(m_last_choosed_path);
  qDebug() << m_last_choosed_path;
  if (file.open(QIODevice::ReadWrite)) {
    file.write("");
    file.write(ui->textBrowser_input_file->toPlainText().toLatin1());
    file.close();
  };
  run_last_choosed_libradtran_input();
}

void LibradtranUi::on_pushButton_show_plot_clicked()
{
    m_plot->xAxis->setRange(m_waves.first(),m_waves.last());
    double max = *std::max_element(m_values.begin(),m_values.end());
    qDebug()<<"max: --> "<<max;
    m_plot->yAxis->setRange(0,max+max*0.1);
    m_plot->graph(0)->setData(m_waves,m_values);
    m_plot->replot();
    m_plot->show();

}
