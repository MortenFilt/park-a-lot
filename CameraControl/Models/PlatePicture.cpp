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
#include "./../ExternalLibraries/base64.h"

#pragma region Constructors
    PlatePicture::PlatePicture()
    {
        // uuid_t id;
        // uuid_generate(id);
        // this-> pictureId = PlatePicture::convertToString(id);
        this-> pictureId = "VeryUniqueId";
        this-> timeStamp = time(0);
        this-> picture = "";
    };

    PlatePicture::PlatePicture(string picture)
    {
        uuid_t id;
        uuid_generate(id);
        this-> pictureId = PlatePicture::convertToString(id);
        // this-> pictureId = "VeryUniqueId";
        this-> timeStamp = time(0);
        this-> picture = base64_encode(picture);
    }
#pragma endregion

#pragma region Getters
    string PlatePicture::getPictureId()
    {
        return this-> pictureId;
    }

    string PlatePicture::getPicture()
    {
        return this-> picture;
    }

    time_t PlatePicture::getTimeStamp(){

        return this-> timeStamp;
    }
#pragma endregion

#pragma region Public Setters
    void PlatePicture::setPicture(string picture)
    {
        string base64EncodedPicture = base64_encode(picture);
        this->picture = base64EncodedPicture;
    }
#pragma endregion
         
#pragma region Private Setters
    void PlatePicture::setTimeStamp(time_t timeStamp)
    {
        this-> timeStamp = timeStamp;
    }

    void PlatePicture::setPictureId(string pictureId)
    {
        this-> pictureId = pictureId;
    }
#pragma endregion

#pragma region Private Helper Methods
    string PlatePicture::convertToString(uuid_t id)
    {
        size_t len = 16;
        return string(reinterpret_cast<char const*>(id), len);
    }

    json PlatePicture::jsonSerialize()
    {
        json platePicture = {
            {"pictureId", this-> pictureId},
            {"picture", this->picture},
            {"timeStamp", this-> timeStamp}
        };

        return platePicture;
    }
#pragma endregion

