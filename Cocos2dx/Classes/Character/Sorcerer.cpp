//
//  Sorcerer.cpp
//  
//
//  Created by 結城朝日 on 2022/05/24.
//

#include "Sorcerer.hpp"

void Sorcerer::init(int border, int startX, int startY, float scale) {
    printf("SorcererrInit\n");
    
    /*1数值Completed*/
    damage = new Damage;
    attack = 100;
    defence = 1.7;
    toughnessMax = 80;
    toughness = 80;
    hp = 1200;
    hpMax = 1200;
    legForce = 3000;
    
    /*2动画Completed*/
    charaAppearance = new CharaSprite;
    charaAppearance->sprite = cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-0.png");
    charaAppearance->sprite->setScale(scale);
    this->scaled = scale;
    charaAppearance->sprite->setPosition(startX, startY);
    charaAppearance->border = border;
    charaAppearance->sprite->setAnchorPoint(cocos2d::Vec2(0.5, 0));
    
    this->charaAppearance->sprite->schedule([=](float dt){
        if (this->toughness < toughnessMax) {
            toughness += 9;
        }
        else
            toughness = toughnessMax;
        printf("%d\n", toughness);
    }, 0.3, "SorcererToughness");
    
    /*3刚体Completed*/
    charaAppearance->body[0] = cocos2d::PhysicsBody::createBox(charaAppearance->sprite->getContentSize(), cocos2d::PhysicsMaterial(10, 0, 0.5));
    charaAppearance->body[0]->setMass(this->mass);
    charaAppearance->body[0]->setLinearDamping(0);
    charaAppearance->sprite->setPhysicsBody(charaAppearance->body[0]);
    
    this->charaAppearance->sprite->schedule([=](float dt){
        if (this->move == FACEL) {
            charaAppearance->body[0]->applyForce(cocos2d::Vec2(-this->legForce * 6, 0));
        }
        else if (this->move == FACER)
            charaAppearance->body[0]->applyForce(cocos2d::Vec2(this->legForce * 6, 0));
        //printf("%d", toughness);
    }, 1/30, "SorcererMove");
    
    standby();
    
};

void Sorcerer::keyW() {
    printf("SorcererW\n");
    
    /*1数值Completed*/
    state = JUMP;
    toughCoef = 1.5;
    
    /*2动画Completed*/
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/105/flandre_40-0.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/105/flandre_40-1.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/105/flandre_40-2.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/105/flandre_40-3.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/105/flandre_40-4.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/105/flandre_40-5.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/105/flandre_40-6.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/105/flandre_40-7.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/105/flandre_40-8.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/105/flandre_40-9.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/105/flandre_40-10.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/105/flandre_40-11.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/105/flandre_40-12.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/105/flandre_40-13.png")->getSpriteFrame());
    cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
    cocos2d::Animate * animate = cocos2d::Animate::create(animation);
    charaAppearance->sprite->stopAllActions();
    charaAppearance->sprite->runAction(animate);
    this->charaAppearance->sprite->scheduleOnce([=](float dt){
        state = STAND_BY;
        printf("SorcererWEnd\n");
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-0.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-1.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-2.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-3.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-4.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-5.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-6.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-7.png")->getSpriteFrame());
        cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
        cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
    }, 1.4, "SorcererWC");

    /*3刚体Completed*/
    this->move = 0;
    charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(0, this->mass * (980 * 0.5 + 100)));//I=G△t+mv=m(g△t+v)
};

void Sorcerer::keyS() {
    printf("SorcererS\n");
   
    /*1数值Completed*/
    state = BEND_BODY;
    toughCoef = 0.5;
 
    /*2动画Completed*/
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/104/flandre_10-0.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/104/flandre_10-1.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/104/flandre_10-2.png")->getSpriteFrame());
    cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.05);
    cocos2d::Animate * animate = cocos2d::Animate::create(animation);
    charaAppearance->sprite->stopAllActions();
    charaAppearance->sprite->runAction(animate);
    
    /*3刚体*/
    this->move = 0;
};

