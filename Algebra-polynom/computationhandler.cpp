#include "computationhandler.hpp"
#include <QtConcurrent>
#include <QObject>
#include <exception>

ComputationHandler::ComputationHandler()
{}

ComputationHandler::~ComputationHandler()
{
    delete workerThread;
}

void ComputationHandler::run(std::function<QVector<QString>()> computation,
         std::function<void(const QVector<QString>&)> onResultReady,
         std::function<void()> onFinished)
{
    if (workerThread)
        throw std::runtime_error("Worker thread already running");

    workerThread = new WorkerThread(computation);
    this->onResultReadyCallback = onResultReady;
    this->onFinishedCallback = onFinished;

    connect(workerThread, &WorkerThread::resultReady, this, &ComputationHandler::handleResult);
    connect(workerThread, &WorkerThread::finished, this, &ComputationHandler::onThreadFinished);

    workerThread->start();
}

void ComputationHandler::handleResult(QVector<QString> result)
{
    onResultReadyCallback(result);
}

void ComputationHandler::onThreadFinished()
{
    delete workerThread;
    workerThread = nullptr;
    onFinishedCallback();
}

void WorkerThread::run()
{
    QVector<QString> result = computation();
    emit resultReady(result);
}
