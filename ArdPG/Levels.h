#pragma once
#include "NPC.h"
#include "Maps.h"

class Levels {
    public:
    NPC *npcc[];
    int8_t *mapData;  
};

Levels levelOne;
Levels *cLevel;
