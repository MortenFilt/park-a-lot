/**
 * @file CameraService.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "./CameraService.hpp"
#pragma region Constructors
    CameraService::CameraService(){};
#pragma endregion

#pragma region Get services
    json CameraService::getPlatePicture(string cameraId)
    {
        // Find Camera with given ID
        // Get camera to take a picture
        // Put picture data into model
        // Serialize model
        // Return data
        ifstream binaryInFileHandler;

        binaryInFileHandler.open("./../../picture2.ppm", ios::in | ios::binary);
        if(!binaryInFileHandler)
        {
            std::cout << "Picture did not open" << std::endl;
            return {};
        }

        binaryInFileHandler.ignore(std::numeric_limits<std::streamsize>::max());
        std::streamsize len = binaryInFileHandler.gcount();
        binaryInFileHandler.clear();
        binaryInFileHandler.seekg(0, std::ios_base::beg);

        char *data = new char[len];
        binaryInFileHandler.read(data, len);
        binaryInFileHandler.close();

        if(!binaryInFileHandler.good())
        {
            std::cout << "Error reading the picture" << std::endl;
            return {};
        }

        PlatePicture picture;
        string pictureAsString = string(reinterpret_cast<char const*>(data), len);
        picture.setPicture(pictureAsString);
        
        return picture.jsonSerialize();
    }
#pragma endregion