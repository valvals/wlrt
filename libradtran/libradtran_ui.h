#ifndef LIBRADTRAN_UI_H
#define LIBRADTRAN_UI_H

#include <QMainWindow>

namespace Ui {
class LibradtranUi;
}

class LibradtranUi : public QMainWindow {
  Q_OBJECT

 public:
  explicit LibradtranUi(QWidget* parent = nullptr);
  ~LibradtranUi();

 private slots:
  void on_pushButton_openFolder_clicked();

  void on_pushButton_save_and_rerun_libradtran_clicked();

 private:
  Ui::LibradtranUi* ui;
  QString last_choosed_path;
  QString getOutFileName();
  void run_last_choosed_libradtran_input();
};

#endif // LIBRADTRAN_UI_H
