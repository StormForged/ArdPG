#pragma once
#include "NPC.h"
bool switches[NUM_OF_SWITCHES] = {};
char npcName[10];
void rudeBoyEvents();
void gayBoyEvents();
void sadBoyEvents();
void soyBoyEvents();
void bupBoyEvents();
void goyBoyEvents();

typedef void (*func_ptr)(void);
func_ptr func_ptr_array[NUM_OF_NPCS] = {rudeBoyEvents, gayBoyEvents, sadBoyEvents, soyBoyEvents, bupBoyEvents, goyBoyEvents};

void NPCInteract(int8_t npcID){
  func_ptr_array[npcID]();
}

void rudeBoyEvents(){
  arduboy.print("hey");
  if(switches[TALKED_TO_BRAD] == false)
    switches[TALKED_TO_BRAD] = true;
}

void gayBoyEvents(){
  if(switches[TALKED_TO_BRAD] == true){
    arduboy.print("cunt");
    return;  
  }
  arduboy.print("faggot,");
}

void sadBoyEvents(){
  arduboy.print("you're");
}

void soyBoyEvents(){
  arduboy.print("pretty");
}

void bupBoyEvents(){
  if(bupBoy.getDirection() = SOUTH){
    arduboy.print("You did it");  
  }
  arduboy.print("fucking");
}

void goyBoyEvents(){
  arduboy.print("dumb");
}


