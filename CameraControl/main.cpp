#include "./Models/PlatePicture.hpp"
#include <iostream>

int main() {
    PlatePicture pictureObject;

    std::cout << pictureObject.getPicture() << std::endl;
    std::cout << pictureObject.getPictureId() << std::endl;
    std::cout << pictureObject.getTimeStamp() << std::endl;

    pictureObject.setPicture("This is now a picture");
    std::cout << pictureObject.getPicture() << std::endl;

    return 0;
}