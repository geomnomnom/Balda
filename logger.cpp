#include "logger.h"

Logger::Logger()
{
    file = new QFile("log.txt");
    if (file->open(QIODevice::Append | QIODevice::Text)) {
        outLog = new QTextStream(file);
    }
}

void Logger::printLog(int level, QString message) {
    if (level == DEBUG) {
        (*outLog) << "[DEBUG] ";
    }
    if (level == ERROR) {
        (*outLog) << "[ERROR] ";
    }
    if (level == WARNING) {
        (*outLog) << "[WARNING] ";
    }
    if (level == INFO) {
        (*outLog) << "[INFO] ";
    }

    (*outLog) << message << "\n";
    (*outLog).flush();
}

void Logger::printLog(int level, int value) {
    if (level == DEBUG) {
        (*outLog) << "[DEBUG] ";
    }
    if (level == ERROR) {
        (*outLog) << "[ERROR] ";
    }
    if (level == WARNING) {
        (*outLog) << "[WARNING] ";
    }
    if (level == INFO) {
        (*outLog) << "[INFO] ";
    }
    (*outLog) << value << "\n";
    (*outLog).flush();
}

void Logger::printLog(int level, QChar letter) {
    if (level == DEBUG) {
        (*outLog) << "[DEBUG] ";
    }
    if (level == ERROR) {
        (*outLog) << "[ERROR] ";
    }
    if (level == WARNING) {
        (*outLog) << "[WARNING] ";
    }
    if (level == INFO) {
        (*outLog) << "[INFO] ";
    }
    (*outLog) << letter << " ";
    (*outLog).flush();
}