void Sorcerer::keyA() {
    printf("SorcererA\n");
   
    /*1数值Completed*/
    charaAppearance->sprite->setFlippedX(true);
    facedirection = FACEL;
    toughCoef = 1.0;
     
    /*2动画Completed*/
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/108/flandre_20-0.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/108/flandre_20-1.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/108/flandre_20-2.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/108/flandre_20-3.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/108/flandre_20-4.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/108/flandre_20-5.png")->getSpriteFrame());
    cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
    cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
    charaAppearance->sprite->stopAllActions();
    charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
    
    /*3刚体Completed*/
    charaAppearance->body[0]->applyForce(cocos2d::Vec2(-this->legForce * 150, 0));
    this->move = FACEL;
    forceCount++;
};

void Sorcerer::keyD() {
    printf("SorcererD\n");
    
    /*1数值Completed*/
    charaAppearance->sprite->setFlippedX(false);
    facedirection = FACER;
    toughCoef = 1.0;
    
    /*2动画Completed*/
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/108/flandre_20-0.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/108/flandre_20-1.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/108/flandre_20-2.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/108/flandre_20-3.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/108/flandre_20-4.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/108/flandre_20-5.png")->getSpriteFrame());
    cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
    cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
    charaAppearance->sprite->stopAllActions();
    charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
    
    /*3刚体Completed*/
    charaAppearance->body[0]->applyForce(cocos2d::Vec2(this->legForce * 150, 0));
    this->move = FACER;
    forceCount++;
};

void Sorcerer::damaged(Damage * damage) {
    printf("SorcererPVPDamaged\n");
    
    /*1数值Completed*/
    PlayableCharacter::damaged(damage);
    state = HURT;
    
    /*2动画Completed*/
    
    if (hp == 0) {
        state = LOST;
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-20.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-30.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-40.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-50.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-1.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-0.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
    }
    else if (toughness == 0)
    {
        state = KNOCKED;
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-20.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-30.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-40.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-50.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-1.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-0.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-3.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(animate2);
        }, 1.4, "SorcererKnockedAnimeC");
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("SorcererWEnd");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames3;
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-0.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-1.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-2.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-3.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-4.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-5.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-6.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-7.png")->getSpriteFrame());
            cocos2d::Animation * animation3 = cocos2d::Animation::createWithSpriteFrames(sFrames3, 0.1);
            cocos2d::Animate * animate3 = cocos2d::Animate::create(animation3);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate3));
        }, 1.8, "SorcererKnockedC");
    }
    else {
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/106/flandre_5010-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/106/flandre_5010-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/106/flandre_5010-20.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/106/flandre_5010-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/106/flandre_5010-0.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("SorcererDamagedEnd\n");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-3.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-4.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-5.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-6.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-7.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        }, 0.5, "SorcererDC");
    }
    
    /*3刚体Completed*/
    this->move = 0;
    this->charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
    charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(2 * (202 - this->facedirection) * this->mass * (this->legForce * 0.01 + 1), 0));
    
};

void Sorcerer::damaged(int damage) {
    printf("SorcererPVEDamaged\n");
    
    /*1数值Completed*/
    PlayableCharacter::damaged(damage);
    
    /*2动画Completed*/
    if (hp == 0) {
        state = LOST;
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-20.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-30.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-40.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-50.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-1.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-0.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
    }
    else if (toughness == 0)
    {
        state = KNOCKED;
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-20.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-30.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-40.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5032-50.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-1.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-0.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/107/flandre_5040-3.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(animate2);
        }, 1.4, "SorcererKnockedAnimeC");
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("SorcererWEnd");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames3;
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-0.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-1.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-2.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-3.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-4.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-5.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-6.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-7.png")->getSpriteFrame());
            cocos2d::Animation * animation3 = cocos2d::Animation::createWithSpriteFrames(sFrames3, 0.1);
            cocos2d::Animate * animate3 = cocos2d::Animate::create(animation3);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate3));
        }, 1.8, "SorcererKnockedC");
    }
    else {
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/106/flandre_5010-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/106/flandre_5010-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/106/flandre_5010-20.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/106/flandre_5010-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/106/flandre_5010-0.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("SorcererDamagedEnd\n");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-3.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-4.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-5.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-6.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-7.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        }, 0.5, "SorcererDC");
    }
    
    
    /*3刚体Completed*/
    this->move = 0;
    this->charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
    
};

