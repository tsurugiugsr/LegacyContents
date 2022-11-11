//
//  Audio.hpp
//  Fight
//
//  Created by 松岡東矢 on 2022/05/30.
//

#ifndef Audio_hpp
#define Audio_hpp

#include <stdio.h>
#include <AudioEngine.h>

class Audio : public cocos2d::AudioEngine {
public:
    Audio();
    void playTitle();
    void playClick();
    void saberAttack();
    
};

#endif /* Audio_hpp */
