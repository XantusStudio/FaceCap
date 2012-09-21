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

//rozdzialka
int maxX;
int maxY;

//tryb pracy programu
int tryb;
//status servera
int serverStatus;
//status klienta
int clientStatus;

//nosek
int punktZero;

//tmp markery
vec2_t t_marker[MAX_MARKERS];
//zakres filtra HSV
int h1,s1,v1,h2,s2,v2;
//jitter removal
int jitter;
//rozmiary markera
int mminx,mminy,mmaxx,mmaxy;
//rozmycie
int fcBlur;
//erozja
int fcErode;
//kolejnosc filtra
int fcOrder;
//inerpolacja
int interpolacja;
//kontury
int levels;


//byt markera
fc_entity_t fc_entity[MAX_MARKERS];

//socket klienta majki
int client_fd;
