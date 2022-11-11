//
//  Saber.cpp
//  Fight
//
//  Created by 松岡東矢 on 2022/05/24.
//

#include "Saber.hpp"

void Saber::init(int border, int startX, int startY, float scale) {
    printf("SaberInit\n");
    
    /*1数值Completed*/
    damage = new Damage;
    attack = 100;
    defence = 2;
    toughnessMax = 100;
    toughness = 100;
    hp = 1000;
    hpMax = 1000;
    legForce = 3000;
    
    /*2动画Completed*/
    charaAppearance = new CharaSprite;
    charaAppearance->sprite = cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-0.png");
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
    }, 0.3, "SaberToughness");
    
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
    }, 1/30, "SaberMove");
    
    standby();

};

void Saber::keyW() {
    printf("SaberW\n");
    
    /*1数值Completed*/
    state = JUMP;
    toughCoef = 1.5;
    
    /*2动画Completed*/
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/105/kirito_41-0.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/105/kirito_41-1.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/105/kirito_41-2.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/105/kirito_41-3.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/105/kirito_41-4.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/105/kirito_41-5.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/105/kirito_41-6.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/105/kirito_41-5.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/105/kirito_41-4.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/105/kirito_41-3.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/105/kirito_41-2.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/105/kirito_41-1.png")->getSpriteFrame());
    cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
    cocos2d::Animate * animate = cocos2d::Animate::create(animation);
    charaAppearance->sprite->stopAllActions();
    charaAppearance->sprite->runAction(animate);
    this->charaAppearance->sprite->scheduleOnce([=](float dt){
        state = STAND_BY;
        printf("SaberWEnd\n");
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-0.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-1.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-2.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-3.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-4.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-5.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-6.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-7.png")->getSpriteFrame());
        cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
        cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
    }, 1.2, "SaberWC");

    /*3刚体Completed*/
    this->move = 0;
    charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(0, this->mass * (980 * 0.5 + 100)));//I=G△t+mv=m(g△t+v)

};

void Saber::keyS() {
    printf("SaberS\n");
   
    /*1数值Completed*/
    state = BEND_BODY;
    toughCoef = 0.5;
 
    /*2动画Completed*/
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/104/kirito_10-0.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/104/kirito_10-1.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/104/kirito_10-2.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/104/kirito_10-3.png")->getSpriteFrame());
    cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.05);
    cocos2d::Animate * animate = cocos2d::Animate::create(animation);
    charaAppearance->sprite->stopAllActions();
    charaAppearance->sprite->runAction(animate);
    
    /*3刚体*/
    this->move = 0;

};

void Saber::keyA() {
    printf("SaberA\n");
   
    /*1数值Completed*/
    charaAppearance->sprite->setFlippedX(true);
    facedirection = FACEL;
    toughCoef = 1.0;
     
    /*2动画Completed*/
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/108/kirito_21-0.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/108/kirito_21-1.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/108/kirito_21-2.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/108/kirito_21-3.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/108/kirito_21-4.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/108/kirito_21-5.png")->getSpriteFrame());
    cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
    cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
    charaAppearance->sprite->stopAllActions();
    charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
    
    /*3刚体Completed*/
    charaAppearance->body[0]->applyForce(cocos2d::Vec2(-this->legForce * 150, 0));
    this->move = FACEL;
    forceCount++;

};

void Saber::keyD() {
    printf("SaberD\n");
    
    /*1数值Completed*/
    charaAppearance->sprite->setFlippedX(false);
    facedirection = FACER;
    toughCoef = 1.0;
    
    /*2动画Completed*/
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/108/kirito_21-0.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/108/kirito_21-1.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/108/kirito_21-2.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/108/kirito_21-3.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/108/kirito_21-4.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/108/kirito_21-5.png")->getSpriteFrame());
    cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
    cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
    charaAppearance->sprite->stopAllActions();
    charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
    
    /*3刚体Completed*/
    charaAppearance->body[0]->applyForce(cocos2d::Vec2(this->legForce * 150, 0));
    this->move = FACER;
    forceCount++;

};

