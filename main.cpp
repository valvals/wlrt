#include "libradtran/libradtran_ui.h"

#include <QApplication>
#include "qrc_files_restorer.h"

int main(int argc, char* argv[]) {
  QrcFilesRestorer::restoreFilesFromQrc(":/pdf_viewer");
  QApplication a(argc, argv);
  LibradtranUi w;
  w.show();
  return a.exec();
}
