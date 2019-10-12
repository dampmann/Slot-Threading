#include "wastetimetask.h"
#include <QThread>
#include <QMetaObject>

void WasteTimeTask::run() {
        for(int i = 0; i < times; ++i) {
        if(*stopped) return;
        QThread::currentThread()->sleep(seconds);
        if(*stopped) return;
          QString message = QObject::tr("Thread %1 -> iteration %2\n").arg(n).arg(i);
          QMetaObject::invokeMethod(
                      receiver,
                      "updateProgress",
                      Qt::QueuedConnection,
                      Q_ARG(QString, message)
          );
    }
}
