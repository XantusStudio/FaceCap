#include <stdio.h>
#include "cv.h"
#include "highgui.h"

CvCapture* capture; //camera
IplImage* frame; //camera frame
IplImage* imgYellowThresh; //hsv
IplImage* imgHSV; // hsv 
IplImage* imgThreshed; //hsv

CvMemStorage* storage; // contour container
CvSeq* contours; // 1st contour grade
CvSeq* contours2; // 2nd contour grade


//mouse pt
CvPoint pt;
//fonts
CvFont font;
CvFont font1;


//convert to HSV, blur
IplImage* GetThresholdedImage(IplImage* img);
// mouse 
void onMouse( int event, int x, int y, int flags, void* param );
//get frame
void fc_GetFrame(void);
//init 
int fc_InitOpenCV(void);
//text
void fc_PutText (IplImage *image,int x, int y,char *text,int size,int r,int g,int b);
//update display
void fc_UpdateDisplay(void);
// hud
void fc_MakeHUD(void);