void Sorcerer::standby(int stag) {
    printf("SorcererStandBy\n");
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/104/flandre_10-2.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/104/flandre_10-1.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/104/flandre_10-0.png")->getSpriteFrame());
    cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.05);
    cocos2d::Animate * animate = cocos2d::Animate::create(animation);
    
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-0.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-1.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-2.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-3.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-4.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-5.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-6.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-7.png")->getSpriteFrame());
    cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
    cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);

    /*1数值Completed*/
    if (stag == 0) {
        toughCoef = 1.0;
        this->damage->v = 0;
        this->damage->deTough = 0;
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        this->state = STAND_BY;
    }
    else if (state == BEND_BODY || state == STAND_BY) {
        if (state == BEND_BODY) {
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(animate);
            this->charaAppearance->sprite->scheduleOnce([=](float dt){
                state = STAND_BY;
                printf("SorcererWEnd");
                cocos2d::Vector<cocos2d::SpriteFrame *> sFrames3;
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-0.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-1.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-2.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-3.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-4.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-5.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-6.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-7.png")->getSpriteFrame());
                cocos2d::Animation * animation3 = cocos2d::Animation::createWithSpriteFrames(sFrames3, 0.1);
                cocos2d::Animate * animate3 = cocos2d::Animate::create(animation3);
                charaAppearance->sprite->stopAllActions();
                charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate3));
            }, 0.2, "SorcererBC");
        }
        else{
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        }
 
        this->state = STAND_BY;
    }
    
    /*2动画Completed*///补在上面
    
    /*3刚体Completed*/
    this->move = 0;
    if (this->forceCount != 0) {
        printf("Forces %d to 0\n", forceCount);
        charaAppearance->body[0]->resetForces();
        charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
        this->forceCount = 0;
    }
};

void Sorcerer::attJ() {
    printf("SorcererJ\n");

    if (this->sJReady == true) {
        /*1数值Completed*/
        int ss;
        ss = rand() * 1000;
        state = J_SKILL;
        toughCoef = 1;
        auto SorcererK = cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/101/flandre_6035-5.png");
        if (facedirection == FACEL) {
            SorcererK->setFlippedX(true);
        }
        char s[100];

        SorcererK->setScale(scaled * scaled / 20);
        SorcererK->setPosition(charaAppearance->sprite->getPositionX() + (charaAppearance->sprite->getContentSize().width/2 + 20) * (facedirection - 202), charaAppearance->sprite->getPositionY() + charaAppearance->sprite->getContentSize().height * scaled / 2);
        auto SorcererKBody = cocos2d::PhysicsBody::createBox(SorcererK->getContentSize(), cocos2d::PhysicsMaterial(1, 1, 0));
        SorcererKBody->setGravityEnable(false);
        SorcererK->setPhysicsBody(SorcererKBody);
        SorcererK->setTag(30 + ss);
        this->charaAppearance->sprite->getParent()->addChild(SorcererK);
        SorcererK->runAction(cocos2d::MoveBy::create(0.8, cocos2d::Vec2(500 * (facedirection - 202), 0)));
        sprintf(s, "SorcererJDestroy%d", ss);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
                SorcererK->removeFromParent();
            printf("SorcererJDestroy\n");
        }, 0.8, s);
        
        
        /*2动画Completed*/
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/101/flandre_200-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/101/flandre_200-1.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/101/flandre_200-2.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/101/flandre_200-3.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.05);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("SorcererDamagedEnd\n");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-3.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-4.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-5.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-6.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-7.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        }, 0.4, "SorcererJAnimeC");
        
        /*3刚体Completed*/
        this->move = 0;
        charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
        charaAppearance->body[0]->applyImpulse(cocos2d::Vec2((202 - this->facedirection) * this->mass * (this->legForce * 0.01 + 1), 0));
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
            charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(2 * (this->facedirection - 202) * this->mass * (this->legForce * 0.01 + 1), 0));
        }, 0.2, "SorcererJForward");
    }
};

