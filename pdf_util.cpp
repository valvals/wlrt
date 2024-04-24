#include "pdf_util.h"
#include <QProcess>
#include <QDir>



void show_pdf_doc(const QString& docName) {
  QProcess process;
  QString sumatra = QDir::currentPath() + "/SumatraPDF.exe";
  QStringList args;
  args.append(QDir::currentPath() + "/" + docName);
  process.startDetached(sumatra, args);
}
