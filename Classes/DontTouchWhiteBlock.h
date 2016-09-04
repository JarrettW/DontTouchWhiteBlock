#ifndef _DONT_TOUCH_WHITE_BLOCK_H_
#define _DONT_TOUCH_WHITE_BLOCK_H_

#include "cocos2d.h"
#include "Block.h"
USING_NS_CC;
class DontTouchWhiteBlock : public cocos2d::Layer
{
private:
	//可见大小
	Size visibleSize;
	//此时呈现的行数
	int linesCount;
	//是否呈现结束行
	bool showEnd;
	//呈现时间
	Label *timerLabel;
	//分层: 块和时间label的层
	Node *gameLayer;
	//时间是否在运行
	bool timerRunning;
	//游戏消耗的时间
	long startTime;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(DontTouchWhiteBlock);

	//添加开始行
	void addStartLine();
	//添加结束行
	void addEndLine();
	//添加黑白块行，即普通的每一行
	void addNormalLine(int lineIndex);

	//开始游戏方法
	void startGame();
	//下移操作
	void moveDown();

	//开始计时
	void startTimer();
	//结束计时
	void stopTimer();

	//计时更新
	virtual void update(float dt);
};

#endif // _DONT_TOUCH_WHITE_BLOCK_H_
