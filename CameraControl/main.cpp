#include "./Services/CameraService.hpp"
#include "./Routes/CameraRoutes.hpp"

int main() {
    std::cout << "PLATE PICTURE TEST" << std::endl;
    PlatePicture pictureObject;

    std::cout << pictureObject.getPicture() << std::endl;
    std::cout << pictureObject.getPictureId() << std::endl;
    std::cout << pictureObject.getTimeStamp() << std::endl;

    pictureObject.setPicture("This is now a picture");
    std::cout << pictureObject.getPicture() << std::endl << std::endl;

    std::cout << "CAMERA SERVICE TEST" << std::endl;
    CameraService serviceObject;

    json jsonPlatePicture = serviceObject.getPlatePicture("1");

    std::cout << "Json? " << typeid(jsonPlatePicture).name() << std::endl;
    std::cout << "This is the end" << std::endl;

    CameraRouteManager app({Ipv4::any(), 9000});
    app.serve();
}