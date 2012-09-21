#include "FC_global.h"

//inicjalizacja tabeli markerow
void fc_InitMarkers(void) {
    int i;
    for (i=0;i<MAX_MARKERS;i++) {
	fc_entity[i].number=i;
	fc_entity[i].curPos[0]=0;
	fc_entity[i].curPos[1]=0;
	fc_entity[i].fixedPos[0]=0;
	fc_entity[i].fixedPos[1]=0;
	fc_entity[i].lastPos[0]=0;
	fc_entity[i].lastPos[1]=0;
	sprintf(fc_entity[i].name,"p%d",i);
    }
}

//ustalanie punktu p0
int fc_BasePoint(vec2_t v) {
    if(strlen(fc_entity[0].name)>0) {
	fc_VectorCopy(v,fc_entity[0].curPos);
	return 1;
    } else {
	return -1;
    }
}

//zapisanie wsolrzednych w curPos,lastPos i fixed
//1.3.0 - najwieksza zmiana:
//- interpolacja 
//
void fc_SetEntity(int n,vec2_t v) {
    vec2_t tmp;

    tmp[0]=0;
    tmp[1]=0;
    
    if(n>-1 && n<MAX_MARKERS) {
	//jitter removal
	if(jitter>0 && interpolacja < 1) {
	    if(fc_VectorDistance(fc_entity[n].curPos,v) < jitter){
		v[0]=fc_entity[n].curPos[0];
		v[1]=fc_entity[n].curPos[1];
	    }
	} else if(interpolacja > 0){
	    if(fc_entity[n].lastPos[0]!=0 && fc_entity[n].lastPos[1]!=0) {
		tmp[0] = (fc_entity[n].curPos[0] + v[0] + fc_entity[n].lastPos[0])/3;
		tmp[1] = (fc_entity[n].curPos[1] + v[1] + fc_entity[n].lastPos[1])/3;
	    }
	}
	//backup ostatniej pozycji
	fc_VectorCopy(fc_entity[n].curPos,fc_entity[n].lastPos);
	// nowe wspolrzedne do cur
	if(tmp[0]!=0 && tmp[1]!=0) {
	    fc_VectorCopy(tmp,fc_entity[n].curPos);
	}else {
	    fc_VectorCopy(v,fc_entity[n].curPos);
	}
	// i wartosc fixedPos (p0-p[n])
	if(n==0) { 
	    fc_entity[n].fixedPos[0]=0;
	    fc_entity[n].fixedPos[1]=0;
	}
//	printf("[%d] [%f,%f],[%f,%f],[%f,%f]\n",n,fc_entity[n].lastPos[0],fc_entity[n].lastPos[1],fc_entity[n].curPos[0],fc_entity[n].curPos[1],v[0],v[1]);
	//1.2.0
	//fixedPos na koncu liczone
	//else {
	//    fc_VectorSub(fc_entity[0].curPos,fc_entity[n].curPos,fc_entity[n].fixedPos);
	//}
    }
}

//1.2.0
void fc_CalcFixedPos(void) {
    int i;
    //pomijamy p0
    for (i=1;i<MAX_MARKERS;i++) {
	if(fc_entity[i].isFound==1)
	    fc_VectorSub(fc_entity[0].curPos,fc_entity[i].curPos,fc_entity[i].fixedPos);
    }
}

//czysci status markerow
void fc_ClearMarkerStatus(void) {
    int i;
    for (i=0;i<MAX_MARKERS;i++) {
	fc_entity[i].isFound=0;
    }
}

//i to ciekawa funkcja wlasnie
// szuka najblizszego markera
int fc_FindEntity(vec2_t v) {
    int i;
    int nearest,dist,t_dist;

    nearest = -1;
    dist = -1;
    for (i=0;i<MAX_MARKERS;i++) {
	if(nearest<0 && i==0) { 
	    dist = fc_VectorDistance(v,fc_entity[0].curPos);
	    nearest = 0;
	} else {
	    t_dist = fc_VectorDistance(v,fc_entity[i].curPos);
	    if( t_dist < dist) {
		nearest = i;
		dist=t_dist;
	    }
	}
    }
    if(nearest>-1) {
	fc_SetEntity(nearest,v);
	return fc_entity[nearest].number;
    } else {
	return -1;
    }
}
