// w sumie rip kodu z SDK majki
#include "FC_maya.h"

//taki pseudo init
void fc_InitMayaServer(char *nazwa) {
    char *cptr;
    cptr = strrchr(nazwa, '/');
    if (cptr) strcpy(program, (cptr + 1));
    else strcpy(program, nazwa);
    serverStatus=FCM_STOP;
}

//pozniej zrobie to na forku 
void fc_StartMayaServer(void) {
    client_fd = CapServe(server_name);
    if(client_fd>0) serverStatus=FCM_ACTIVE;
    base_timeout.tv_sec  = 0;
    base_timeout.tv_usec = 0;
}
//samo sie wyjasnia o co kaman
void fc_StopMayaServer(void) {
    closesocket(client_fd);
    client_fd = -1;
}
//obsluga klienta
int fc_Klient(void) {
    CapCommand cmd;
    char ruser[64], rhost[64], realhost[64];
    fd_set rd_fds;
    int status;
    
    FD_ZERO(&rd_fds);
    FD_SET((unsigned int)client_fd, &rd_fds);
    timeout.tv_sec  = base_timeout.tv_sec;
    timeout.tv_usec = base_timeout.tv_usec;
    status = select(FD_SETSIZE, &rd_fds, NULL, NULL, &timeout);
    if(status==0) return 1; //poprostu timeout
    else if(status>0){

    cmd = CapGetCommand(client_fd);
      switch (cmd)
      {
        case CAP_CMD_QUIT:
    	    return -1;
        case CAP_CMD_AUTHORIZE:
            status = CapGetAuthInfo(client_fd, ruser, rhost, realhost);
            if (status < 0) return -1;
            status = CapAuthorize(client_fd, 1);
            break;
        case CAP_CMD_INIT:
            status = CapInitialize(client_fd, program);
            break;
        case CAP_CMD_VERSION:
            status = CapVersion(client_fd, program, "1.3.4","Xantus FaceCap server");
            break;
        //odpytka o kanalki
	case CAP_CMD_INFO:
            if (!channels_created) {
        	status = create_channels();
        	if (status < 0) break;
        	channels_created = 1;
            }
            status = CapInfo(client_fd, 0.0, 0.0, 0.0, 512 * 1024, 1);
            break;
	case CAP_CMD_DATA:
            get_data();
            status = CapData(client_fd);
            break;
        default:
            break;
	}
    }
    return status;

}

//wysyla dane
static void get_data(void) {
    int i;
    for (i=0;i<MAX_MARKERS;i++) {
	if(fc_entity[i].curPos[0]!=0 && fc_entity[i].curPos[1]!=0) {
	    CapSetData(px[i],&fc_entity[i].fixedPos[0]);
	    CapSetData(py[i],&fc_entity[i].fixedPos[1]);
	}
    }
    return;
}


//tworzy kanaly tylko dla aktywnych markerow
static int create_channels(void) {
    int i;
    char opis[50];
    for (i=0;i<MAX_MARKERS;i++) {
	if(fc_entity[i].curPos[0]!=0 && fc_entity[i].curPos[1]!=0) {
	    sprintf(opis,"%s_x",fc_entity[i].name);
	    px[i] = CapCreateChannel(opis,   CAP_USAGE_XPOS, 1);
	    sprintf(opis,"%s_y",fc_entity[i].name);
	    py[i] = CapCreateChannel(opis,   CAP_USAGE_YPOS, 1);
	}
    }
  return 0;
}


