#include "DontTouchWhiteBlock.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* DontTouchWhiteBlock::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = DontTouchWhiteBlock::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool DontTouchWhiteBlock::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	//随机种子
	srand(time(NULL));

	//可见大小
	visibleSize = Director::getInstance()->getVisibleSize();
	//创建一个层
	gameLayer = Node::create();
	addChild(gameLayer);
	timerLabel = Label::create();
	timerLabel->setTextColor(Color4B::BLUE);
	timerLabel->setSystemFontSize(48);
	timerLabel->setPosition(visibleSize.width / 2, visibleSize.height - 100);
	timerLabel->setString("0.000000");
	addChild(timerLabel);

	startGame();
	//创建事件监听器, 监听应用程序的touch
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch *t, Event *e) {  //catch this
		//遍历所有blocks
		auto bs = Block::getBlocks();
		Block *b;
		for (auto it = bs->begin(); it != bs->end(); it++) {
			b = *it;
			//只有行(hang)为1的情况下才执行判断, 并且和触摸点相碰撞
			//t->getLocation: 触摸到的坐标位置.  getBoundingBox(): 返回 AABB 轴对齐边界框在其父级的坐标系统
			if (b->getLineIndex() == 1 && b->getBoundingBox().containsPoint(t->getLocation())) {
				if (b->getColor() == Color3B::BLACK) {//如果点击的是黑块, 则所有块下移
					if (!timerRunning) {
						this->startTimer();
					}
					b->setColor(Color3B::GRAY);  //设置为灰色
					this->moveDown();
				}
				else if (b->getColor() == Color3B::GREEN) {
					this->moveDown();
					this->stopTimer();
				}
				else {
					MessageBox("Game Over！", "Failed");
				}
				break;
			}
		}
		return false;
	};
	//添加事件监听器
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

//添加开始行
void DontTouchWhiteBlock::addStartLine() {
	 //创建一个块
	auto b = Block::createWithArgs(Color3B::YELLOW, Size(visibleSize.width, visibleSize.height / 4), "", 20, Color4B::BLACK);
	gameLayer->addChild(b);
	//初始行索引为0
	b->setLineIndex(0);
}

void DontTouchWhiteBlock::addEndLine() {
	auto b = Block::createWithArgs(Color3B::GREEN, visibleSize, "Game Over", 32, Color4B::BLACK);
	gameLayer->addChild(b);
	//结束行索引为4, 从最上边向下移动的,所以为4
	b->setLineIndex(4);
}

void DontTouchWhiteBlock::addNormalLine(int lineIndex) {
	Block *b;
	int blackIndex = rand() % 4;
	for (int i = 0; i < 4; i++) {
		b = Block::createWithArgs(blackIndex == i ? Color3B::BLACK : Color3B::WHITE, Size(visibleSize.width / 4 - 2 , visibleSize.height / 4-1 ), "", 20, Color4B::BLACK);
		gameLayer->addChild(b);
		b->setPosition(i * visibleSize.width / 4, lineIndex * visibleSize.height / 4);
		//计数行索引
		b->setLineIndex(lineIndex);
	}
	//添加普通块行时
	linesCount++;
}

void DontTouchWhiteBlock::startGame() {
	//开始行数为0
	linesCount = 0;
	//开始没有呈现结束
	showEnd = false;

	timerRunning = false;

	//添加第一行, 开始行
	addStartLine();
	//添加第二行, 游戏行
	addNormalLine(1);
	//添加第三行
	addNormalLine(2);
	//添加第四行
	addNormalLine(3);
}

void DontTouchWhiteBlock::moveDown() {
	if (linesCount < 50) {
		addNormalLine(4);  //增加第四行
	}
	else if(!showEnd){
		addEndLine();
		showEnd = true;
	}
	auto bs = Block::getBlocks();
	for (auto it = bs->begin(); it != bs->end(); it++) {
		(*it)->moveDown();
	}
}

void DontTouchWhiteBlock::update(float dt) {
	//offset为微秒, 当前时间减掉开始的时间
	long offset = clock() - startTime;
	timerLabel->setString(StringUtils::format("%g", ((double)offset / 1000000)));  //offset为微秒，转换为秒

}

void DontTouchWhiteBlock::startTimer() {
	if (!timerRunning) {
		scheduleUpdate();
		startTime = clock();
		timerRunning = true;
	}
}

void DontTouchWhiteBlock::stopTimer() {
	if (timerRunning) {
		unscheduleUpdate();
		timerRunning = false;
	}
}