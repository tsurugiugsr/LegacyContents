//
//  PlayableCharacter.hpp
//  Fight
//
//  Created by 結城朝日 on 2022/05/24.
//

#ifndef PlayableCharacter_hpp
#define PlayableCharacter_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Damage.hpp"
#include "DefinedMacros.h"
#include "CharaSprite.hpp"

class PlayableCharacter {
public:
    int hp = 1000;
    int state = 0;
    int mass = 60;
    int height = 180;
    int width = 60;
    int legForce = 200;
    int forceCount = 0;
    int attack = 100;
    double defence = 2.0;
    int facedirection = FACER;
    int toughness = 100;
    double toughCoef = 1.0;
    int toughCoefBuf = 0;
    CharaSprite * charaAppearance;
    double attackBuff = 1.0;
    double defenceBuff = 1.0;
    int attackBuffCount = 0;
    int defenceBuffCount = 0;
    bool sKReady = true;
    bool sLReady = true;
    float scaled = 1.0;
    int move = 0;
    
public:
    int hpMax = 1000;
    int toughnessMax = 100;
    Damage * damage;
    Damage * hitdamage;
    
    cocos2d::Sprite * getSprite();
    virtual void init(int border, int startX, int startY, float scale = 1.0) = 0;
    virtual void keyW();
    virtual void keyS();
    virtual void keyA();
    virtual void keyD();
    virtual void damaged(Damage * damage);
    virtual void damaged(int damage);
    int getHealth();
    virtual void standby(int stag = 0);
    virtual void attJ();
    virtual void attK();
    virtual void attL();
    void setTag(int tag);
    int getTag();
    void hit(int hitTag);
    void setScale(double scale);
    void forceMoveBy(float duration, cocos2d::Vec2 move);
};

#endif /* PlayableCharacter_hpp */
