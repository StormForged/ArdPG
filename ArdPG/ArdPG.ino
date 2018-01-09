#include <Arduboy2.h>
#include "Bitmap.h"
Arduboy2 arduboy;
Sprites sprites;
int playerX = 0, playerY = 0;
int cameraX = 0, cameraY = 0;
int actionCooldown = 0;

const uint8_t gameMap[8][16] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {1,6,0,0,0,5,0,6,0,0,0,6,5,0,6,3},
    {1,0,5,0,0,0,0,5,0,0,0,0,0,5,0,3},
    {1,0,0,0,0,0,5,0,0,6,0,10,10,10,0,3},
    {1,0,0,5,0,0,0,0,0,0,0,8,0,7,0,3},
    {1,6,0,0,0,0,5,0,0,0,6,8,9,7,0,3},
    {1,5,0,6,6,0,0,0,0,5,0,0,0,0,0,3},
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
};

void setup() {
    arduboy.begin();
    arduboy.clear(); 
}
void loop() {
    arduboy.clear();
    if(arduboy.pressed(LEFT_BUTTON) && actionCooldown == 0){
      cameraX = cameraX - 1;
      actionCooldown = 60;
    }
    if(arduboy.pressed(RIGHT_BUTTON) && actionCooldown == 0){
      cameraX = cameraX + 1;
      actionCooldown = 60;
    }
    if(arduboy.pressed(UP_BUTTON) && actionCooldown == 0){
      cameraY--;
      actionCooldown = 60;  
    }
    if(arduboy.pressed(DOWN_BUTTON) && actionCooldown == 0){
      cameraY++;
      actionCooldown = 60;
    }
    //For each column on the screen
    for(int y = 0; y < 4; y++){
      for(int x = 0; x < 8; x++){
        if(y + cameraY >= 0 && x + cameraX >= 0 && y + cameraY < 8 && x + cameraX < 16)
          sprites.drawSelfMasked(x*16, y*16, tiles, gameMap[y + cameraY][x + cameraX]);
          arduboy.setCursor(0,0);
      }   
    }   

    if(arduboy.pressed(A_BUTTON)){
      arduboy.fillRect(0, 0, 64, 16, BLACK);
      arduboy.setCursor(0,0);
      arduboy.print(cameraX);  
    }

    //Draw player sprite
    sprites.drawOverwrite(playerX, playerY, player,0);
    if(actionCooldown > 0) 
      actionCooldown--;
    arduboy.display();
}
