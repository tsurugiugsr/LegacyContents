//
//  Saber.hpp
//  Fight
//
//  Created by 松岡東矢 on 2022/05/24.
//

#ifndef Saber_hpp
#define Saber_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "PlayableCharacter.hpp"

using namespace std;

class Saber : public PlayableCharacter {
public:
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

#endif /* Saber_hpp */
