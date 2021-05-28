/**
 * @file CameraService.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "./../Models/PlatePicture.hpp"
#include <raspicam/raspicam.h>
#include <fstream>
#include <iostream>
#include <limits>

class CameraService {
    public:
        #pragma region Constructors
        /**
         * @brief Construct a new Camera Service object
         * 
         */
        CameraService();
        #pragma endregion

        /**
         * @brief Get a plate picture from the camera with the given id
         * 
         * @param cameraId 
         * @return json 
         * "pictureId"
         * "picture"
         * "timeStamp"
         */
        json getAreaPicture(string cameraId);

};