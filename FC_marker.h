//markers entity 
//
//
typedef struct {
    int number; //ID
    char name[20]; //Maya's name
    int isFound; // is found in current loop
    vec2_t curPos; // screen pos
    vec2_t lastPos; // last screen pos
    vec2_t fixedPos; // fixed pos p0 based
		     // if p0 then it's always <0,0>
} fc_entity_t;

//markers init
void fc_InitMarkers(void);
//p0 init
int fc_BasePoint(vec2_t v);
//clear markers
void fc_ClearMarkerStatus(void);
// entity coords
void fc_SetEntity(int n,vec2_t v);
//1.2.0
void fc_CalcFixedPos(void);
//really nice trick here 
int fc_FindEntity(vec2_t v);
