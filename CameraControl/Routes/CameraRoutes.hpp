#include <pistache/endpoint.h>
#include "./../Controllers/CameraController.hpp"

using namespace Pistache;

class CameraRouteManager: public Http::Endpoint {
    Rest::Router cameraRouter;
    public:
        /**
         * @brief Construct a new Camera Route Manager object
         * 
         * @param addr 
         */
        CameraRouteManager(Address addr);

        /**
         * @brief Get the Plate Picture object
         * 
         * @param request 
         * @param response Json {"picture", "pictureId", "timeStamp"} 
         */
        void getPlatePicture(const Rest::Request& request, Http::ResponseWriter response);
};
