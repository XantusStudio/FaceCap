// struktura bytu markera
//
//
typedef struct {
    int number; // numer ID
    char name[20]; //nazwa dla majki
    int isFound; // czy w danej petli znaleziono cos
    vec2_t curPos; // pozycja na ekranie
    vec2_t lastPos; // poprzednia pozycja na ekranie
    vec2_t fixedPos; // przeliczona pozycja wzgledem punku bazowego
		     // jesli bazowy to 0,0
} fc_entity_t;

//inicjalizacja markerow
void fc_InitMarkers(void);
// init punktu bazowego
int fc_BasePoint(vec2_t v);
//czysci status makerow
void fc_ClearMarkerStatus(void);
// ustalanie wsp dla ent
void fc_SetEntity(int n,vec2_t v);
//1.2.0
void fc_CalcFixedPos(void);
//ciekawa funkcja zlepiajace wspolrzedne
int fc_FindEntity(vec2_t v);
