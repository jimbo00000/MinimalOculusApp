// minimal_oculus_app.cpp
// https://developer.oculusvr.com/wiki/index.php?title=Minimal_Oculus_Application&status=1

#include <iostream>
#include <iomanip>
#ifdef _WIN32
#  include <conio.h>
#  include <windows.h>
#endif

#include "OVR_CAPI.h"
#include "../Src/Kernel/OVR_Math.h" ///@todo Expose GetEulerAngles function from CAPI

using namespace OVR;

void main()
{
    ovr_Initialize();

    ovrHmd     hmd = ovrHmd_Create(0);
    ovrHmdDesc hmdDesc;
    if (hmd)
    {
        ovrHmd_GetDesc(hmd, &hmdDesc);
    }

    ovrHmd_StartSensor(hmd,
        ovrHmdCap_Orientation |
        ovrHmdCap_YawCorrection,
        ovrHmdCap_Orientation);

    while(1)
    {
        ovrSensorState ss = ovrHmd_GetSensorState(hmd, 0.0);

        if (ss.StatusFlags & (ovrStatus_OrientationTracked))
        {
            //ovrPosef pose = ss.Predicted.Pose; ///<@todo This seems to yield noisy results
            ovrPosef pose = ss.Recorded.Pose;

#if 1
            std::cout
                << "X: " << pose.Orientation.x
                << ", Y: " << pose.Orientation.y
                << ", Z: " << pose.Orientation.z
                << ", W: " << pose.Orientation.w << std::endl;
#else
            // Use the C++ API's Quat functions to get Euler angles
            ovrQuatf o = pose.Orientation;
            OVR::Quatf qf(o.x, o.y, o.z, o.w);

            float yaw, pitch, roll;
            qf.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);

            std::cout
                << std::setprecision(2)
                << " Yaw " << RadToDegree(yaw)
                << ",  Pitch " << RadToDegree(pitch)
                << ",  Roll " << RadToDegree(roll) << std::endl;
#endif
        }

#ifdef _WIN32
        // Exit on input from keyboard
        Sleep(50);
        if (_kbhit()) exit(0);
#endif
    }

    ovr_Shutdown();
}
