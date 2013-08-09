// minimal_oculus_app.cpp
// https://developer.oculusvr.com/wiki/index.php?title=Minimal_Oculus_Application&status=1

#include <iostream>
#ifdef _WIN32
#  include <conio.h>
#endif
#include "OVR.h"

using namespace std;
using namespace OVR;

Ptr<DeviceManager>	pManager;
Ptr<HMDDevice>		pHMD;
Ptr<SensorDevice>	pSensor;
SensorFusion		FusionResult;
HMDInfo			Info;
bool			InfoLoaded;


void Init()
{
    System::Init();

    pManager = *DeviceManager::Create();

    pHMD = *pManager->EnumerateDevices<HMDDevice>().CreateDevice();

    if (pHMD)
    {
        InfoLoaded = pHMD->GetDeviceInfo(&Info);

        pSensor = *pHMD->GetSensor();
    }
    else
    {
        pSensor = *pManager->EnumerateDevices<SensorDevice>().CreateDevice();
    }

    if (pSensor)
    {
        FusionResult.AttachToSensor(pSensor);
    }
}

void Clear()
{
    pSensor.Clear();
    pHMD.Clear();
    pManager.Clear();

    System::Destroy();
}

void Output()
{
    cout << "----- Oculus Console -----" << endl;

    if (pHMD)
    {
        cout << " [x] HMD Found" << endl;
    }
    else
    {
        cout << " [ ] HMD Not Found" << endl;
    }

    if (pSensor)
    {
        cout << " [x] Sensor Found" << endl;
    }
    else
    {
        cout << " [ ] Sensor Not Found" << endl;
    }

    cout << "--------------------------" << endl;

    if (InfoLoaded)
    {
        cout << " DisplayDeviceName: " << Info.DisplayDeviceName << endl;
        cout << " ProductName: " << Info.ProductName << endl;
        cout << " Manufacturer: " << Info.Manufacturer << endl;
        cout << " Version: " << Info.Version << endl;
        cout << " HResolution: " << Info.HResolution<< endl;
        cout << " VResolution: " << Info.VResolution<< endl;
        cout << " HScreenSize: " << Info.HScreenSize<< endl;
        cout << " VScreenSize: " << Info.VScreenSize<< endl;
        cout << " VScreenCenter: " << Info.VScreenCenter<< endl;
        cout << " EyeToScreenDistance: " << Info.EyeToScreenDistance << endl;
        cout << " LensSeparationDistance: " << Info.LensSeparationDistance << endl;
        cout << " InterpupillaryDistance: " << Info.InterpupillaryDistance << endl;
        cout << " DistortionK[0]: " << Info.DistortionK[0] << endl;
        cout << " DistortionK[1]: " << Info.DistortionK[1] << endl;
        cout << " DistortionK[2]: " << Info.DistortionK[2] << endl;
        cout << "--------------------------" << endl;
    }

    cout << endl << " Press ENTER to continue" << endl;

    cin.get();

    while(pSensor)
    {
        Quatf quaternion = FusionResult.GetOrientation();

        float yaw, pitch, roll;
        quaternion.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);

        cout << " Yaw: " << RadToDegree(yaw) << 
            ", Pitch: " << RadToDegree(pitch) << 
            ", Roll: " << RadToDegree(roll) << endl;

#ifdef _WIN32
        Sleep(50);
        if (_kbhit()) exit(0);
#endif
    }
}

int main()
{
    Init();
    Output();
    Clear();
}