void Saber::damaged(Damage * damage) {
    printf("SaberPVPDamaged\n");
    if (damage->v == 0) {
        return;
    }
    
    /*1数值Completed*/
    PlayableCharacter::damaged(damage);
    state = HURT;
    
    /*2动画Completed*/
    
    if (hp == 0) {
        state = LOST;
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5032-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5032-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5042-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5042-10.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
    }
    else if (toughness == 0)
    {
        state = KNOCKED;
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5032-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5032-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5042-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5042-10.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5042-20.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5020-30.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5020-20.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5020-10.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5020-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5012-20.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5012-10.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5012-0.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(animate2);
        }, 1.4, "SaberKnockedAnimeC");
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("SaberWEnd");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames3;
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-0.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-1.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-2.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-3.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-4.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-5.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-6.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-7.png")->getSpriteFrame());
            cocos2d::Animation * animation3 = cocos2d::Animation::createWithSpriteFrames(sFrames3, 0.1);
            cocos2d::Animate * animate3 = cocos2d::Animate::create(animation3);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate3));
        }, 2.7, "SaberKnockedC");
    }
    else {
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/106/kirito_5010-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/106/kirito_5010-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/106/kirito_5010-20.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/106/kirito_5010-30.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("SaberDamagedEnd\n");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-3.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-4.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-5.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-6.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-7.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        }, 0.4, "SaberDC");
    }
    
    /*3刚体Completed*/
    this->move = 0;
    this->charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
    charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(2 * (202 - this->facedirection) * this->mass * (this->legForce * 0.01 + 1), 0));
    
};

void Saber::damaged(int damage) {
    printf("SaberPVEDamaged\n");
    
    /*1数值Completed*/
    PlayableCharacter::damaged(damage);
    
    /*2动画Completed*/
    if (hp == 0) {
        state = LOST;
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5032-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5032-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5042-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5042-10.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
    }
    else if (toughness == 0)
    {
        state = KNOCKED;
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5032-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5032-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5042-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5042-10.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5042-20.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5020-30.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5020-20.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5020-10.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5020-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5012-20.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5012-10.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/107/kirito_5012-0.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(animate2);
        }, 1.4, "SaberKnockedAnimeC");
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("SaberWEnd");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames3;
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-0.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-1.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-2.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-3.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-4.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-5.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-6.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-7.png")->getSpriteFrame());
            cocos2d::Animation * animation3 = cocos2d::Animation::createWithSpriteFrames(sFrames3, 0.1);
            cocos2d::Animate * animate3 = cocos2d::Animate::create(animation3);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate3));
        }, 2.7, "SaberKnockedC");
    }
    else {
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/106/kirito_5010-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/106/kirito_5010-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/106/kirito_5010-20.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/106/kirito_5010-30.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("SaberDamagedEnd\n");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-3.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-4.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-5.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-6.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-7.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        }, 0.4, "SaberDC");
    }
    
    
    /*3刚体Completed*/
    this->move = 0;
    this->charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
    
};

void Saber::standby(int stag) {
    printf("SaberStandBy\n");
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/104/kirito_10-3.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/104/kirito_10-2.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/104/kirito_10-1.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/104/kirito_10-0.png")->getSpriteFrame());
    cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.05);
    cocos2d::Animate * animate = cocos2d::Animate::create(animation);
    
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-0.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-1.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-2.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-3.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-4.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-5.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-6.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-7.png")->getSpriteFrame());
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
                printf("SaberWEnd");
                cocos2d::Vector<cocos2d::SpriteFrame *> sFrames3;
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-0.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-1.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-2.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-3.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-4.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-5.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-6.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-7.png")->getSpriteFrame());
                cocos2d::Animation * animation3 = cocos2d::Animation::createWithSpriteFrames(sFrames3, 0.1);
                cocos2d::Animate * animate3 = cocos2d::Animate::create(animation3);
                charaAppearance->sprite->stopAllActions();
                charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate3));
            }, 0.2, "SaberBC");
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

void Saber::attJ() {
    printf("SaberJ\n");

    /*1数值Completed*/
    state = J_SKILL;
    toughCoef = 1;
    int times = 1;
    this->damage->v = this->attack * times * this->attackBuff;
    this->damage->deTough = 40;
    
    /*2动画Completed*/
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/101/kirito_210-1.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/101/kirito_210-2.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/101/kirito_210-3.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/101/kirito_210-4.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/101/kirito_210-5.png")->getSpriteFrame());
    cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
    cocos2d::Animate * animate = cocos2d::Animate::create(animation);
    charaAppearance->sprite->stopAllActions();
    charaAppearance->sprite->runAction(animate);
    this->charaAppearance->sprite->scheduleOnce([=](float dt){
        state = STAND_BY;
        printf("SaberDamagedEnd\n");
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-0.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-1.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-2.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-3.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-4.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-5.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-6.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-7.png")->getSpriteFrame());
        cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
        cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        toughCoef = 1.0;
        this->damage->v = 0;
        this->damage->deTough = 0;
    }, 0.5, "SaberJC");
    
    /*3刚体Completed*/
    this->move = 0;
    charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
    charaAppearance->body[0]->applyImpulse(cocos2d::Vec2((202 - this->facedirection) * this->mass * (this->legForce * 0.01 + 1), 0));
    this->charaAppearance->sprite->scheduleOnce([=](float dt){
        charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
        charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(1.5 * (this->facedirection - 202) * this->mass * (this->legForce * 0.01 + 1), 0));
    }, 0.1, "SaberJForward");

};

