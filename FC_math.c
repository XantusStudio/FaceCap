// wszystkie poniższe funkcje wziete z kodu Quake3Arena :)
// jest GPL wiec można
#include "FC_math.h"
//
//dlugosc vectora od pana
//pitagorasa
//
float fc_VectorLength(vec2_t v) {
    int i;
    double length;

    length=0;
    for(i=0;i<2;i++) {
	length += v[i]*v[i];
    }
    if(length!=0)
	length = sqrt(length);
    return length;
}
//
// odleglosc miedzy vectorami
// :dlugosc(v1-v2) 
//
float fc_VectorDistance(vec2_t v1, vec2_t v2) {
    vec2_t dir;

    fc_VectorSub(v1,v2,dir);
    return fc_VectorLength(dir);
}

