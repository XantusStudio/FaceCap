#include <stdio.h>
#include "cv.h"
#include "highgui.h"

CvCapture* capture; //kamerka
IplImage* frame; //ramka z kamerki
IplImage* imgYellowThresh; //wyciete z hsv
IplImage* imgHSV; // hsv 
IplImage* imgThreshed; //rozmyte i wyciete z hsv

CvMemStorage* storage; // kontener dla info o konturach
CvSeq* contours; // 1-szy stopien konturowania
CvSeq* contours2; // 2-gi stopien konturowania


//pkt myszki
CvPoint pt;
//fonty
CvFont font;
CvFont font1;


//konwersja do HSV , rozmycie 
IplImage* GetThresholdedImage(IplImage* img);
// oblsuga myszki
void onMouse( int event, int x, int y, int flags, void* param );
//ladnie ramke wez
void fc_GetFrame(void);
//init tez zrob ladnie
int fc_InitOpenCV(void);
//pisanie po ekranie
void fc_PutText (IplImage *image,int x, int y,char *text,int size,int r,int g,int b);
//update displa
void fc_UpdateDisplay(void);
// ladny hud
void fc_MakeHUD(void);
