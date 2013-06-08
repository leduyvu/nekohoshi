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
        _catNum++;
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
    newPole->setScale(1.5);
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
    cat->setScale(1.5);
    
    float minX = cat->getContentSize().width/2 + 25;
    float maxX = winSize.width - cat->getContentSize().width/2 - 25;
    float rangeX = maxX - minX;
    float actualX = (float)rand()/((float)RAND_MAX/rangeX)+minX;
    
    float minY = 25;
    float maxY = winSize.height*3/7;
    cat->setPosition(ccp(actualX , minY));
    
    int minDuration = (int)1.0;
    int maxDuration = (int)3.0;
    int rangeDuration   = maxDuration - minDuration;
    float actualDuration  = (float)rand()/((float)RAND_MAX/rangeDuration) +
                            minDuration;
    
    CCFiniteTimeAction* moveRight =
    CCMoveTo::create(actualDuration, ccp(maxX, minY));
    moveRight->setTag(10);
    CCFiniteTimeAction *moveUp =
    CCMoveTo::create(actualDuration/4,ccp(maxX, maxY));
    moveUp->setTag(10);
    CCFiniteTimeAction *moveLeft =
    CCMoveTo::create(actualDuration,ccp(minX, maxY));
    moveLeft->setTag(10);
    CCFiniteTimeAction *moveDown =
    CCMoveTo::create(actualDuration/4,ccp(minX, minY));
    moveDown->setTag(10);
    
    CCFiniteTimeAction *goRightAnimation =
    CCCallFuncN::create(this, callfuncN_selector(HelloWorld::toRightBottom));
    CCFiniteTimeAction *goUpAnimation =
    CCCallFuncN::create(this, callfuncN_selector(HelloWorld::toRightTop));
    CCFiniteTimeAction *goLeftAnimation =
    CCCallFuncN::create(this, callfuncN_selector(HelloWorld::toLeftTop));
    CCFiniteTimeAction *goDownAnimation =
    CCCallFuncN::create(this, callfuncN_selector(HelloWorld::toLeftBottom));
    
    
    CCFiniteTimeAction* moveForever =
        CCRepeatForever::create(CCSequence::create(goRightAnimation, moveRight,
                                                   goUpAnimation, moveUp,
                                                   goLeftAnimation, moveLeft,
                                                   goDownAnimation, moveDown,
                                                   NULL));
    
    cat->runAction(moveForever);
    this->addChild(cat, 2);
    _cats->addObject(cat);
}


void HelloWorld::toRightBottom(CCSprite *cat) {
    cat->stopActionByTag(11);
    CCSpriteFrameCache *catRight = CCSpriteFrameCache::sharedSpriteFrameCache();
    catRight->addSpriteFramesWithFile("orangeCatRight.plist");
    CCArray *catRightFrames = CCArray::createWithCapacity(4);
    char str[100];
    for (int i = 5; i<= 8; i++) {
        sprintf(str, "CatSide%d.png", i);
        CCSpriteFrame *catRightFrame = catRight->spriteFrameByName(str);
        catRightFrames->addObject(catRightFrame);
    }
    
    CCAnimation *catRightAnim =
    CCAnimation::createWithSpriteFrames(catRightFrames, 0.1f);
    CCFiniteTimeAction *catRightAnimate =
    CCRepeatForever::create(CCAnimate::create(catRightAnim));
    catRightAnimate->setTag(11);
    cat->runAction(catRightAnimate);
}

void HelloWorld::toRightTop(CCSprite *cat) {
    cat->stopActionByTag(11);
    CCSpriteFrameCache *catUp = CCSpriteFrameCache::sharedSpriteFrameCache();
    catUp->addSpriteFramesWithFile("orangeCatBack.plist");
    CCArray *catUpFrames = CCArray::createWithCapacity(4);
    char str[100];
    for (int i = 1; i<= 4; i++) {
        sprintf(str, "CatBack%d.png", i);
        CCSpriteFrame *catUpFrame = catUp->spriteFrameByName(str);
        catUpFrames->addObject(catUpFrame);
    }
    
    CCAnimation *catUpAnim =
    CCAnimation::createWithSpriteFrames(catUpFrames, 0.1f);
    CCFiniteTimeAction *catUpAnimate =
    CCRepeatForever::create(CCAnimate::create(catUpAnim));
    catUpAnimate->setTag(11);
    cat->runAction(catUpAnimate);
}

void HelloWorld::toLeftTop(CCSprite *cat) {
    cat->stopActionByTag(11);
    CCSpriteFrameCache *catLeft = CCSpriteFrameCache::sharedSpriteFrameCache();
    catLeft->addSpriteFramesWithFile("orangeCatLeft.plist");
    CCArray *catLeftFrames = CCArray::createWithCapacity(4);
    char str[100];
    for (int i = 1; i<= 4; i++) {
        sprintf(str, "CatSide%d.png", i);
        CCSpriteFrame *catLeftFrame = catLeft->spriteFrameByName(str);
        catLeftFrames->addObject(catLeftFrame);
    }
    
    CCAnimation *catLeftAnim =
    CCAnimation::createWithSpriteFrames(catLeftFrames, 0.1f);
    CCFiniteTimeAction *catLeftAnimate =
    CCRepeatForever::create(CCAnimate::create(catLeftAnim));
    catLeftAnimate->setTag(11);
    cat->runAction(catLeftAnimate);
}

