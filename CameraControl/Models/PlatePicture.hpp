/**
 * @file PlatePicture.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include <ctime>
#include <uuid/uuid.h>

using namespace std;

/**
 * @brief Area Picture model class
 * 
 */
class PlatePicture{
    string pictureId;
    time_t timeStamp;
    string picture;
    
    public: 
        #pragma region Constructors
        /**
         * @brief Construct a new Area Picture object
         * 
         */
        PlatePicture();

        /**
         * @brief Construct a new Area Picture object
         * 
         * @param pictureId 
         * @param timeStamp 
         * @param picture 
         */
        PlatePicture(string pictureId, time_t timeStamp, string picture);
        #pragma endregion

        #pragma region Public Getters
        /**
         * @brief Get the Picture Id object
         * 
         * @return string 
         */
        string getPictureId();

        /**
         * @brief Get the Picture object
         * 
         * @return string 
         */
        string getPicture();

        /**
         * @brief Get the Time Stamp object
         * 
         * @return time_t 
         */
        time_t getTimeStamp();
        #pragma endregion

        #pragma region Public Setters
        /**
         * @brief Set the Picture object
         * 
         * @param picture 
         */
        void setPicture(string picture);
        #pragma endregion
    
    private:
        #pragma region Private Setters
        /**
         * @brief Set the Time Stamp object
         * 
         * @param timeStamp 
         */
        void setTimeStamp(time_t timeStamp);

        /**
         * @brief Set the Picture Id object
         * 
         * @param pictureId 
         */
        void setPictureId(string pictureId);
        #pragma endregion

        #pragma region Private Helper Methods
        /**
         * @brief Convert uuid to string
         * 
         * @param id 
         * @return string 
         */
        string convertToString(uuid_t id);
        #pragma endregion
};