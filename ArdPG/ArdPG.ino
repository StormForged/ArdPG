#include <Arduboy2.h>
#include "Definitions.h"
#include "Bitmap.h"
#include "Levels.h"
#include "NPC.h"
#include "Maps.h"
#include "Events.h"
int8_t playerX = 2, playerY = 2, playerDirection = 0;
int8_t cameraX = 0, cameraY = 0;
int8_t actionCooldown = 0;
int8_t npcCount = 3;
int8_t levelNum = 1;
int8_t states = 1;

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

NPC rudeBoy("Rude Boy", 4, 4, 0, 0);
NPC gayBoy("Gay Boy", 5, 5, 1, 1);
NPC sadBoy("Sad Boy", 6, 6, 2, 2);
NPC soyBoy("Soy Boy", 4, 3, 3, 3);
NPC bupBoy("Bup Boy", 5, 3, 0, 4);
NPC goyBoy("Goy Boy", 6, 3, 1, 5);

void mapOneInit(){
    npcs[0] = &rudeBoy;
    npcs[1] = &gayBoy;
    npcs[2] = &sadBoy;
    for(int8_t i = 0; i < npcCount; i++)
      entityMap[npcs[i]->getY()][npcs[i]->getX()] = 1; 
}

void mapTwoInit(){
    npcs[0] = &soyBoy;
    npcs[1] = &bupBoy;
    npcs[2] = &goyBoy;
    for(int8_t i = 0; i < npcCount; i++)
      entityMap[npcs[i]->getY()][npcs[i]->getX()] = 1; 
}

void moveNPC(int8_t npc, int8_t x){
    entityMap[npcs[npc]->getY()][npcs[npc]->getX()] = 0;
    npcs[npc]->setX(x);
    entityMap[npcs[npc]->getY()][x] = 1;
}

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(15);
    arduboy.clear();
    cLevel = &levelOne;
}
void loop() {
    arduboy.clear();
    switch(states){
      case 1:
        sprites.drawSelfMasked(16, 32, title, 0);
        arduboy.setTextColor(WHITE);
        arduboy.setCursor(48, 32);
        arduboy.print("Press button to start");
        if(arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)){
          mapOneInit();
          states = 2;  
        }
        arduboy.display();
        break;
      case 2:
          if(arduboy.pressed(LEFT_BUTTON) && actionCooldown == 0){
      playerDirection = 3;
      if(pgm_read_byte(&currentLevel[playerY][playerX - 1]) > 3 && entityMap[playerY][playerX - 1] == 0){
        playerX = playerX - 1;
        if(playerX <= cameraX + 1)
          cameraX = cameraX - 1;
        actionCooldown = 60; 
      }
    }
    if(arduboy.pressed(RIGHT_BUTTON) && actionCooldown == 0){
      playerDirection = 1;
      if(pgm_read_byte(&currentLevel[playerY][playerX + 1]) > 3 && entityMap[playerY][playerX + 1] == 0){
        playerX = playerX + 1;
        if(playerX >= cameraX + 6)
          cameraX = cameraX + 1;
        actionCooldown = 60; 
      } 
    }
    if(arduboy.pressed(UP_BUTTON) && actionCooldown == 0){
      playerDirection = 0;
      if(pgm_read_byte(&currentLevel[playerY - 1][playerX]) > 3 && entityMap[playerY - 1][playerX] == 0){
        playerY = playerY - 1;
        if(playerY <= cameraY)
          cameraY = cameraY - 1;
        actionCooldown = 60;  
      }
    }
    if(arduboy.pressed(DOWN_BUTTON) && actionCooldown == 0){
      playerDirection = 2;
      if(pgm_read_byte(&currentLevel[playerY + 1][playerX]) > 3 && entityMap[playerY + 1][playerX] == 0){
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
          sprites.drawSelfMasked(x*16, y*16, tiles, pgm_read_byte(&currentLevel[y + cameraY][x + cameraX]));
      }   
    }   
    
    //Drawing other entities
    //Needs to know if it is inside camera so that every entity isnt when it shouldnt be
    //This will need to be in its own class
    for(int8_t i = 0; i < npcCount; i++){
      //if(npcs[i]->getX() < cameraX + 8 && npcs[i]->getY() >= cameraX && npcs[i]->getY() >= cameraY && npcs[i]->getY() < cameraY + 4)
        sprites.drawPlusMask((npcs[i]->getX() - cameraX) * 16, (npcs[i]->getY() - cameraY) * 16, omae, npcs[i]->getDirection());
    } 
    
    //Draw player sprite
    sprites.drawPlusMask((playerX - cameraX) * 16, (playerY - cameraY) * 16, player, playerDirection);
    if(arduboy.pressed(A_BUTTON) && actionCooldown == 0){
      if(levelNum == 1){
        for(int8_t i = 0; i < 3; i++)
          entityMap[npcs[i]->getY()][npcs[i]->getX()] = 0;
        memset(npcs, 0, sizeof(npcs));
        levelNum = 2;
        actionCooldown = 60;
        mapTwoInit();
      }
      else if(levelNum == 2){
        for(int8_t i = 0; i < 3; i++)
          entityMap[npcs[i]->getY()][npcs[i]->getX()] = 0;
        memset(npcs, 0, sizeof(npcs));
        levelNum = 1;
        actionCooldown = 60;
        mapOneInit();
      }
    }
    //GUI
    if(arduboy.pressed(B_BUTTON)){
       for(int8_t i = 0; i < 3; i++){
         if(npcs[i]->CollisionCheck(playerX, playerY, playerDirection)){
            npcs[i]->setDirection(npcs[i]->CheckDirection(playerDirection));
            npcs[i]->CollisionStuff();  
          }  
       }
    }
    
    //if(arduboy.pressed(B_BUTTON)){
    //  moveNPC(0, 1);  
    //}
    
    if(actionCooldown > 0) 
      actionCooldown--;
    arduboy.display();
        break;
    }

}
