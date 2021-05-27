/**
 * @file CameraController.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <pistache/router.h>
#include <pistache/http.h>
#include <curl/curl.h>

using namespace Pistache;

class CameraController {
    public:
        /**
         * @brief Get the Plate Picture object
         * 
         * @param request 
         * @param response Json {"picture", "pictureId", "timeStamp"} 
         */
        static void getAreaPicture(const Rest::Request& request, Http::ResponseWriter response);

        /**
         * @brief Send the Plate Picture object to get stored temporarily
         * 
         * @param request 
         * @param rresponse 
         */
        static void postPlatePicture(const Rest::Request& request, Http::ResponseWriter rresponse);
};