void HelloWorld::toLeftBottom(CCSprite *cat) {
    cat->stopActionByTag(11);
    CCSpriteFrameCache *catDown = CCSpriteFrameCache::sharedSpriteFrameCache();
    catDown->addSpriteFramesWithFile("orangeCatFront.plist");
    CCArray *catDownFrames = CCArray::createWithCapacity(4);
    char str[100];
    for (int i = 1; i<= 4; i++) {
        sprintf(str, "CatFront%d.png", i);
        CCSpriteFrame *catDownFrame = catDown->spriteFrameByName(str);
        catDownFrames->addObject(catDownFrame);
    }
    
    CCAnimation *catDownAnim =
    CCAnimation::createWithSpriteFrames(catDownFrames, 0.1f);
    CCFiniteTimeAction *catDownAnimate =
    CCRepeatForever::create(CCAnimate::create(catDownAnim));
    catDownAnimate->setTag(11);
    cat->runAction(catDownAnimate);
}

void HelloWorld::struggle(CCSprite *cat){
    cat->stopActionByTag(11);
    CCSpriteFrameCache *catStruggle = CCSpriteFrameCache::sharedSpriteFrameCache();
    catStruggle->addSpriteFramesWithFile("orangeCatGrab.plist");
    CCArray *catStruggleFrames = CCArray::createWithCapacity(2);
    
    CCSpriteFrame *catGrab = catStruggle->spriteFrameByName("CatGrab.png");
    CCSpriteFrame *catHang = catStruggle->spriteFrameByName("CatHang.png");
    catStruggleFrames->addObject(catGrab);
    catStruggleFrames->addObject(catHang);
    
    CCAnimation *catStruggleAnim =
    CCAnimation::createWithSpriteFrames(catStruggleFrames, 0.1f);
    CCFiniteTimeAction *catStruggleAnimate =
    CCRepeatForever::create(CCAnimate::create(catStruggleAnim));
    catStruggleAnimate->setTag(11);
    cat->runAction(catStruggleAnimate);

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
            _cats->removeObject(it);
            this->removeChild(cat);
            _catNum--;
            CCLOG("%d", _catNum);
        }
    }
    
    if (_catNum < 3) {
        int catToAdd = rand() % 5 + 1;
        for (int i=0; i<catToAdd; i++){
            addCats();
            _catNum++;
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
            _pickedCat = it;
        }

    }
}

void HelloWorld::ccTouchesMoved(CCSet* touches, CCEvent* event){
    CCTouch *touch = (CCTouch *)touches->anyObject();
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    if (_catPicked){
        CCSprite *cat = dynamic_cast<CCSprite *>(_pickedCat);
        cat->stopAllActions();
        CCFiniteTimeAction *catStruggle=
        CCCallFuncN::create(this, callfuncN_selector(HelloWorld::struggle));
        cat->runAction(CCSequence::create(catStruggle, NULL));
        cat->setPosition(location);
    }
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event){
    _catHanging = false;
    _catFalling = false;

    if (_catPicked) {
        CCSprite *cat = dynamic_cast<CCSprite *>(_pickedCat);
        CCObject *it = NULL;

        CCARRAY_FOREACH(_poles, it) {
            CCSprite *pole = dynamic_cast<CCSprite *>(it);
            CCRect catRect = cat->boundingBox();
            CCRect poleRect = pole->boundingBox();
            if (catRect.intersectsRect(poleRect)) {
                _catHanging = true;
                _hangingCatIndex = _cats->indexOfObject(_pickedCat);
                CCFiniteTimeAction* toHang =
                CCMoveTo::create(0.1,
                                 ccp(cat->getPositionX(),
                                     winSize.height*4/5));
                float actualMoveDuration =
                (winSize.width - cat->getPositionX()+ cat->getContentSize().width)/60;
                CCFiniteTimeAction* moveOut =
                CCMoveTo::create(actualMoveDuration,
                                 ccp(winSize.width + cat->getContentSize().width,
                                     winSize.height*4/5));
                
                cat->stopAllActions();
                cat->runAction(CCSequence::create(toHang, moveOut, NULL));
                break;
            }
        }
        if (!_catHanging) {
            float actualFallDuration = cat->getPositionY()/winSize.height;
            float actualMoveDuration = 2 * (winSize.width - cat->getPositionX())/winSize.width;
            
            CCFiniteTimeAction* fallDown =
            CCMoveTo::create(actualFallDuration,
                             ccp(cat->getPositionX(),
                                 cat->getContentSize().height/2));
            CCFiniteTimeAction *flipRight =
            CCCallFuncN::create(this, callfuncN_selector(HelloWorld::toRightBottom));
            CCFiniteTimeAction* moveOut =
            CCMoveTo::create(actualMoveDuration,
                             ccp(winSize.width + cat->getContentSize().width,
                                 cat->getContentSize().height/2));
            
            CCFiniteTimeAction *runAway = CCSequence::create(fallDown, flipRight, moveOut, NULL);
            cat->stopAllActions();
            cat->runAction(runAway);

        }

    }
    
    _catPicked  = false;
}


