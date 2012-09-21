#include "FC_global.h"

//konwertuje obraz do HSV i robi mocne rozmycie
IplImage* GetThresholdedImage(IplImage* img) {
	cvCvtColor(img, imgHSV, CV_BGR2HSV);
        cvInRangeS(imgHSV, cvScalar(s1, v1, h1,1), cvScalar(s2, v2, h2,1), imgThreshed);
//1.2.0
	if(fcBlur<1) fcBlur=1;
	if(fcBlur % 2 != 1) fcBlur++;
	if(fcOrder)cvSmooth(imgThreshed,imgThreshed,CV_GAUSSIAN, fcBlur,fcBlur ,0,0);
	cvErode(imgThreshed,imgThreshed,NULL,fcErode);
	if(!fcOrder)cvSmooth(imgThreshed,imgThreshed,CV_GAUSSIAN, fcBlur,fcBlur ,0,0);
	if(tryb>FC_PREV) {
    		cvInRangeS(imgThreshed, cvScalar(255, 255,255,1), cvScalar(255, 255, 255,1), imgThreshed);
		return imgThreshed;
	} else { return imgHSV;}
}

void fc_ClearMouse(void){
    pt.x=-1;
    pt.y=-1;
}

//myszka
void onMouse( int event, int x, int y, int flags, void* param )
{
    if( event == CV_EVENT_LBUTTONDOWN )
    {
        pt.x = x;
        pt.y = y;
    }
}

