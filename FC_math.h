#include <stdlib.h>
#include <math.h>
//^^ dla sqrt() w sumie

// definicje vektorow 
typedef float vec_t; //1d
typedef vec_t vec2_t[2]; //2d

// odejmowanie vectorow jako proste makro
#define fc_VectorSub(a,b,c)     {c[0]=a[0]-b[0];c[1]=a[1]-b[1];}
// podobnie z dodawaniem 
#define fc_VectorAdd(a,b,c)     {c[0]=a[0]+b[0];c[1]=a[1]+b[1];}
// i kopiowaniem
#define fc_VectorCopy(a,b) {b[0]=a[0];b[1]=a[1];}

//dlugosc vectora
float fc_VectorLength(vec2_t v);
//odleglosc miedzy vectorami
float fc_VectorDistance(vec2_t v1, vec2_t v2);
