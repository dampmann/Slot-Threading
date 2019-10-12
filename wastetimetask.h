#ifndef WASTETIMETASK_H
#define WASTETIMETASK_H

#include <QRunnable>
#include <QObject>

class WasteTimeTask : public QRunnable
{
public:
    explicit WasteTimeTask(
        QObject *receiver_,
        int n_,
        volatile bool *stopped_,
        unsigned long seconds_,
        int times_) : receiver(receiver_), n(n_), stopped(stopped_), seconds(seconds_), times(times_) {}

private:
    QObject *receiver;
    int n;
    volatile bool *stopped;
    unsigned long seconds;
    int times;
    void run();
};

#endif // WASTETIMETASK_H
