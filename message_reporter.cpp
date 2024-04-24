#include "message_reporter.h"
#include "QMessageBox"
#include <stddef.h>

namespace {
void showMessage(const QString& message, QMessageBox::Icon icon) {
  QMessageBox mb;
  //mb.setWindowTitle("");
  mb.setInformativeText(message);
  mb.setIcon(icon);
  mb.exec();
};
}

namespace uts {

void showWarnigMessage(const QString& message) {
  showMessage(message, QMessageBox::Warning);
};
void showErrorMessage(const QString& message) {
  showMessage(message, QMessageBox::Critical);
}
void showInfoMessage(const QString& message) {
  showMessage(message, QMessageBox::Information);
}

} // end namespace uts