void Saber::attK() {
    printf("SaberK\n");

    if (this->sKReady == true) {
        /*1数值Completed*/
        sKReady = false;
        state = K_SKILL;
        toughCoef = 1;
        this->charaAppearance->sprite->scheduleOnce([=](float dt){sKReady = true;printf("SaberKReady");}, 5, "SaberKC");
        auto SaberK = cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/102/kirito_320-2.png");
        if (facedirection == FACEL) {
            SaberK->setFlippedX(true);
        }
        SaberK->setScale(scaled * scaled / 2);
        SaberK->setPosition(charaAppearance->sprite->getPositionX() + (charaAppearance->sprite->getContentSize().width/2 + 20) * (facedirection - 202), charaAppearance->sprite->getPositionY() + charaAppearance->sprite->getContentSize().height * scaled / 2);
        auto SaberKBody = cocos2d::PhysicsBody::createBox(SaberK->getContentSize(), cocos2d::PhysicsMaterial(1, 1, 0));
        SaberKBody->setGravityEnable(false);
        SaberK->setPhysicsBody(SaberKBody);
        SaberK->setTag(20);
        this->charaAppearance->sprite->getParent()->addChild(SaberK);
        SaberK->runAction(cocos2d::MoveBy::create(0.8, cocos2d::Vec2(500 * (facedirection - 202), 0)));
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            if(charaAppearance->sprite->getParent()->getChildByTag(20) != nullptr)
                charaAppearance->sprite->getParent()->getChildByTag(20)->removeFromParent();
            printf("SaberKDestroy\n");
        }, 0.8, "SaberKDestroy");
        
        
        /*2动画Completed*/
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/102/kirito_200-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/102/kirito_200-1.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/102/kirito_200-2.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/102/kirito_200-3.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.05);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("SaberDamagedEnd\n");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-3.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-4.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-5.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-6.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-7.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        }, 0.4, "SaberKAnimeC");
        
        /*3刚体Completed*/
        this->move = 0;
        charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
        charaAppearance->body[0]->applyImpulse(cocos2d::Vec2((202 - this->facedirection) * this->mass * (this->legForce * 0.01 + 1), 0));
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
            charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(2 * (this->facedirection - 202) * this->mass * (this->legForce * 0.01 + 1), 0));
        }, 0.2, "SaberLForward");
    }

};

void Saber::attL() {
    printf("SaberL\n");
    
    if (this->sLReady == true) {
        /*1数值Completed*/
        sLReady = false;
        state = L_SKILL;
        toughCoef = 1;
        float times = 1.5;
        this->damage->v = this->attack * times * this->attackBuff;
        this->damage->deTough = 40;
        this->charaAppearance->sprite->scheduleOnce([=](float dt){sLReady = true;printf("SaberLReady");}, 7, "SaberLC");
     
        /*2动画Completed*/
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/103/kirito_220-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/103/kirito_220-1.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/103/kirito_220-2.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/103/kirito_220-3.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/103/kirito_220-4.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/103/kirito_220-5.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/103/kirito_220-6.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.08);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("SaberDamagedEnd\n");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-3.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-4.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-5.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-6.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Saber/100/kirito_0-7.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
            toughCoef = 1.0;
            this->damage->v = 0;
            this->damage->deTough = 0;
        }, 0.8, "SaberLAnimeC");
        
        /*3刚体Completed*/
        this->move = 0;
        charaAppearance->body[0]->applyImpulse(cocos2d::Vec2((202 - this->facedirection) * this->mass * (this->legForce * 0.01 + 1), 0));
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
            charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(2 * (this->facedirection - 202) * this->mass * (this->legForce * 0.01 + 1), 0));
        }, 0.3, "SaberLForward");
    }

};
