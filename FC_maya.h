#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <getopt.h>
#include <unistd.h>
#include <maya/mocapserver.h>
#include <maya/mocapserial.h>
#include "FC_global.h"
#define closesocket close

//taken from Maya SDK
static char program[80];
static char *server_name = program;
static CapChannel px[MAX_MARKERS],py[MAX_MARKERS];
static void get_data(void);
static int create_channels(void);

struct timeval base_timeout, timeout; //timeout for socket (0)
//channels info
static int channels_created = 0;

//init server name 
void fc_InitMayaServer(char *nazwa);
void fc_StartMayaServer(void);
//do client
int fc_Klient(void);
