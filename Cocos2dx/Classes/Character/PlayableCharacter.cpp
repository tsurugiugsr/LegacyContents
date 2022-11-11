//
//  PlayableCharacter.cpp
//  Fight
//
//  Created by 松岡東矢 on 2022/05/24.
//

#include "PlayableCharacter.hpp"

cocos2d::Sprite * PlayableCharacter::getSprite() { //Completed
    return charaAppearance->sprite;
};

//void PlayableCharacter::init(int border, int startX, int startY) { //Split
//
//};

void PlayableCharacter::keyW() { //Derived
    
};

void PlayableCharacter::keyS() { //Derived
    
};

void PlayableCharacter::keyA() { //Derived
    
};

void PlayableCharacter::keyD() { //Derived
    
};

void PlayableCharacter::damaged(Damage * damage) { //Split
    if (damage->v == 0)
        return;
    
    this->hp -= (double)damage->v * (this->defence - 1.0) * this->defenceBuff;
    if (this->hp < 0) {
        this->hp = 0;
    }
    this->toughness -= damage->deTough * this->toughCoef;
    if (this->toughness < 0) {
        this->toughness = 0;
    }
    if (hp == 0) {
        this->state = LOST;
    }
    if (toughness == 0) {
        this->state = KNOCKED;
        this->toughCoef = 0;
    }
    else if (state == STAND_BY) {
        this->state = HURT;
        this->toughCoef = 0;
    }
};

void PlayableCharacter::damaged(int damage) { //Split
    this->hp -= damage * (this->defence - 1.0) * this->defenceBuff;
    if (this->hp < 0) {
        this->hp = 0;
    }
    if (hp == 0) {
        this->state = LOST;
    }
    else if (state == STAND_BY) {
        this->state = HURT;
    }
};

int PlayableCharacter::getHealth() { //Completed
    return this->hp;
};

void PlayableCharacter::standby(int stag) { //Derived
    
};

void PlayableCharacter::attJ() { //Derived
    
};

void PlayableCharacter::attK() { //Derived
    
};

void PlayableCharacter::attL() { //Derived
    
};

void PlayableCharacter::setTag(int tag) { //Completed
    this->charaAppearance->sprite->setTag(tag);
};

int PlayableCharacter::getTag() { //Completed
    return charaAppearance->sprite->getTag();
};

void PlayableCharacter::hit(int hitTag) { //Completed
    int tV, tDetough = 40;
    switch (hitTag) {
        case 20:
            tV = 150;
            break;
        case 21:
            tV = 100;
            break;
        case 22:
            tV = 200;
            break;
            
        default:
            tV = 100;
            break;
    }
    this->hitdamage->deTough = tDetough;
    this->hitdamage->v = tV;
    this->damaged(this->hitdamage);
};

void PlayableCharacter::setScale(double scale) { //Completed
    charaAppearance->sprite->setScale(scale);
    this->scaled = scale;
};

void PlayableCharacter::forceMoveBy(float duration, cocos2d::Vec2 move) { //Completed
    charaAppearance->sprite->runAction(cocos2d::Sequence::create(cocos2d::MoveBy::create(duration, move), NULL));
};

