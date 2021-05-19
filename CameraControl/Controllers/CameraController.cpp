#include "./CameraController.hpp"
#include "./../Services/CameraService.hpp"

using namespace Pistache;

void CameraController::getPlatePicture(const Rest::Request& request, Http::ResponseWriter response)
{
    CameraService camService;
    // string cameraId = request.param(":cameraId").as<string>();
    string cameraId = "1";
    json platePicture = camService.getPlatePicture(cameraId);
    auto jsonObjects = json::array();

    jsonObjects.push_back(platePicture);
    response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
    response.send(Http::Code::Ok, jsonObjects.dump());
}