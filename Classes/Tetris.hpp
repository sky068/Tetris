//
//  Tetris.hpp
//  testTable
//
//  Created by xujw on 15/10/20.
//
//

#ifndef Tetris_hpp
#define Tetris_hpp

#include <stdio.h>
#include "cocos2d.h"


typedef enum class BrickType{
    tDefault = 0
}tBrickType;

class Brick:public cocos2d::Sprite
{
public:
    Brick();
    ~Brick();
    CC_SYNTHESIZE(int, _px, Px);
    CC_SYNTHESIZE(int, _py, Py);
    static Brick* create(tBrickType type = tBrickType::tDefault);
private:
    bool initWithType(tBrickType type);
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
    void initFrame();
    void addMenu();
    void onLeftCall(cocos2d::Ref*sender);
    void onRightCall(cocos2d::Ref*sender);
    void onDownCall(cocos2d::Ref*sender);
    void initMatrix();
    void update(float dt);
    int _matrix[10][21];
    Brick* _matrixPtr[10][21];
    
    void createActiveNode();
    
    void checkClearRow();
    
    Brick *_activeNode;
};

#endif /* Tetris_hpp */
