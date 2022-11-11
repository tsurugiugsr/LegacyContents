//
//  Player.hpp
//  
//
//  Created by 結城朝日 on 2022/05/24.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "PlayableCharacter.hpp"
#include "Character/Saber.hpp"
#include "Character/Monk.hpp"
#include "Character/Sorcerer.hpp"

class Player {
public:
    PlayableCharacter *chara;
    
    int getHealth();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    
    void init(int border, int startX, int startY, int character, float scale = 1);
    Damage * getDamage();
    cocos2d::Sprite * getSprite();
    void attack(char key);
    void attackReset();
    void setTag(int tag);
    int getTag();
    void damaged(Player *attacker);
    void hit(int hitTag);
    void standby();
    void setScale(double scale);
    void pveHurt(int hurt);
    void forceMoveBy(float duration, cocos2d::Vec2 move);
};

#endif /* Player_hpp */
