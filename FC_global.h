#include <stdio.h>
#include <string.h>
#include "FC_math.h"
#include "FC_marker.h"
#include "FC_opencv.h"
#define MAX_MARKERS 20


enum fc_tryb {
    FC_INIT,
    FC_PREV,
    FC_FILTR,
    FC_TRACK,
    FC_MARK,
    FC_MOCAP,
    FC_MAX
};

enum fc_mayaServ {
    FCM_STOP,
    FCM_INIT,
    FCM_ACTIVE,
    FCM_MAX
};

//cam resolution
int maxX;
int maxY;

//current mode
int tryb;
//server status
int serverStatus;
//client status
int clientStatus;

//p0 (nose point :)
int punktZero;

//tmp markers
vec2_t t_marker[MAX_MARKERS];
//HSV filters
int h1,s1,v1,h2,s2,v2;
//jitter removal
int jitter;
//markers size
int mminx,mminy,mmaxx,mmaxy;
//blur
int fcBlur;
//erode
int fcErode;
//filter order
int fcOrder;
//inerpolation
int interpolacja;
//contours
int levels;


//marker entity
fc_entity_t fc_entity[MAX_MARKERS];

//socket for Maya client
int client_fd;
