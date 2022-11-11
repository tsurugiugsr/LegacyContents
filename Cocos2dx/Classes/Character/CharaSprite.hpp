//
//  CharaSprite.hpp
//  
//
//  Created by 結城朝日 on 2022/05/24.
//

#ifndef CharaSprite_hpp
#define CharaSprite_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace std;

class CharaSprite {
public:
    cocos2d::Sprite *sprite;
    cocos2d::PhysicsBody *body[3];
    int border = 0;
};

#endif /* CharaSprite_hpp */
