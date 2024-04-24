#ifndef MESSAGE_REPORTER_H
#define MESSAGE_REPORTER_H

class QString;

namespace uts {

void showWarnigMessage(const QString& message);
void showErrorMessage(const QString& message);
void showInfoMessage(const QString& message);

} // end namespace uts

#endif // MESSAGE_REPORTER_H
