#include "./CameraRoutes.hpp"

using namespace Rest;

CameraRouteManager::CameraRouteManager(Address addr):  Http::Endpoint(addr)
{
    Routes::Get(CameraRouteManager::cameraRouter, "/platePicture", Routes::bind(&CameraController::getPlatePicture));
    setHandler(cameraRouter.handler());
}