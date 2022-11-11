//
//  Monk.cpp
//  
//
//  Created by 結城朝日 on 2022/05/24.
//

#include "Monk.hpp"

void Monk::init(int border, int startX, int startY, float scale) {
    printf("MonkInit\n");
    
    /*1数值Completed*/
    damage = new Damage;
    attack = 80;
    defence = 1.7;
    toughness = 150;
    toughnessMax = 150;
    hp = 1000;
    hpMax = 1000;
    legForce = 3000;
    
    
    /*2动画Completed*/
    charaAppearance = new CharaSprite;
    charaAppearance->sprite = cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-0.png");
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
    }, 0.3, "MonkToughness");
    
    /*3刚体*/
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
    }, 1/30, "MonkMove");
    
    standby();

    
};

void Monk::keyW() {
    printf("MonkW\n");
    
    /*1数值Completed*/
    state = JUMP;
    toughCoef = 1.5;
    
    /*2动画*/
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/105/kyo_40-0.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/105/kyo_40-1.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/105/kyo_40-2.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/105/kyo_40-3.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/105/kyo_40-4.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/105/kyo_40-4.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/105/kyo_40-4.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/105/kyo_40-4.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/105/kyo_40-4.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/105/kyo_40-3.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/105/kyo_40-2.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/105/kyo_40-1.png")->getSpriteFrame());
    cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
    cocos2d::Animate * animate = cocos2d::Animate::create(animation);
    charaAppearance->sprite->stopAllActions();
    charaAppearance->sprite->runAction(animate);
    this->charaAppearance->sprite->scheduleOnce([=](float dt){
        state = STAND_BY;
        printf("MonkWEnd\n");
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-0.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-1.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-2.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-3.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-4.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-5.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-6.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-7.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-8.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-9.png")->getSpriteFrame());
        cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
        cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
    }, 1.2, "MonkWC");
    
    /*3刚体*/
    this->move = 0;
    charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(0, this->mass * (980 * 0.5 + 100)));//I=G△t+mv=m(g△t+v)
    
};

void Monk::keyS() {
    printf("MonkS\n");
   
    /*1数值Completed*/
    state = BEND_BODY;
    toughCoef = 0.5;
 
    /*2动画*/
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/104/kyo_50-0.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/104/kyo_50-1.png")->getSpriteFrame());
    cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.05);
    cocos2d::Animate * animate = cocos2d::Animate::create(animation);
    charaAppearance->sprite->stopAllActions();
    charaAppearance->sprite->runAction(animate);
    
    /*3刚体*/
    this->move = 0;
    
};

void Monk::keyA() {
    printf("MonkA\n");
   
    /*1数值Completed*/
    charaAppearance->sprite->setFlippedX(true);
    facedirection = FACEL;
    toughCoef = 1.0;
     
    /*2动画*/
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-0.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-1.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-2.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-3.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-4.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-5.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-6.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-7.png")->getSpriteFrame());
    cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
    cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
    charaAppearance->sprite->stopAllActions();
    charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
    
    /*3刚体*/
    charaAppearance->body[0]->applyForce(cocos2d::Vec2(-this->legForce * 150, 0));
    this->move = FACEL;
    forceCount++;

};

void Monk::keyD() {
    printf("MonkD\n");
    
    /*1数值Completed*/
    charaAppearance->sprite->setFlippedX(false);
    facedirection = FACER;
    toughCoef = 1.0;
    
    /*2动画*/
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-0.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-1.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-2.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-3.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-4.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-5.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-6.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/108/kyo_20-7.png")->getSpriteFrame());
    cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
    cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
    charaAppearance->sprite->stopAllActions();
    charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
    
    /*3刚体*/
    charaAppearance->body[0]->applyForce(cocos2d::Vec2(this->legForce * 150, 0));
    this->move = FACER;
    forceCount++;

};

void Monk::damaged(Damage * damage) {
    printf("MonkPVPDamaged");
    
    /*1数值Completed*/
    PlayableCharacter::damaged(damage);
    state = HURT;
    
    /*2动画*/
    if (hp == 0) {
        state = LOST;
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5032-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5032-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5042-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5042-10.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
    }
    else if (toughness == 0)
    {
        state = KNOCKED;
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5032-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5032-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5042-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5042-10.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5042-20.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5020-21.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5020-20.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5020-10.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5020-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5012-20.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5012-10.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5012-0.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(animate2);
        }, 1.4, "MonkKnockedAnimeC");
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("MonkWEnd");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames3;
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-0.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-1.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-2.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-3.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-4.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-5.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-6.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-7.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-8.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-9.png")->getSpriteFrame());
            cocos2d::Animation * animation3 = cocos2d::Animation::createWithSpriteFrames(sFrames3, 0.1);
            cocos2d::Animate * animate3 = cocos2d::Animate::create(animation3);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate3));
        }, 2.7, "MonkKnockedC");
    }
    else {
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/106/kyo_5000-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/106/kyo_5000-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/106/kyo_5000-20.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/106/kyo_5000-21.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/106/kyo_5000-22.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("MonkDamagedEnd\n");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-3.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-4.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-5.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-6.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-7.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-8.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-9.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        }, 0.5, "MonkDC");
    }
    
    /*3刚体*/
    this->move = 0;
    this->charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
    charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(2 * (202 - this->facedirection) * this->mass * (this->legForce * 0.01 + 1), 0));
    
};

