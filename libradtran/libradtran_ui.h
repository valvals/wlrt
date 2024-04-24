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

 private:
  Ui::LibradtranUi* ui;
  QString getOutFileName();
};

#endif // LIBRADTRAN_UI_H
