//
//  Monk.hpp
//  
//
//  Created by 結城朝日 on 2022/05/24.
//

#ifndef Monk_hpp
#define Monk_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "PlayableCharacter.hpp"

using namespace std;

class Monk : public PlayableCharacter {
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

#endif /* Monk_hpp */
