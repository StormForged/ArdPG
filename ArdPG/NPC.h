#pragma once
#include "Events.h"
class NPC{
  public:
    //Constructor
    NPC(char* n, int8_t x, int8_t y, int8_t df, int8_t id){
      strcpy(npcName, n);
	  xPosition = x;
      yPosition = y;
      directionFacing = df;
	  npcID = id;
    }
    bool CollisionCheck(int8_t playerX, int8_t playerY, int8_t playerDirection){
        if(playerDirection == 0){
          if(playerX == xPosition && playerY - 1 == yPosition)
            return true;   
        }
        if(playerDirection == 1){
          if(playerX + 1 == xPosition && playerY == yPosition)
            return true;   
        }
        if(playerDirection == 2){
          if(playerX == xPosition && playerY + 1 == yPosition)
            return true;   
        }
        if(playerDirection == 3){
          if(playerX - 1 == xPosition && playerY == yPosition)
            return true;   
        }

        return false;
    }
    int8_t CheckDirection(int8_t playerDirection){
      if(playerDirection == 0)
        return 2;
      if(playerDirection == 1)
        return 3;
      if(playerDirection == 2)
        return 0;
      if(playerDirection == 3)
        return 1;

      return 0;
   }
   void CollisionStuff(){
      NPCInteract(npcID);
   }
   int8_t getX(){
    return xPosition;
   }
   int8_t getY(){
    return yPosition; 
   }
   int8_t getDirection(){
    return directionFacing;
   }
   void setDirection(int8_t d){
     directionFacing = d;
   }
   int8_t getID(){
    return npcID;
   }
   void setX(int8_t x){
    xPosition = x;
   }
  private:
    char npcName[10];
	int8_t npcID;
    int8_t xPosition;
    int8_t yPosition;
    int8_t directionFacing;
};
