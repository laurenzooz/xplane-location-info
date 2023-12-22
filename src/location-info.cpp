#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"

#include <iostream>
#include <string.h>

#if IBM
	#include <windows.h>
#endif
#if LIN
	#include <GL/gl.h>
#elif __GNUC__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#ifndef XPLM400
	#error This is made to be compiled against the XPLM400 SDK
#endif


// coordinate dataref handles
XPLMDataRef lat_handle = XPLMFindDataRef("sim/flightmodel/position/latitude");
XPLMDataRef lon_handle = XPLMFindDataRef("sim/flightmodel/position/longitude");

static float floop_cb(float time_since_last_call, float time_since_last_floop, int floop_counter, void* inRefcon) // vehicles
{	
	
	double lat = XPLMGetDataf(lat_handle);
	double lon = XPLMGetDataf(lon_handle);

	XPLMDebugString("Current coordinates are: ");
	XPLMDebugString(std::to_string(lat).c_str());
	XPLMDebugString(", ");
	XPLMDebugString(std::to_string(lon).c_str());
	XPLMDebugString("\n");

	return 10;
}




PLUGIN_API int XPluginStart(
							char *		outName,
							char *		outSig,
							char *		outDesc)
{
	strcpy(outName, "LocationInfoPlugin");
	strcpy(outSig, "laurenzo.LocationInfoPlugin");
	strcpy(outDesc, "A plug-in that shows info of the location you are flying in");

	XPLMDebugString("Starting Location Info plugin\n");

	XPLMRegisterFlightLoopCallback(floop_cb, 10, NULL); // flight loop every 10 seconds
	
}

PLUGIN_API void	XPluginStop(void)
{
}

PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void)  { return 10; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void * inParam) { }