void Monk::damaged(int damage) {
    printf("MonkPVEDamaged");
    
    /*1数值Completed*/
    PlayableCharacter::damaged(damage);
    
    /*2动画*/
    if (hp == 0) {
        state = LOST;
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5032-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5032-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5042-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5042-10.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
    }
    else if (toughness == 0)
    {
        state = KNOCKED;
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5032-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5032-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5042-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5042-10.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5042-20.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5020-21.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5020-20.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5020-10.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5020-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5012-20.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5012-10.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/107/kyo_5012-0.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(animate2);
        }, 1.4, "MonkKnockedAnimeC");
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("MonkWEnd");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames3;
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-0.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-1.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-2.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-3.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-4.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-5.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-6.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-7.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-8.png")->getSpriteFrame());
            sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-9.png")->getSpriteFrame());
            cocos2d::Animation * animation3 = cocos2d::Animation::createWithSpriteFrames(sFrames3, 0.1);
            cocos2d::Animate * animate3 = cocos2d::Animate::create(animation3);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate3));
        }, 2.7, "MonkKnockedC");
    }
    else {
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/106/kyo_5000-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/106/kyo_5000-10.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/106/kyo_5000-20.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/106/kyo_5000-21.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/106/kyo_5000-22.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("MonkDamagedEnd\n");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-3.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-4.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-5.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-6.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-7.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-8.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-9.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        }, 0.5, "MonkDC");
    }
    
    
    /*3刚体*/
    this->move = 0;
    this->charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
    
};

void Monk::standby(int stag) {
    printf("MonkStandBy\n");
    
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/104/kyo_50-1.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/104/kyo_50-0.png")->getSpriteFrame());
    cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.1);
    cocos2d::Animate * animate = cocos2d::Animate::create(animation);
    
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-0.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-1.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-2.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-3.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-4.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-5.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-6.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-7.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-8.png")->getSpriteFrame());
    sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-9.png")->getSpriteFrame());
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
                printf("MonkWEnd");
                cocos2d::Vector<cocos2d::SpriteFrame *> sFrames3;
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-0.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-1.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-2.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-3.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-4.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-5.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-6.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-7.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-8.png")->getSpriteFrame());
                sFrames3.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-9.png")->getSpriteFrame());
                cocos2d::Animation * animation3 = cocos2d::Animation::createWithSpriteFrames(sFrames3, 0.1);
                cocos2d::Animate * animate3 = cocos2d::Animate::create(animation3);
                charaAppearance->sprite->stopAllActions();
                charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate3));
            }, 0.2, "MonkBC");
        }
        else{
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        }
 
        this->state = STAND_BY;
    }
    
    /*2动画*///补在上面
    /*3刚体*/
    this->move = 0;
    if (this->forceCount != 0) {
        printf("Forces %d to 0\n", forceCount);
        charaAppearance->body[0]->resetForces();
        charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
        this->forceCount = 0;
    }
    
};

void Monk::attJ() {
    printf("MonkJ\n");
    
    /*1数值Completed*/
    state = J_SKILL;
    toughCoef = 1;
    float times = 1.2;
    this->damage->v = this->attack * times * this->attackBuff;
    this->damage->deTough = 40;
    
    /*2动画*/
    cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/101/kyo_200-0.png")->getSpriteFrame());
    sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/101/kyo_200-1.png")->getSpriteFrame());
    cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.2);
    cocos2d::Animate * animate = cocos2d::Animate::create(animation);
    charaAppearance->sprite->stopAllActions();
    charaAppearance->sprite->runAction(animate);
    this->charaAppearance->sprite->scheduleOnce([=](float dt){
        state = STAND_BY;
        printf("MonkDamagedEnd\n");
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-0.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-1.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-2.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-3.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-4.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-5.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-6.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-7.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-8.png")->getSpriteFrame());
        sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-9.png")->getSpriteFrame());
        cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
        cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        toughCoef = 1.0;
        this->damage->v = 0;
        this->damage->deTough = 0;
    }, 0.4, "MonkJC");
    
    /*3刚体*/
    this->move = 0;
    charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
    charaAppearance->body[0]->applyImpulse(cocos2d::Vec2((202 - this->facedirection) * this->mass * (this->legForce * 0.01 + 1), 0));
    this->charaAppearance->sprite->scheduleOnce([=](float dt){
        charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
        charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(1.5 * (this->facedirection - 202) * this->mass * (this->legForce * 0.01 + 1), 0));
    }, 0.1, "MonkJForward");
    
};

