#ifndef LOGGER_H
#define LOGGER_H

#include <QTextStream>
#include <QString>
const int INFO = -1;
const int DEBUG = 0;
const int WARNING = 1;
const int ERROR = 2;

class Logger
{
    QTextStream* outLog;
public:
    Logger();

    void printLog(int level, QString message);

    void printLog(int level, int value);

    void printLog(int level, QChar letter);

    ~Logger() {
        delete outLog;
    }
};

#endif // LOGGER_H