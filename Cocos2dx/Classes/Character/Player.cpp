//
//  Player.cpp
//  
//
//  Created by 結城朝日 on 2022/05/24.
//

#include "Player.hpp"

using namespace std;

int Player::getHealth() { //Completed
    return chara->getHealth();
};

void Player::moveLeft() { //Completed
    if (this->chara->state == STAND_BY)
        chara->keyA();
};

void Player::moveRight() {//Completed
    if (this->chara->state == STAND_BY)
        chara->keyD();
};

void Player::moveUp() { //Completed
    if (this->chara->state == STAND_BY)
        chara->keyW();
};

void Player::moveDown() { //Completed
    if (this->chara->state == STAND_BY)
        chara->keyS();
};

void Player::init(int border, int startX, int startY, int character, float scale) { //Completed
    switch (character) {
        case SABER:
            chara = (Saber *)new Saber;
            break;
        case MONK:
            chara = new Monk;
            break;
        case SORCERER:
            chara = new Sorcerer;
            break;
            
        default:
            break;
    }
    chara->init(border, startX, startY, scale);
};

Damage * Player::getDamage() { //Completed
    return chara->damage;
};

cocos2d::Sprite * Player::getSprite() { //Completed
    return chara->getSprite();
};

void Player::attack(char key) { //Completed
    if (this->chara->state == STAND_BY)
        {
            switch (key) {
            case 'j':
                chara->attJ();
                break;
            case 'k':
                chara->attK();
                break;
            case 'l':
                chara->attL();
                break;
                
            default:
                break;
            }
        }
};

void Player::attackReset() { //Abandoned
    return;
};

void Player::setTag(int tag) { //Completed
    chara->setTag(tag);
};

int Player::getTag() { //Completed
    return chara->getTag();
};

void Player::damaged(Player *attacker) { //Completed
    if (attacker->getDamage()->v == 0) {
        return;
    }
    if (chara->state == HURT || chara->state == LOST || chara->state == KNOCKED) {
        return;
    }
    if ((attacker->getSprite()->getPositionX() - this->getSprite()->getPositionX()) * (attacker->chara->facedirection - 202) <= 0) {
        this->chara->facedirection = ((attacker->getSprite()->getPositionX() - this->getSprite()->getPositionX() > 0) ? FACER : FACEL);
        this->chara->charaAppearance->sprite->setFlippedX(((attacker->getSprite()->getPositionX() - this->getSprite()->getPositionX() > 0) ? false : true));
        chara->damaged(attacker->getDamage());
    }

};

void Player::hit(int hitTag) { //Completed
    if (chara->state == HURT || chara->state == LOST || chara->state == KNOCKED) {
        return;
    }
    chara->hit(hitTag);
};

void Player::standby() { //Completed
    if (chara->state == BEND_BODY || chara->state == STAND_BY)
        chara->standby(1);//主动调用stag = 1
};

void Player::setScale(double scale) { //Completed
    chara->setScale(scale);
};

void Player::pveHurt(int hurt) { //Completed
    if (chara->state == HURT || chara->state == LOST || chara->state == KNOCKED) {
        return;
    }
    chara->damaged(hurt);
};

void Player::forceMoveBy(float duration, cocos2d::Vec2 move) { //Completed
    chara->forceMoveBy(duration, move);
};
