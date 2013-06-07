#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{


    if ( !CCLayerColor::initWithColor(ccc4(200, 200, 200, 200)))
    {
        return false;
    }
    
    this->setTouchEnabled(true);
    
    CCSprite *background_img = CCSprite::create("gallery_29_107_15317.jpg");
    background_img->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background_img);
    
    CCLabelTTF* pLabel = CCLabelTTF::create("猫ほし", "Thonburi", 34);
    pLabel->setPosition( ccp(winSize.width / 2, winSize.height - 20) );
    this->addChild(pLabel, 1);
    
    CCSprite *pole1 =  CCSprite::create("ShortBlack.png");
    float w1 = pole1->getContentSize().width;
    _poleNum = (int)(winSize.width/w1)+5;
    int currentPos = winSize.width;
    for (int i=1; i<_poleNum; i++) {
        CCSprite *pole = createPole();
        currentPos -= pole->getContentSize().width/2;
        pole->setPosition(ccp(currentPos, winSize.height * 4 / 5));
        currentPos -= pole->getContentSize().width/2;
        _poles->addObject(pole);
        this->addChild(pole);
    }
        
    for (int i = 0; i< 5; i++) {
        addCats();
    }
    
    
    this->schedule(schedule_selector(HelloWorld::update));
    return true;
}

CCSprite *HelloWorld::createPole() {
    char poleColor[4][20];
    char poleLong[2][20];
    
    strcpy(poleColor[0], "Red");
    strcpy(poleColor[1], "Orange");
    strcpy(poleColor[2], "Black");
    strcpy(poleColor[3], "White");
    
    strcpy(poleLong[0], "Short");
    strcpy(poleLong[1], "Long");
    
    int i = rand() % 2;
    int j = rand() % 4;
    
    char str[100];
    sprintf(str, "%s%s.png", poleLong[i], poleColor[j]);
    
    CCSprite *newPole = CCSprite::create(str);
    return newPole;
}

void HelloWorld::addPole() {
    CCSprite *newPole = createPole();
    
    CCSprite *lastPole = dynamic_cast<CCSprite *>(_poles->lastObject());
    
    float lastPolePosX = lastPole->getPositionX();
    float lastPoleWidth = lastPole->getContentSize().width;
    float newPoleWidth = newPole->getContentSize().width;
    newPole->setPosition(ccp(lastPolePosX -
                             (newPoleWidth + lastPoleWidth) / 2,
                                winSize.height * 4 / 5));
    
    this->addChild(newPole);
    _poles->addObject(newPole);
    
}

void HelloWorld::addCats() {
    CCSprite *cat = CCSprite::create();
    
    char str[100];
    
    CCSpriteFrameCache *catRight = CCSpriteFrameCache::sharedSpriteFrameCache();
    catRight->addSpriteFramesWithFile("orangeCatRight.plist");
    CCArray *catRightFrames = CCArray::createWithCapacity(4);
    
    for (int i = 5; i<= 8; i++) {
        sprintf(str, "CatSide%d.png", i);
        CCSpriteFrame *catRightFrame = catRight->spriteFrameByName(str);
        catRightFrames->addObject(catRightFrame);
    }
    
    CCAnimation *catRightAnim =
    CCAnimation::createWithSpriteFrames(catRightFrames, 0.1f);
    CCFiniteTimeAction *catRightAnimate =
    CCRepeatForever::create(CCAnimate::create(catRightAnim));
    cat->runAction(catRightAnimate);
    
    float actualX = (rand() % 100) + 50;
    float actualY = rand() % 10 + 25;
    cat->setPosition(ccp(actualX , actualY));
    
    int minDuration = (int)2.0;
    int maxDuration = (int)6.0;
    int rangeDuration   = maxDuration - minDuration;
    float actualDuration  = (float)rand()/((float)RAND_MAX/rangeDuration) +
                            minDuration;
    
    CCFiniteTimeAction* moveRight =
    CCMoveTo::create(actualDuration,
                     ccp(winSize.width - cat->getContentSize().width/2 -10, actualY));
    moveRight->setTag(1);
    CCFiniteTimeAction *moveLeft =
    CCMoveTo::create(actualDuration,ccp(cat->getContentSize().width/2 + 10, actualY));
    moveLeft->setTag(2);
    
    CCFiniteTimeAction *catFlipTrue = CCFlipX::create(true);
    CCFiniteTimeAction *catFlipFalse = CCFlipX::create(false);
    CCFiniteTimeAction* moveForever =
        CCRepeatForever::create(CCSequence::create(moveRight,
                                                   catFlipTrue,
                                                   moveLeft,
                                                   catFlipFalse,
                                                   NULL));
    moveForever->setTag(999);
    
    cat->runAction(moveForever);
    this->addChild(cat, 2);
    _cats->addObject(cat);
}

