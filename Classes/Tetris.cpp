//
//  Tetris.cpp
//  testTable
//
//  Created by xujw on 15/10/20.
//  屏幕为320*480
//  每个小块为20*20像素 间隔为1像素 每次移动一个格子(21像素)
//  muatix 为10*20格子即200*400像素 序号为0,0--9,19
//

#include "Tetris.hpp"

Brick::Brick():_px(5),_py(20)
{
    
}
Brick::~Brick()
{
    
}

Brick* Brick::create(tBrickType type)
{
    Brick *brick = new (std::nothrow) Brick();
    if (brick && brick->initWithType(type))
    {
        brick->autorelease();
        return brick;
    }
    CC_SAFE_DELETE(brick);
    return nullptr;
}

bool Brick::initWithType(tBrickType type)
{
    if (!cocos2d::Sprite::init())
    {
        
        return false;
    }
    
//    cocos2d::DrawNode *node = cocos2d::DrawNode::create();
//    node->drawRect(cocos2d::Vec2(0,0), cocos2d::Vec2(20,20), cocos2d::Color4F::YELLOW);
//    this->addChild(node);
    this->setColor(cocos2d::Color3B::BLACK);
    this->setTextureRect(cocos2d::Rect(0,0,20,20));
    this->setAnchorPoint(cocos2d::Vec2(0,0));
    
    return true;
}

#pragma mark--+++++game layer+++++++

TetrisGameLayer::TetrisGameLayer():_activeNode(nullptr)
{
    
}
TetrisGameLayer::~TetrisGameLayer()
{
    
}

cocos2d::Scene* TetrisGameLayer::createTetrisScene()
{
    cocos2d::Scene* scene = cocos2d::Scene::create();
    TetrisGameLayer* layer = TetrisGameLayer::create();
    scene->addChild(layer);
    return scene;
}

bool TetrisGameLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //bg color
    auto layercolor = cocos2d::LayerColor::create(cocos2d::Color4B::GRAY);
    this->addChild(layercolor);
   
    initMatrix();
    //游戏框
    initFrame();
    
    addMenu();
    
    createActiveNode();
    
//    for (int i=0; i<10; i++) {
//        Brick *b = Brick::create();
//        b->setPosition(1+i*21,1);
//        this->addChild(b);
//    }
    
    
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](cocos2d::Touch *touch,cocos2d::Event *event)
    {
        return true;
    };
    listener->onTouchEnded = [](cocos2d::Touch *touch,cocos2d::Event *event)
    {
        cocos2d::log("x:%f,y:%f",touch->getLocation().x,touch->getLocation().y);
    };
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    schedule(std::bind(&TetrisGameLayer::update, this,std::placeholders::_1),0.5, "update");
    
    return true;
}

void TetrisGameLayer::initFrame()
{
    cocos2d::DrawNode *node = cocos2d::DrawNode::create();
    node->drawRect(cocos2d::Vec2(1,1), cocos2d::Vec2(211,421), cocos2d::Color4F::BLUE);
    this->addChild(node);
    
    return;
}

void TetrisGameLayer::addMenu()
{
    cocos2d::MenuItemFont *downItem = cocos2d::MenuItemFont::create("Down",std::bind(&TetrisGameLayer::onDownCall, this,std::placeholders::_1));
    downItem->setPosition(270,30);
    cocos2d::MenuItemFont *leftItem = cocos2d::MenuItemFont::create("L",std::bind(&TetrisGameLayer::onLeftCall, this,std::placeholders::_1));
    leftItem->setPosition(250,80);
    cocos2d::MenuItemFont *rightItem = cocos2d::MenuItemFont::create("R",std::bind(&TetrisGameLayer::onRightCall, this,std::placeholders::_1));
    rightItem->setPosition(290,80);
    
    cocos2d::Menu *menu = cocos2d::Menu::create(downItem,leftItem,rightItem, NULL);
    menu->setPosition(0,0);
    this->addChild(menu);

    return;
}

void TetrisGameLayer::initMatrix()
{
//    for (int i=0; i<10; i++)
//    {
//        for (int j=0; j<21; j++)
//        {
//            _matrix[i][j] = 0;
//        }
//    }
    
    for (int i=0; i<10; i++)
    {
        for (int j=0; j<21; j++)
        {
            _matrixPtr[i][j] = nullptr;
        }
    }
    
    return;
}

void TetrisGameLayer::onDownCall(cocos2d::Ref *sender)
{
    cocos2d::log("to down");
    schedule(std::bind(&TetrisGameLayer::update, this,std::placeholders::_1),0.05, "update");

    return;
}

