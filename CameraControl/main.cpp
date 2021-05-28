#include "./Services/CameraService.hpp"
#include "./Routes/CameraRoutes.hpp"
#include "./Log/log.hpp"

int main() {
    std::cout << "Server is starting up" << std::endl;

    Address addr(Ipv4::any(), 9000);
    CameraRouteManager routeManager(addr);

    routeManager.init(2, 65536);
    routeManager.start();
}