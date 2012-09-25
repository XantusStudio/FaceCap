/* 

	= FaceCap v1.3.4 - Realtime Face Mocap Server for Maya = 
	2012 Xantus S.A.
	Check README.md for details.

*/

#include <unistd.h>
#include "FC_global.h"

void main(int argc, char **argv) {
    int loopHack; // main window update

    tryb = FC_INIT;
    loopHack=0;

    if (argc==3) {
	printf("Setting %s x %s \n",argv[1],argv[2]);
    	maxX=atoi(argv[1]);
	maxY=atoi(argv[2]);
    }


    fc_InitMarkers();
    if(fc_InitOpenCV()<0) exit;
    fc_InitMayaServer(argv[0]);

//main loop
    tryb = FC_PREV;

    while(1) {
	if(tryb==FC_INIT) {
	    fc_InitMarkers();
	    fc_ClearMouse();
	    if(client_fd>0) {
		fc_StopMayaServer();
		serverStatus=FCM_STOP;
	    }
	    tryb = FC_PREV;
	}

	fc_GetFrame();
	if(tryb > FC_FILTR) {
	    fc_ClearMarkerStatus();
	    fc_TrackMarkers();
	    fc_CalcFixedPos();
	}

	fc_MakeHUD();
	fc_UpdateDisplay();

	if(tryb == FC_MOCAP && serverStatus == FCM_INIT) {
	    if(loopHack > 10) {
		fc_StartMayaServer();
		loopHack=0;
	    }else loopHack++;
	} else if (serverStatus == FCM_ACTIVE) {
		clientStatus = fc_Klient(client_fd);
		if(clientStatus < 0) serverStatus=FCM_STOP;
	} else if (serverStatus == FCM_STOP && client_fd > 0) {
		fc_StopMayaServer();
	}

	char c = (char)cvWaitKey(2);
	switch(c) {
	    case 'n':
		if(tryb < FC_MOCAP)
		if (tryb!=FC_TRACK)tryb++;
	    break;
	    case 'c':
		tryb=FC_INIT;
	    break;
	    case 's':
		if(serverStatus==FCM_STOP)
		    serverStatus=FCM_INIT;
		else serverStatus=FCM_STOP;
	    break;
	    default:
	    ;
	}
    }
}


