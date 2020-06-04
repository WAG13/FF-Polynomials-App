#ifndef COMPUTATIONHANDLER_HPP
#define COMPUTATIONHANDLER_HPP

#include <functional>
#include <QString>
#include <QFutureWatcher>
#include <QThread>
#include <QVector>


class WorkerThread : public QThread
{
    Q_OBJECT

public:

    WorkerThread(std::function<QVector<QString>()> computation, QThread* parent = nullptr)
        : QThread(parent), computation(computation)
    {}

    void run() override;

signals:
    void resultReady(QVector<QString> result);
private:
    std::function<QVector<QString>()> computation;
};



class ComputationHandler : public QObject
{
    Q_OBJECT

public:
    ComputationHandler();
    ~ComputationHandler();

    void run(std::function<QVector<QString>()> computation,
             std::function<void(const QVector<QString>&)> onResultReady,
             std::function<void()> onFinished);
    //void terminate();

private:
    WorkerThread* workerThread = nullptr;
    std::function<void(const QVector<QString>&)> onResultReadyCallback;
    std::function<void()> onFinishedCallback;

private slots:
    void onThreadFinished();
    void handleResult(QVector<QString> result);
};

#endif // COMPUTATIONHANDLER_HPP
