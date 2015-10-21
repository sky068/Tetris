#include "HelloWorldScene.h"

USING_NS_CC;

int rows = 5;   //3列  加两列为了流畅运转
int cols = 5;

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

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    _startSpin = false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    _bgNode = ClippingNode::create();
    Sprite *s = Sprite::create("room_1_item_1.png");
    LayerColor *stencil = LayerColor::create(Color4B::BLUE, s->getContentSize().width*cols, s->getContentSize().height*(rows-2));
    _bgNode->setStencil(stencil);
    this->addChild(_bgNode);
    _bgNode->setAlphaThreshold(1);
    
//    _bgNode->addChild(s);
//    s->setPosition(0,0);
    
    _colTime = (float*)calloc(cols, sizeof(int));
    _colTime[0] = 2;
    _colTime[1] = 4;
    _colTime[2] = 6;
    _colTime[3] = 8;
    _colTime[4] = 10;
    
    initTable();
    
    scheduleUpdate();
    
    
    return true;
}

void HelloWorld::initTable()
{
    _arrCol = __Array::create();
    _arrCol->retain();
    
    for (int i=0; i<cols; i++)
    {
        __Array *arrRow = __Array::create();
        for (int j=0; j<rows; j++)
        {
            std::string file = StringUtils::format("room_1_item_%d.png",j+1);
            Sprite *cell = Sprite::create(file);
            cell->setPosition(Vec2(25+i*cell->getContentSize().width,cell->getContentSize().height/2+j*cell->getContentSize().height));
            _bgNode->addChild(cell);
            arrRow->addObject(cell);
        }
        _arrCol->addObject(arrRow);
    }
}

void HelloWorld::update(float dt)
{
    if (_startSpin)
    {
        _allTime += dt;
        for (int i=0; i<cols; i++)
        {
            //每一列数据
            __Array * aCol = (__Array*)_arrCol->getObjectAtIndex(i);
            for (int j=0; j<rows; j++)
            {
                if (_allTime<_colTime[i])
                {
                    Sprite *cell = (Sprite*)aCol->getObjectAtIndex(j);
                    cell->setPositionY(cell->getPositionY()-10);
                }
            }
            
            Sprite *head = (Sprite*) aCol->getObjectAtIndex(0);
            if (head->getPositionY() <= -head->getContentSize().height/2)
            {
                Sprite *tail = (Sprite*) aCol->getObjectAtIndex(aCol->count()-1);
                head->setPositionY(tail->getPositionY()+tail->getContentSize().height);
                aCol->removeObjectAtIndex(0);
                aCol->addObject(head);
            }

        }
        
        
    }
    return;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    _startSpin = !_startSpin;
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}