void HelloWorld::checkCats() {
    int catNum = _cats->count();
    if (catNum < 4) {
        int catToAdd = rand() % 3;
        for (int i=0; i<=catToAdd; i++){
            addCats();
        }
    }
}

void HelloWorld::update(float dt) {
    CCObject *it = NULL;
        
    CCARRAY_FOREACH(_poles, it) {
        CCSprite *pole = dynamic_cast<CCSprite *>(it);
        float currentPosX = pole->getPositionX();
        if (currentPosX > winSize.width + 200) {
            _poles->removeObject(it);
            this->removeChild(pole);
        } else {
            pole->setPositionX(currentPosX + dt * 60);
        }
    }
    CCARRAY_FOREACH(_cats, it) {
        CCSprite *cat = dynamic_cast<CCSprite *>(it);
        float currentPosX = cat->getPositionX();
        if (currentPosX > winSize.width) {
            checkCats();
            _cats->removeObject(it);
            this->removeChild(cat);
        }
    }
    
    if (_poles->count() < _poleNum) addPole();
}

void HelloWorld::ccTouchesBegan(CCSet *touches, CCEvent *event) {
    CCTouch *touch = (CCTouch *)touches->anyObject();
    CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
    
    CCObject *it = NULL;
    CCARRAY_FOREACH(_cats, it) {
        CCSprite *cat = dynamic_cast<CCSprite *>(it);
        CCRect catRect = cat->boundingBox();
        if (catRect.containsPoint(touchLoc) && !_catPicked) {
            cat->stopActionByTag(999);
            _catPicked = true;
            _pickedCatIndex = _cats->indexOfObject(it);
        }

    }
}

void HelloWorld::ccTouchesMoved(CCSet* touches, CCEvent* event){
    CCTouch *touch = (CCTouch *)touches->anyObject();
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    if (_catPicked){
        CCObject *it = _cats->objectAtIndex(_pickedCatIndex);
        CCSprite *cat = dynamic_cast<CCSprite *>(it);
        cat->setPosition(location);
    }
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event){
    _catHanging = false;
    _catFalling = false;

    if (_catPicked) {
        CCObject *jt = _cats->objectAtIndex(_pickedCatIndex);
        CCSprite *cat = dynamic_cast<CCSprite *>(jt);
        CCObject *it = NULL;

        CCARRAY_FOREACH(_poles, it) {
            CCSprite *pole = dynamic_cast<CCSprite *>(it);
            CCRect catRect = cat->boundingBox();
            CCRect poleRect = pole->boundingBox();
            if (catRect.intersectsRect(poleRect)) {
                _catHanging = true;
                _hangingCatIndex = _cats->indexOfObject(jt);
                float actualMoveDuration =
                (winSize.width - cat->getPositionX()+ cat->getContentSize().width)/60;
                CCFiniteTimeAction* moveOut =
                CCMoveTo::create(actualMoveDuration,
                                 ccp(winSize.width + cat->getContentSize().width,
                                     winSize.height*4/5));
                
                cat->stopAllActions();
                cat->runAction(moveOut);
                
                break;
            }
        }
        if (!_catHanging) {
            float actualFallDuration = 2 * cat->getPositionY()/winSize.height;
            float actualMoveDuration = 2 * (winSize.width - cat->getPositionX())/winSize.width;
            
            CCFiniteTimeAction *noFlip =  CCFlipX::create(false);
            CCFiniteTimeAction* fallDown =
            CCMoveTo::create(actualFallDuration,
                             ccp(cat->getPositionX(),
                                 cat->getContentSize().height/2));
            CCFiniteTimeAction* moveOut =
            CCMoveTo::create(actualMoveDuration,
                             ccp(winSize.width + cat->getContentSize().width,
                                 cat->getContentSize().height/2));
            
            CCFiniteTimeAction *runAway = CCSequence::create(fallDown, noFlip, moveOut, NULL);
            
            cat->runAction(runAway);
        }

    }
    
    _catPicked  = false;
}


