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

class CameraController {
    public:
        /**
         * @brief Get the Plate Picture object
         * 
         * @param request 
         * @param response Json {"picture", "pictureId", "timeStamp"} 
         */
        static void getPlatePicture(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
};