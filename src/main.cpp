#include <iostream>
#include "config.h"
#include "Application.h"
#include "Network.h"
using namespace std;

#ifdef _MSC_VER
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "enet.lib")
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "BulletCollision.lib")
#pragma comment(lib, "BulletDynamics.lib")
#pragma comment(lib, "BulletSoftBody.lib")
#pragma comment(lib, "LinearMath.lib")
#endif

int main(int argc, char** argv){

    Application a;
    a.run();

	return 0;
}
