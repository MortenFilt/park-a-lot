#include "./CameraController.hpp"
#include "./../Services/CameraService.hpp"
#include "./../Log/log.hpp"

using namespace Pistache;

void CameraController::getPlatePicture(const Rest::Request& request, Http::ResponseWriter response)
{
    MyLog myLog;
    CameraService camService;
    string cameraId = request.param(":cameraId").as<string>();
    // string cameraId = "1";
    json platePicture = camService.getPlatePicture(cameraId);
    auto jsonObjects = json::array();

    jsonObjects.push_back(platePicture);
    response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
    response.send(Http::Code::Ok, jsonObjects.dump());
    myLog.log("Nummerplade billede sendt til billedeprocesserings servicen");
}

void CameraController::postPlatePicture(const Rest::Request& request, Http::ResponseWriter response)
{
    MyLog myLog;
    string body = request.body();
    json bodyAsJson = json::parse(body);
    string picture = bodyAsJson["picture"];
    std::cout << "Picture info is: " << picture << std::endl;
    response.send(Http::Code::Created);
    myLog.log("Nummerplade billede er taget");
}