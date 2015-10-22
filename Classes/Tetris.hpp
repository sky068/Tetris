//
//  Tetris.hpp
//  testTable
//
//  Created by xujw on 15/10/20.
//
//  Brick : (_px,py) 表示在矩阵里的位置，会自动关联在屏幕上的实际坐标

#ifndef Tetris_hpp
#define Tetris_hpp

#include <stdio.h>
#include "cocos2d.h"


typedef enum class BrickType{
    tDefault = 0,
    tL = 1, //L型
    tT = 2, //田
    t1 = 3, //1字型
    tN = 4, //N字型
    tFl = 5, //反L
    tFn = 6, //反N
}tBrickType;

class Brick:public cocos2d::Sprite
{
public:
    Brick();
    ~Brick();
    inline void setPx(int x)
    {
        _px = x;
        this->setPositionX(1+this->getPx()*21);
    };
    inline void setPy(int y)
    {
        _py = y;
        this->setPositionY(1+this->getPy()*21);
    };
    inline int getPx(){return _px;};
    inline int getPy(){return _py;};
    static Brick* create();

    //存放矩阵的集合
    Brick* bList[4][4];
private:
    bool init();
    void initBlist();
    int _px;
    int _py;
};
    
class TetrisGameLayer:public cocos2d::Layer
{
public:
    TetrisGameLayer();
    ~TetrisGameLayer();
    bool init();
    CREATE_FUNC(TetrisGameLayer);
    static cocos2d::Scene* createTetrisScene();

private:
    std::vector<Brick*> createBricks(tBrickType type = tBrickType::tDefault);
    void initBgFrame();
    void addMenu();
    void onLeftCall(cocos2d::Ref*sender);
    void onRightCall(cocos2d::Ref*sender);
    void onDownCall(cocos2d::Ref*sender);
    void initMatrix();
    void update(float dt);
    Brick* _matrixPtr[10][24];  //10*20格子，加上每次生成4*4矩阵
    
    void createActiveNode();
    
    void checkClearRow();
    
    Brick *_activeNode;
    
    tBrickType _bType;
};

#endif /* Tetris_hpp */
