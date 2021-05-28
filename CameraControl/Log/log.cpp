#include "./log.hpp"

void MyLog::log(std::string logMessage)
{
    std::time_t now = time(0);
    std::tm *localNow = localtime(&now);
    int monthNum = 1 + localNow->tm_mon;
    int dayNum = localNow->tm_mday - 1;
    int hourNum = 9 + localNow->tm_hour;
    int minNum = localNow->tm_min;
    int secNum = localNow->tm_sec;


    std::string year = std::to_string(1900 + localNow->tm_year);
    std::string month = std::to_string(1 + localNow->tm_mon);
    std::string day = std::to_string(localNow->tm_mday - 1);
    std::string hour = std::to_string(9 + localNow->tm_hour);
    std::string min = std::to_string(localNow->tm_min);
    std::string sec = std::to_string(localNow->tm_sec);

    if(monthNum < 10){
        month = "0" + month;
    }

    if(dayNum < 10){
        day = "0" + day;
    }

    if(hourNum < 10){
        hour = "0" + hour;
    }

    if(minNum < 10){
        min = "0" + min;
    }

    if(secNum < 10){
        sec = "0" + sec;
    }


    std::string timeStamp = year + "/" + month + "/" + day + "/" + hour + ":" + min + ":" + sec;

    std::string logType = "[LOG]";
    std::string logEntry = timeStamp + " " + logType + " " + logMessage;

    std::ofstream logFile;
    logFile.open(fileName, std::ios::app);
    logFile << logEntry + "\r\n";
    logFile.close();
}

MyLog::MyLog()
{
    setFileName("log.txt");
}

MyLog::MyLog(std::string fileName)
{
    setFileName(fileName);
}

void MyLog::setFileName(std::string newFileName)
{
    this->fileName = newFileName;
}

std::string MyLog::getFileName()
{
    return this->fileName;
}