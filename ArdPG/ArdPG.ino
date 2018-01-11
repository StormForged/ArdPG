#include <Arduboy2.h>
#include "Definitions.h"
#include "Bitmap.h"
//#include "Maps.h"
#include "NPC.h"
int8_t playerX = 2, playerY = 2, playerDirection = 0;
int8_t cameraX = 0, cameraY = 0;
int8_t actionCooldown = 0;

const uint8_t gameMap[10][20] PROGMEM = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,6,4,4,4,5,4,6,4,4,4,6,5,4,6,2,0,0,0,0},
    {0,4,5,4,4,4,4,5,4,4,4,4,4,5,4,2,0,0,0,0},
    {0,4,4,4,4,4,5,4,4,6,4,10,10,10,4,2,0,0,0,0},
    {0,4,4,5,4,4,4,4,4,4,4,8,4,7,4,2,0,0,0,0},
    {0,6,4,4,4,4,5,4,4,4,6,8,9,7,4,2,0,0,0,0},
    {0,5,4,6,6,4,4,4,4,5,4,4,4,4,4,2,0,0,0,0},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

uint8_t entityMap[10][20] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}  
};

NPC *npcs[3];
NPC rudeBoy(4, 4, 0);
NPC gayBoy(4, 5, 0);
NPC sadBoy(4, 6, 0);

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(15);
    arduboy.clear();
    npcs[0] = &rudeBoy;
    npcs[1] = &gayBoy;
    npcs[2] = &sadBoy;
    for(int8_t i = 0; i < 3; i++)
      entityMap[npcs[i]->getY()][npcs[i]->getX()] = 1;
}
void loop() {
    arduboy.clear();
    if(arduboy.pressed(LEFT_BUTTON) && actionCooldown == 0){
      playerDirection = 3;
      if(pgm_read_byte(&gameMap[playerY][playerX - 1]) > 3 && entityMap[playerY][playerX - 1] == 0){
        playerX = playerX - 1;
        if(playerX <= cameraX + 1)
          cameraX = cameraX - 1;
        actionCooldown = 60; 
      }
    }
    if(arduboy.pressed(RIGHT_BUTTON) && actionCooldown == 0){
      playerDirection = 1;
      if(pgm_read_byte(&gameMap[playerY][playerX + 1]) > 3 && entityMap[playerY][playerX + 1] == 0){
        playerX = playerX + 1;
        if(playerX >= cameraX + 6)
          cameraX = cameraX + 1;
        actionCooldown = 60; 
      } 
    }
    if(arduboy.pressed(UP_BUTTON) && actionCooldown == 0){
      playerDirection = 0;
      if(pgm_read_byte(&gameMap[playerY - 1][playerX]) > 3 && entityMap[playerY - 1][playerX] == 0){
        playerY = playerY - 1;
        if(playerY <= cameraY)
          cameraY = cameraY - 1;
        actionCooldown = 60;  
      }
    }
    if(arduboy.pressed(DOWN_BUTTON) && actionCooldown == 0){
      playerDirection = 2;
      if(pgm_read_byte(&gameMap[playerY + 1][playerX]) > 3 && entityMap[playerY + 1][playerX] == 0){
        playerY = playerY + 1;
        if(playerY >= cameraY + 3)
          cameraY = cameraY + 1;
        actionCooldown = 60;
      }
    }

    //For each column on the screen
    for(int y = 0; y < 4; y++){
      for(int x = 0; x < 8; x++){
        if(y + cameraY >= 0 && x + cameraX >= 0 && y + cameraY < 8 && x + cameraX < 16)
          sprites.drawSelfMasked(x*16, y*16, tiles, pgm_read_byte(&gameMap[y + cameraY][x + cameraX]));
      }   
    }   
    
    //Drawing other entities
    //Needs to know if it is inside camera so that every entity isnt when it shouldnt be
    //This will need to be in its own class
    for(int8_t i = 0; i < 3; i++){
      if(npcs[i]->getX() < cameraX + 8 && npcs[i]->getY() >= cameraX && npcs[i]->getY() >= cameraY && npcs[i]->getY() < cameraY + 4)
        sprites.drawPlusMask((npcs[i]->getX() - cameraX) * 16, (npcs[i]->getY() - cameraY) * 16, omae, npcs[i]->getDirection());
    } 
    
    //Draw player sprite
    sprites.drawPlusMask((playerX - cameraX) * 16, (playerY - cameraY) * 16, player, playerDirection);

    //GUI
    if(arduboy.pressed(B_BUTTON)){
       for(int8_t i = 0; i < 3; i++){
         if(npcs[i]->CollisionCheck(playerX, playerY, playerDirection)){
            npcs[i]->setDirection(npcs[i]->CheckDirection(playerDirection));
            npcs[i]->CollisionStuff();  
          }  
       }
    }
    
    if(actionCooldown > 0) 
      actionCooldown--;
    arduboy.display();
}
