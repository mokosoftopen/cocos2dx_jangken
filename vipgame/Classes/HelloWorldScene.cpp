#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

static Sprite* jangken_aite;
static CCAnimate* jangken_anime_run;
static LabelTTF* lbl_dis;

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    auto lbl_title = LabelTTF::create("じゃんけんゲーム", "HiraKakuProN-W6", 30);
    lbl_title->setPosition(Point(origin.x +visibleSize.width/2,
                                 origin.y +visibleSize.height - lbl_title->getContentSize().height ));
    this->addChild(lbl_title);
    
    // グーだけの単一スプライトを表示する
    jangken_aite = Sprite::create("goo.png");
    jangken_aite->setPosition(Point(origin.x+visibleSize.width/2,
                                    origin.y+visibleSize.height
                                    - lbl_title->getContentSize().height
                                    - jangken_aite->getContentSize().height
                                    -20));
    this->addChild(jangken_aite);
    
    // アニメーションを生成する
    auto jangken_anime = Animation::create();
    jangken_anime->addSpriteFrameWithFile("choki.png");
    jangken_anime->addSpriteFrameWithFile("par.png");
    jangken_anime->addSpriteFrameWithFile("goo.png");
    jangken_anime->setDelayPerUnit(0.1f);
    jangken_anime->setLoops(-1);
    jangken_anime->setRestoreOriginalFrame(true);
    jangken_anime_run = (CCAnimate*)CCSequence::create(
                                                CCAnimate::create(jangken_anime),
                                                NULL);
    // アニメーション実行
    jangken_aite->runAction(jangken_anime_run);
    
    
    
    // じゃんけんボタンを追加
    auto btn_goo = MenuItemImage::create("goo.png", "goo.png", CC_CALLBACK_1(HelloWorld::pushGoo, this));
    auto btn_choki = MenuItemImage::create("choki.png", "choki.png", CC_CALLBACK_1(HelloWorld::pushChoki, this));
    auto btn_par = MenuItemImage::create("par.png", "par.png", CC_CALLBACK_1(HelloWorld::pushPar, this));
    
    btn_goo->setPosition(Point(origin.x + btn_goo->getContentSize().width/2 + 10,
                               origin.y + visibleSize.height/2 - 20));
    
    btn_choki->setPosition(Point(btn_goo->getPosition().x + btn_choki->getContentSize().width + 10,
                               origin.y + visibleSize.height/2 - 20));
    
    btn_par->setPosition(Point(btn_choki->getPosition().x + btn_par->getContentSize().width + 10,
                               origin.y + visibleSize.height/2 - 20));
    
    
    auto btns = Menu::create(btn_goo, btn_choki, btn_par, NULL);
    btns->setPosition(Point::ZERO);
    this->addChild(btns);
    
    
    
    // 乱数を初期化
    srand((unsigned)time(NULL));
    
    lbl_dis = LabelTTF::create("", "HiraKakuProN-W6", 30);
    lbl_dis->setPosition(Point(origin.x + visibleSize.width/2,
                               origin.y + 200));
    addChild(lbl_dis);
    
    
    return true;
}


void HelloWorld::procJangken(int i)
{
    
    int rnd = rand() % 3 + 1;
    bool win = false;
    bool aiko = false;
    if ( rnd == 1 ) {
        if ( i == 1 ) {
            aiko = true;
        } else if ( i == 2 ) {
            win = true;
        }
    } else if ( rnd == 2 ) {
        if ( i == 2 ) {
            aiko = true;
        } else if ( i == 1 ) {
            win = true;
        }
    } else if ( rnd == 3 ) {
        if ( i == 3 ) {
            aiko = true;
        } else if ( i == 2 ) {
            win = true;
        }
    }
    
    // アニメーションをストップ
    jangken_aite->stopAllActions();
    if ( rnd == 1 ) {
        jangken_aite->setTexture(TextureCache::getInstance()->addImage("goo.png"));
    } else if ( rnd == 2 ) {
        jangken_aite->setTexture(TextureCache::getInstance()->addImage("choki.png"));
    } else if ( rnd == 3 ) {
        jangken_aite->setTexture(TextureCache::getInstance()->addImage("par.png"));
    }

    if ( aiko ) {
        lbl_dis->setString("あいこでしょ！");
    } else {
        if ( win ) {
            lbl_dis->setString("勝利！");
        } else {
            lbl_dis->setString("負け！");
        }
    }
    
}

void HelloWorld::pushGoo(Object *pSender)
{
    this->procJangken(1);
}

void HelloWorld::pushChoki(Object *pSender)
{
    this->procJangken(2);
}

void HelloWorld::pushPar(Object *pSender)
{
    this->procJangken(3);
}


void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
