/**
 * @file PlatePicture.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "./PlatePicture.hpp"

#pragma region Constructors
    /**
     * @brief Construct a new Area Picture object
     * 
     */
    PlatePicture::PlatePicture()
    {
        uuid_t id;
        uuid_generate(id);
        this-> pictureId = PlatePicture::convertToString(id);
        this-> timeStamp = time(0);
        this-> picture = "No Picture";
    };

    /**
     * @brief Construct a new Area Picture object
     * 
     * @param pictureId 
     * @param timeStamp 
     * @param picture 
     */
    PlatePicture::PlatePicture(string pictureId, time_t timeStamp, string picture)
    {
        this-> pictureId = pictureId;
        this-> timeStamp = timeStamp;
        this-> picture = picture;
    }
#pragma endregion

#pragma region Getters
    /**
     * @brief Get the Picture Id object
     * 
     * @return string 
     */
    string PlatePicture::getPictureId()
    {
        return this-> pictureId;
    }

    /**
     * @brief Get the Picture object
     * 
     * @return string 
     */
    string PlatePicture::getPicture()
    {
        return this-> picture;
    }

    /**
     * @brief Get the Time Stamp object
     * 
     * @return time_t 
     */
    time_t PlatePicture::getTimeStamp(){

        return this-> timeStamp;
    }
#pragma endregion

#pragma region Public Setters
    /**
     * @brief Set the Picture object
     * 
     * @param picture 
     */
    void PlatePicture::setPicture(string picture)
    {
        this->picture = picture;
    }
#pragma endregion
         
#pragma region Private Setters
    /**
     * @brief Set the Time Stamp object
     * 
     * @param timeStamp 
     */
    void PlatePicture::setTimeStamp(time_t timeStamp)
    {
        this-> timeStamp = timeStamp;
    }

    /**
     * 
     * @brief Set the Picture Id object
     * 
     * @param pictureId 
     */
    void PlatePicture::setPictureId(string pictureId)
    {
        this-> pictureId = pictureId;
    }
#pragma endregion

#pragma region Private Helper Methods
    /**
     * @brief Convert uuid to string
     * 
     * @param id 
     * @return string 
     */
    string PlatePicture::convertToString(uuid_t id)
    {
        size_t len = 16;
        return string(reinterpret_cast<char const*>(id), len);
    }
#pragma endregion

