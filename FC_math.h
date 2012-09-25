#include <stdlib.h>
#include <math.h>
//^^ for sqrt()

// vectors def
typedef float vec_t; //1d
typedef vec_t vec2_t[2]; //2d

// vectors sub
#define fc_VectorSub(a,b,c)     {c[0]=a[0]-b[0];c[1]=a[1]-b[1];}
// add
#define fc_VectorAdd(a,b,c)     {c[0]=a[0]+b[0];c[1]=a[1]+b[1];}
// copy
#define fc_VectorCopy(a,b) {b[0]=a[0];b[1]=a[1];}

//lentgh
float fc_VectorLength(vec2_t v);
//distance
float fc_VectorDistance(vec2_t v1, vec2_t v2);
