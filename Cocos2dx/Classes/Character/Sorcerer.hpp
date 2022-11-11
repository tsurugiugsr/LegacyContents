//
//  Sorcerer.hpp
//  
//
//  Created by 結城朝日 on 2022/05/24.
//

#ifndef Sorcerer_hpp
#define Sorcerer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "PlayableCharacter.hpp"

using namespace std;

class Sorcerer : public PlayableCharacter{
public:
    bool sJReady = true;
    void init(int border, int startX, int startY, float scale);
    void keyW();
    void keyS();
    void keyA();
    void keyD();
    void damaged(Damage * damage);
    void damaged(int damage);
    void standby(int stag = 0);
    void attJ();
    void attK();
    void attL();
};

#endif /* Sorcerer_hpp */
