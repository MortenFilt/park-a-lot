#include "./Services/CameraService.hpp"
#include "./Routes/CameraRoutes.hpp"
#include "./Log/log.hpp"

int main() {
    MyLog myLog("platelog.txt");

    myLog.log("This is a test");
    myLog.log("This is test number 2");
    myLog.log("This is test number 3");
    std::cout << "Server is starting up" << std::endl;

    Address addr(Ipv4::any(), 9000);
    CameraRouteManager routeManager(addr);

    routeManager.init(2, 65536);
    routeManager.start();
}