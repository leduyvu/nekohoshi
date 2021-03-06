#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::CCLayerColor
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    void addPole();
    void addCats();
    void checkCats();
    
    void toRightBottom(CCSprite *cat);
    void toRightTop(CCSprite *cat);
    void toLeftTop(CCSprite *cat);
    void toLeftBottom(CCSprite *cat);
    void struggle(CCSprite *cat);
    
    
    CCSprite *createPole();
    
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    void update(float dt);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
private:
    CCSize winSize  = CCDirector::sharedDirector()->getWinSize();
    CCArray *_poles = new CCArray;
    CCArray *_cats  = new CCArray;
    
    CCLabelTTF *scoreNum;
    
    int _poleNum;
    int _score = 0;

    bool _catPicked = false;
    CCObject *_pickedCat;
    int _pickedCatIndex;
    
    bool _catHanging = false;
    int _hangingCatIndex;
    
    bool _catFalling = false;
    int _fallingCatIndex;

};

#endif // __HELLOWORLD_SCENE_H__
