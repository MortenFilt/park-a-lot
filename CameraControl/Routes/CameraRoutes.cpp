#include "./CameraRoutes.hpp"

using namespace Rest;

CameraRouteManager::CameraRouteManager(Address addr):  Http::Endpoint(addr), httpEndpoint(std::make_shared<Http::Endpoint>(addr))
{
    Routes::Get(CameraRouteManager::cameraRouter, "/areaPicture/:cameraId", Routes::bind(&CameraController::getAreaPicture));
    Routes::Post(CameraRouteManager::cameraRouter, "/platePicture", Routes::bind(&CameraController::postPlatePicture));
}

void CameraRouteManager::init(size_t threads, size_t maxPayload)
{
    auto opts = Http::Endpoint::options()
                    .threads(threads)
                    .maxRequestSize(maxPayload);
    httpEndpoint->init(opts);
}

void CameraRouteManager::start()
{
    httpEndpoint->setHandler(cameraRouter.handler());
    httpEndpoint->serve();
}