//trackuj markery
void fc_TrackMarkers(void) {
    vec2_t v1,v2;
    char boxsize[20];
    int ile = 0;
    int i,j;
    int isFound;
    CvRect rect;
    CvPoint pt1;
    //
    storage = cvCreateMemStorage(0);

    //szuka konturow na wyfiltrowanym obrazie
    cvFindContours( imgYellowThresh, storage, &contours, sizeof(CvContour),CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
    //upraszcza kontury

    if(contours!=0)
	contours2 = cvApproxPoly(contours, sizeof(CvContour),storage,CV_POLY_APPROX_DP,levels,1);
    if(contours2!=0 && levels>0)
    cvDrawContours( frame, contours2, CV_RGB(255,0,0), CV_RGB(0,255,0), levels,3, CV_AA, cvPoint(1,1) );

    //robi "bound rect" wokolo konturow
    if(contours!=0) {
	for( ; contours2!= 0;  contours2 =  contours2->h_next ) {
	    rect = cvBoundingRect(contours2, 0);
	    pt1.x = rect.x + (rect.width/2);
	    pt1.y = rect.y + (rect.height/2);
	    //jesli box > min marker size (5) tzn ze marker
	    if(rect.width > mminx && rect.height > mminy && rect.width  <mmaxx && rect.height < mmaxy )  {
		t_marker[ile][0]=pt1.x;
		t_marker[ile][1]=pt1.y;
		//krzyzyki dla FC_TRACK
		if(tryb!=FC_MOCAP) {
		    cvLine(frame, cvPoint(pt1.x-3, pt1.y), cvPoint(pt1.x+3,pt1.y), cvScalar(0,255,255,1), 5,8,0);
        	    cvLine(frame, cvPoint(pt1.x, pt1.y-3), cvPoint(pt1.x, pt1.y+3), cvScalar(0,255,255,1), 5,8,0);
		    cvRectangle(frame, cvPoint(rect.x,rect.y),cvPoint(rect.x+rect.width,rect.y+rect.height), cvScalar(0,255,255,1), 1, 8, 0);
		    sprintf(boxsize,"%d,%d",rect.width,rect.height);
		    fc_PutText(frame,rect.x,pt1.y-(rect.height/2)-5,boxsize,1,0,0,0);

        	}
		if(tryb == FC_TRACK) {
		    v1[0] = pt1.x;
		    v1[1] = pt1.y;
		    v2[0] = pt.x;
		    v2[1] = pt.y;
		    //jesli kliknelismy w odleglosci < 10 od punktu tzn ze punkt 0 i ze mozna cisnac dalej
		    if(fc_VectorDistance(v1,v2) < 10) {
			fc_entity[0].isFound = 1;
			fc_BasePoint(v1);
			tryb = FC_MARK;
			punktZero = ile;
			}
		} else if(tryb == FC_MOCAP) {
			//mamy p0 i lecimy
			isFound = fc_FindEntity(t_marker[ile]);
			if(isFound>=0) fc_entity[isFound].isFound = 1;
		}
		ile++;
	    }
	}

	//dokonczenie wybierania markerow po oznaczeniu p0
	if(tryb==FC_MARK) {
		j=1;
		for(i=0;i<ile;i++) {
		    if(i==punktZero) i++;
		    fc_entity[j].isFound = 1;
		    fc_SetEntity(j,t_marker[i]);
		    j++;
		}
		tryb = FC_MOCAP;
	}
    }

cvReleaseMemStorage(&storage);

}
//
//init okien i dewajsa
//
int fc_InitOpenCV(void) {

    capture = cvCaptureFromCAM(0);
    if(!capture)
    {
        printf("eee no camera??...\n");
        return -1;
    }

    if(maxX!=0&&maxY!=0) {
	cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, maxX );
	cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, maxY);
    } else {
	cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, 800 );
	cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, 600);
    }

    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0, 1, CV_AA);
    cvInitFont(&font1, CV_FONT_HERSHEY_SIMPLEX, 0.3, 0.3, 0, 1, CV_AA);

    cvNamedWindow("FaceCap video",1);
    cvNamedWindow("FaceCap filter",0);
    cvNamedWindow("FaceCap marker",0);

    //default filtra dla rozowego markera :)
    s1=96;
    s2=255;
    h1=125;
    h2=255;
    v1=89;
    v2=186;
    cvCreateTrackbar( "Hmin", "FaceCap filtr", &h1,255, 0 );
    cvCreateTrackbar( "Smin", "FaceCap filtr", &s1,255, 0 );
    cvCreateTrackbar( "Vmin", "FaceCap filtr", &v1,255, 0 );
    cvCreateTrackbar( "Hmax", "FaceCap filtr", &h2,255, 0 );
    cvCreateTrackbar( "Smax", "FaceCap filtr", &s2,255, 0 );
    cvCreateTrackbar( "Vmax", "FaceCap filtr", &h2,255, 0 );

    mminx=10;
    mminy=10;
    mmaxx=30;
    mmaxy=30;
    jitter=2;
    fcBlur=4;
    fcErode=3;
    fcOrder=0;
    interpolacja=0;
    levels=3;

    cvCreateTrackbar( "MarkerMinX", "FaceCap marker", &mminx,100, 0 );
    cvCreateTrackbar( "MarkerMinY", "FaceCap marker", &mminy,100, 0 );
    cvCreateTrackbar( "MarkerMaxX", "FaceCap marker", &mmaxx,100, 0 );
    cvCreateTrackbar( "MarkerMaxY", "FaceCap marker", &mmaxy,100, 0 );
    cvCreateTrackbar( "Jitter", "FaceCap marker", &jitter,20, 0 );
    cvCreateTrackbar( "Interpolation", "FaceCap marker", &interpolacja,1, 0 );
    cvCreateTrackbar( "Blur", "FaceCap marker", &fcBlur,21, 0 );
    cvCreateTrackbar( "Erode", "FaceCap marker", &fcErode,20, 0 );
    cvCreateTrackbar( "B/E Order", "FaceCap marker", &fcOrder,1, 0 );
    cvCreateTrackbar( "Contour", "FaceCap marker", &levels,20, 0 );
    

    cvSetMouseCallback( "FaceCap video", onMouse, 0 );

    frame=0;
    contours = 0;
    contours2 = 0;
    return 1;
}
//get frame z kamerki
void fc_GetFrame(void) {
    frame = cvQueryFrame(capture);
    if(frame) {
	if(!imgHSV) imgHSV = cvCreateImage(cvGetSize(frame), 8, 3);
	if(!imgThreshed) imgThreshed = cvCreateImage(cvGetSize(frame), 8, 1);
	imgYellowThresh = GetThresholdedImage(frame);
    }
}
//pisanie po ekranie
void fc_PutText (IplImage *image,int x, int y,char *text,int size,int r,int g,int b) {
    CvFont t_font;
    if (size!=0) t_font = font1;
	else t_font = font;
        cvPutText(image, text, cvPoint(x, y), &t_font, cvScalar(r, g, b, 0));
}
//update display :)
void fc_UpdateDisplay(void) {
	if(!frame) return;
        cvShowImage("FaceCap filter", imgYellowThresh);
        cvShowImage("FaceCap video", frame);
}
//HUD
void fc_MakeHUD(void) {
	int i;
	char hudinfo[250];
	switch(tryb) {
	    case FC_PREV:
		sprintf(hudinfo,"MODE: RGB->HSV VIEW");
		break;
	    case FC_FILTR:
		sprintf(hudinfo,"MODE: FILTER SET UP");
		break;
	    case FC_TRACK:
		sprintf(hudinfo,"MODE: TRACKING AND P0");
		break;
	    case FC_MOCAP:
		sprintf(hudinfo,"MODE: MOCAP");
		break;
	    default:
		sprintf(hudinfo,"MODE: NULL");
		break;
	}
	fc_PutText(frame,3,16,hudinfo,0,255,0,0);
	fc_PutText(frame,1,14,hudinfo,0,255,255,255);

	switch(serverStatus) {
	    case FCM_STOP:
		if(tryb<FC_MOCAP)
		    sprintf(hudinfo,"Server: N/A");
		else sprintf(hudinfo,"Server: READY TO START");
		break;
	    case FCM_INIT:
		    sprintf(hudinfo,"Server: WAITING FOR MAYA");
		break;
	    case FCM_ACTIVE:
		    sprintf(hudinfo,"Server: ACTIVE");
		break;
	    default:
		sprintf(hudinfo,"Server: NULL");
	    	break;
	}
	fc_PutText(frame,3,30,hudinfo,0,255,0,0);
	fc_PutText(frame,1,28,hudinfo,0,255,255,255);

	if(tryb == FC_MOCAP)
	for(i=0;i<MAX_MARKERS;i++) {
		if(fc_entity[i].curPos[0]!=0 && fc_entity[i].curPos[1]!=0) {
		    //klasycznie rysujemy z p0 do p[i] linie
		    cvLine(frame, cvPoint(fc_entity[0].curPos[0], fc_entity[0].curPos[1]), cvPoint(fc_entity[i].curPos[0],fc_entity[i].curPos[1]), cvScalar(255,0,0,1), 1,8,0);
		    //jesli znaleziony w tej kolecje petli to spoko a jesli nie o na czerwono go 
		    if(fc_entity[i].isFound>0)
			cvCircle(frame, cvPoint(fc_entity[i].curPos[0],fc_entity[i].curPos[1]), 6, cvScalar(0,100,255,1), 2, CV_AA,0);
		    else 
			cvCircle(frame, cvPoint(fc_entity[i].curPos[0],fc_entity[i].curPos[1]), 8, cvScalar(50,0,255,1), 8, CV_AA,0);
		    //info ladne co i gdzie
		    fc_PutText(frame,fc_entity[i].curPos[0]+7,fc_entity[i].curPos[1],fc_entity[i].name,1,255,0,0);
		    fc_PutText(frame,fc_entity[i].curPos[0]+6,fc_entity[i].curPos[1]-1,fc_entity[i].name,1,255,255,0);
		}
	}

}