void Monk::attK() {
    printf("MonkK\n");

    if (this->sKReady == true) {
        /*1数值*/
        sKReady = false;
        state = K_SKILL;
        toughCoef = 1;
        this->attackBuff = 1.2;
        attackBuffCount ++;
        this->defenceBuff = 1.2;
        defenceBuffCount ++;
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            sKReady = true;
            printf("MonkKReady");
        }, 6, "MonkKC");
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            this->attackBuff = 1;
            attackBuffCount --;
            this->defenceBuff = 1;
            defenceBuffCount --;
            printf("MonkKDataend");
        }, 5, "MonkKDataC");
        
        /*2动画Completed*/
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/102/kyo_181-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/102/kyo_181-1.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/102/kyo_181-2.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/102/kyo_181-3.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/102/kyo_181-4.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/102/kyo_181-5.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/102/kyo_181-6.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/102/kyo_181-7.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.05);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("MonkDamagedEnd\n");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-3.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-4.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-5.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-6.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-7.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-8.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-9.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
        }, 0.8, "MonkKAnimeC");
        
        /*3刚体Completed*/
        this->move = 0;
        charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
        charaAppearance->body[0]->applyImpulse(cocos2d::Vec2((202 - this->facedirection) * this->mass * (this->legForce * 0.01 + 1), 0));
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
            charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(2 * (this->facedirection - 202) * this->mass * (this->legForce * 0.01 + 1), 0));
        }, 0.2, "MonkLForward");
    }
};

void Monk::attL() {
    printf("MonkL\n");
    
    if (this->sLReady == true) {
        /*1数值Completed*/
        sLReady = false;
        state = L_SKILL;
        toughCoef = 1;
        float times = 2;
        this->damage->v = this->attack * times * this->attackBuff;
        this->damage->deTough = 40;
        this->charaAppearance->sprite->scheduleOnce([=](float dt){sLReady = true;printf("MonkLReady");}, 12, "MonkLC");
     
        /*2动画Completed*/
        cocos2d::Vector<cocos2d::SpriteFrame *> sFrames;
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/103/kyo_210-0.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/103/kyo_210-1.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/103/kyo_210-2.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/103/kyo_210-3.png")->getSpriteFrame());
        sFrames.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/103/kyo_210-4.png")->getSpriteFrame());
        cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(sFrames, 0.08);
        cocos2d::Animate * animate = cocos2d::Animate::create(animation);
        charaAppearance->sprite->stopAllActions();
        charaAppearance->sprite->runAction(animate);
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            state = STAND_BY;
            printf("MonkDamagedEnd\n");
            cocos2d::Vector<cocos2d::SpriteFrame *> sFrames2;
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-0.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-1.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-2.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-3.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-4.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-5.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-6.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-7.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-8.png")->getSpriteFrame());
            sFrames2.pushBack(cocos2d::Sprite::create("/Users/touyamatsuoka/Documents/作业/2022.2/Cocos2dx/贵物大乱斗/Cocos2dx/Fight/Resources/Characters/Monk/100/kyo_0-9.png")->getSpriteFrame());
            cocos2d::Animation * animation2 = cocos2d::Animation::createWithSpriteFrames(sFrames2, 0.1);
            cocos2d::Animate * animate2 = cocos2d::Animate::create(animation2);
            charaAppearance->sprite->stopAllActions();
            charaAppearance->sprite->runAction(cocos2d::RepeatForever::create(animate2));
            toughCoef = 1.0;
            this->damage->v = 0;
            this->damage->deTough = 0;
        }, 0.5, "MonkLAnimeC");
        
        /*3刚体Completed*/
        this->move = 0;
        charaAppearance->body[0]->applyImpulse(cocos2d::Vec2((202 - this->facedirection) * this->mass * (this->legForce * 0.01 + 1), 0));
        this->charaAppearance->sprite->scheduleOnce([=](float dt){
            charaAppearance->body[0]->setVelocity(cocos2d::Vec2(0, 0));
            charaAppearance->body[0]->applyImpulse(cocos2d::Vec2(2 * (this->facedirection - 202) * this->mass * (this->legForce * 0.01 + 1), 0));
        }, 0.3, "MonkLForward");
    }
};
