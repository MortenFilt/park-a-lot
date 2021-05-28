#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class MyLog {
    std::string fileName;
    
    public:
        /**
         * @brief Log the given message in the objects related log file. 
         * 
         * Timestamp and log type is added automatically.
         * Log format: yyyy/mm/dd/hh:mm:ss [LOG] Given message here
         */
        void log(std::string logMessage);

        #pragma region Constructors
        /**
         * @brief Construct a new Log object in the current directory with the name log.txt
         * 
         */
        MyLog();

        /**
         * @brief Construct a new Log object in the current directory with the given log name
         * 
         * @param fileName 
         */
        MyLog(std::string fileName);

        #pragma endregion

        #pragma region Setters
        /**
         * @brief Set the File Name object
         * 
         * @param newFileName 
         */
        void setFileName(std::string newFileName);
        #pragma endregion

        #pragma region Getters
        /**
         * @brief Set the File Name object
         * 
         * @return string 
         */
        std::string getFileName();
        #pragma endregion
};