void Sorcerer::attK() {
    printf("SorcererK\n");

    if (this->sKReady == true) {
        /*1数值Completed*/
        sKReady = false;
        state = K_SKILL;
        toughCoef = 1;
        this->hp += 350;
        if (hp > hpMax) {
            hp = hpMax;
        }
        this->charaAppearance->sprite->scheduleOnce([=](float dt){sKReady = true;printf("SorcererKReady");}, 5, "SorcererKC");
        
        /*2动画Completed*/
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/102/flandre_220-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/102/flandre_220-1.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/102/flandre_220-2.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/102/flandre_220-3.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/102/flandre_220-4.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/102/flandre_220-5.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/102/flandre_220-6.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/102/flandre_220-7.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/102/flandre_220-8.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/102/flandre_220-9.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.05);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("SorcererDamagedEnd\n");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-3.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-4.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-5.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-6.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-7.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        }, 0.5, "SorcererKAnimeC");
        
        /*3刚体Completed*/
        this->move = 0;
        charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
        charaAppearance->body[0]->applyImpulse(cocos2d::Vec2((202 - this->facedirection) * this->mass * (this->legForce * 0.01 + 1), 0));
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
            charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(2 * (this->facedirection - 202) * this->mass * (this->legForce * 0.01 + 1), 0));
        }, 0.2, "SorcererLForward");
    }
};

void Sorcerer::attL() {
    printf("SorcererL\n");

    if (this->sLReady == true) {
        /*1数值Completed*/
        sLReady = false;
        state = L_SKILL;
        toughCoef = 1;
        this->charaAppearance->sprite->scheduleOnce([=](float dt){sKReady = true;printf("SorcererLReady");}, 7, "SorcererLC");
        auto SorcererK = cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/103/flandre_6050-4.png");
        if (facedirection == FACEL) {
            SorcererK->setFlippedX(true);
        }
        SorcererK->setScale(scaled * scaled / 10);
        SorcererK->setPosition(charaAppearance->sprite->getPositionX() + (charaAppearance->sprite->getContentSize().width/2 + 20) * (facedirection - 202), charaAppearance->sprite->getPositionY() + charaAppearance->sprite->getContentSize().height * scaled / 2);
        auto SorcererKBody = cocos2d::PhysicsBody::createBox(SorcererK->getContentSize(), cocos2d::PhysicsMaterial(1, 1, 0));
        SorcererKBody->setGravityEnable(false);
        SorcererK->setPhysicsBody(SorcererKBody);
        SorcererK->setTag(22);
        this->charaAppearance->sprite->getParent()->addChild(SorcererK);
        SorcererK->runAction(cocos2d::MoveBy::create(0.8, cocos2d::Vec2(500 * (facedirection - 202), 0)));
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            if(charaAppearance->sprite->getParent()->getChildByTag(22) != nullptr)
                charaAppearance->sprite->getParent()->getChildByTag(22)->removeFromParent();
            printf("SorcererLDestroy\n");
        }, 0.8, "SorcererLDestroy");
        
        
        /*2动画Completed*/
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/103/flandre_250-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/103/flandre_250-1.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/103/flandre_250-2.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/103/flandre_250-3.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/103/flandre_250-4.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/103/flandre_250-5.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/103/flandre_250-6.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/103/flandre_250-7.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/103/flandre_250-8.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/103/flandre_250-9.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.05);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("SorcererDamagedEnd\n");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-3.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-4.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-5.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-6.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Sorcerer/100/flandre_0-7.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        }, 1, "SorcererLAnimeC");
        
        /*3刚体Completed*/
        this->move = 0;
        charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
        charaAppearance->body[0]->applyImpulse(cocos2d::Vec2((202 - this->facedirection) * this->mass * (this->legForce * 0.01 + 1), 0));
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
            charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(2 * (this->facedirection - 202) * this->mass * (this->legForce * 0.01 + 1), 0));
        }, 0.2, "SorcererLForward");
    }
};