void TetrisGameLayer::onLeftCall(cocos2d::Ref *sender)
{
    cocos2d::log("to left");
    if (_activeNode)
    {
        if (_activeNode->getPx()>0 && _matrixPtr[_activeNode->getPx()-1][_activeNode->getPy()]==nullptr)
        {
//            _matrix[_activeNode->getPx()][_activeNode->getPy()]=0;
//            _matrix[_activeNode->getPx()-1][_activeNode->getPy()]=1;
            _matrixPtr[_activeNode->getPx()][_activeNode->getPy()]=nullptr;
            _matrixPtr[_activeNode->getPx()-1][_activeNode->getPy()]=_activeNode;
            _activeNode->setPx(_activeNode->getPx()-1);
            _activeNode->setPosition(1+_activeNode->getPx()*21,1+_activeNode->getPy()*21);
            
        }
    }
    
    return;
}

void TetrisGameLayer::onRightCall(cocos2d::Ref *sender)
{
    cocos2d::log("to right");
    if (_activeNode)
    {
        if (_activeNode->getPx()<9 && _matrixPtr[_activeNode->getPx()+1][_activeNode->getPy()]==nullptr)
        {
//            _matrix[_activeNode->getPx()][_activeNode->getPy()]=0;
//            _matrix[_activeNode->getPx()+1][_activeNode->getPy()]=1;
            _matrixPtr[_activeNode->getPx()][_activeNode->getPy()]=nullptr;
            _matrixPtr[_activeNode->getPx()+1][_activeNode->getPy()]=_activeNode;
            _activeNode->setPx(_activeNode->getPx()+1);
            _activeNode->setPosition(1+_activeNode->getPx()*21,1+_activeNode->getPy()*21);
            
        }
    }
    
    return;
}

void TetrisGameLayer::createActiveNode()
{
    schedule(std::bind(&TetrisGameLayer::update, this,std::placeholders::_1),0.5, "update");

    _activeNode = Brick::create();
    this->addChild(_activeNode);
    _activeNode->setPosition(1+_activeNode->getPx()*21,1+_activeNode->getPy()*21);
    
    return;
}

void TetrisGameLayer::update(float dt)
{
    if (_activeNode->getPy()>0 && _matrixPtr[_activeNode->getPx()][_activeNode->getPy()-1]==nullptr)
    {
//        _matrix[_activeNode->getPx()][_activeNode->getPy()]=0;
//        _matrix[_activeNode->getPx()][_activeNode->getPy()-1]=1;
        
        _matrixPtr[_activeNode->getPx()][_activeNode->getPy()]=nullptr;
        _matrixPtr[_activeNode->getPx()][_activeNode->getPy()-1]=_activeNode;
        
        _activeNode->setPy(_activeNode->getPy()-1);
        _activeNode->setPosition(1+_activeNode->getPx()*21,1+_activeNode->getPy()*21);
        
    }
    else
    {
        if (_matrixPtr[_activeNode->getPx()][19] != nullptr)
        {
            cocos2d::log("game over");
            unscheduleAllCallbacks();
        }
        else
        {
            checkClearRow();
            createActiveNode();
        }
    }
    
    return;
}

void TetrisGameLayer::checkClearRow()
{
    //查看每一行的情况
    for(int j=0;j<20;j++)
    {
        //从下至上一行一行遍历
        int count = 0;
        for (int i=0; i<10; i++)
        {
            if (_matrixPtr[i][j] != nullptr)
            {
                count++;
            }
        }
        
        if (count == 10)
        {
            //移除一行
            for (int i=0; i<10; i++)
            {
                _matrixPtr[i][j]->removeFromParent();
                _matrixPtr[i][j]=nullptr;
            }
            //上面所有的砖块向下移动一格
            for (int i=0; i<10; i++) {
                for (int j=1; j<20; j++)
                {
                    if (_matrixPtr[i][j])
                    {
                        _matrixPtr[i][j]->setPy(_matrixPtr[i][j]->getPy()-1);
                        _matrixPtr[i][j]->setPosition(1+_matrixPtr[i][j]->getPx()*21,1+_matrixPtr[i][j]->getPy()*21);
                        
                        _matrixPtr[i][j-1]=_matrixPtr[i][j];
                        _matrixPtr[i][j]=nullptr;
                    }
                }
            }
            //重新从最下一行开始遍历
            j=0;
        }
    }
    
    
    return;
}


