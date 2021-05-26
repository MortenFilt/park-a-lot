#include <pistache/endpoint.h>
#include "./../Controllers/CameraController.hpp"

using namespace Pistache;

class CameraRouteManager: public Http::Endpoint {
    Rest::Router cameraRouter;
    std::shared_ptr<Http::Endpoint> httpEndpoint;
    
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

        /**
         * @brief Initializes server with routing for the camera optional number of threads
         * 
         * @param threads 
         */
        void init(size_t threads = 2, size_t maxPayload = 8192);

        /**
         * @brief Starts the server
         * 
         */
        void start();
};
