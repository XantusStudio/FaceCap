// all the functions taken from Quake3Arena :) long live JC!
#include "FC_math.h"
//
//lentgh from Pitagoras
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
// dstance
// :length(v1-v2) 
//
float fc_VectorDistance(vec2_t v1, vec2_t v2) {
    vec2_t dir;

    fc_VectorSub(v1,v2,dir);
    return fc_VectorLength(dir);
}

