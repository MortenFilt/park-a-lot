#include "./CameraController.hpp"
#include "./../Services/CameraService.hpp"
#include "./../Log/log.hpp"

using namespace Pistache;

void CameraController::getAreaPicture(const Rest::Request& request, Http::ResponseWriter response)
{
    MyLog myLog;
    CameraService camService;
    string cameraId = request.param(":cameraId").as<string>();
    json platePicture = camService.getAreaPicture(cameraId);
    auto jsonObjects = json::array();

    jsonObjects.push_back(platePicture);
    response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
    response.send(Http::Code::Ok, jsonObjects.dump());
}

void CameraController::postPlatePicture(const Rest::Request& request, Http::ResponseWriter response)
{
    MyLog myLog;
    string body = request.body();
    std::cout << "Body: " << body << std::endl;
    json bodyAsJson = json::parse(body);
    string picture = bodyAsJson["picture"];
    response.send(Http::Code::Created);
    myLog.log("Nummerplade billede er taget");

    CURLcode ret;
    CURL *handler;
    struct curl_slist *slist1;

    slist1 = NULL;
    slist1 = curl_slist_append(slist1, "Content-Type: application/json");

    handler = curl_easy_init();
    curl_easy_setopt(handler, CURLOPT_URL, "http:/192.168.87.149:5000/licenseplate");
    curl_easy_setopt(handler, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(handler, CURLOPT_POSTFIELDS, body);
    curl_easy_setopt(handler, CURLOPT_USERAGENT, "curl/7.38.0");
    curl_easy_setopt(handler, CURLOPT_HTTPHEADER, slist1);
    curl_easy_setopt(handler, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(handler, CURLOPT_TCP_KEEPALIVE, 1L);

    ret = curl_easy_perform(handler);
    std::cout << "Post request sent to 192.168.87.149" << std::endl;

    curl_easy_cleanup(handler);
    handler = NULL;
    curl_slist_free_all(slist1);
    slist1 = NULL;

    myLog.log("Nummerplade billede sendt til billedeprocesserings servicen");
}