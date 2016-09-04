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
	//�������
	srand(time(NULL));

	//�ɼ���С
	visibleSize = Director::getInstance()->getVisibleSize();
	//����һ����
	gameLayer = Node::create();
	addChild(gameLayer);
	timerLabel = Label::create();
	timerLabel->setTextColor(Color4B::BLUE);
	timerLabel->setSystemFontSize(48);
	timerLabel->setPosition(visibleSize.width / 2, visibleSize.height - 100);
	timerLabel->setString("0.000000");
	addChild(timerLabel);

	startGame();
	//�����¼�������, ����Ӧ�ó����touch
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch *t, Event *e) {  //catch this
		//��������blocks
		auto bs = Block::getBlocks();
		Block *b;
		for (auto it = bs->begin(); it != bs->end(); it++) {
			b = *it;
			//ֻ����(hang)Ϊ1������²�ִ���ж�, ���Һʹ���������ײ
			//t->getLocation: ������������λ��.  getBoundingBox(): ���� AABB �����߽�����丸��������ϵͳ
			if (b->getLineIndex() == 1 && b->getBoundingBox().containsPoint(t->getLocation())) {
				if (b->getColor() == Color3B::BLACK) {//���������Ǻڿ�, �����п�����
					if (!timerRunning) {
						this->startTimer();
					}
					b->setColor(Color3B::GRAY);  //����Ϊ��ɫ
					this->moveDown();
				}
				else if (b->getColor() == Color3B::GREEN) {
					this->moveDown();
					this->stopTimer();
				}
				else {
					MessageBox("Game Over��", "Failed");
				}
				break;
			}
		}
		return false;
	};
	//����¼�������
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

//��ӿ�ʼ��
void DontTouchWhiteBlock::addStartLine() {
	 //����һ����
	auto b = Block::createWithArgs(Color3B::YELLOW, Size(visibleSize.width, visibleSize.height / 4), "", 20, Color4B::BLACK);
	gameLayer->addChild(b);
	//��ʼ������Ϊ0
	b->setLineIndex(0);
}

void DontTouchWhiteBlock::addEndLine() {
	auto b = Block::createWithArgs(Color3B::GREEN, visibleSize, "Game Over", 32, Color4B::BLACK);
	gameLayer->addChild(b);
	//����������Ϊ4, �����ϱ������ƶ���,����Ϊ4
	b->setLineIndex(4);
}

void DontTouchWhiteBlock::addNormalLine(int lineIndex) {
	Block *b;
	int blackIndex = rand() % 4;
	for (int i = 0; i < 4; i++) {
		b = Block::createWithArgs(blackIndex == i ? Color3B::BLACK : Color3B::WHITE, Size(visibleSize.width / 4 - 2 , visibleSize.height / 4-1 ), "", 20, Color4B::BLACK);
		gameLayer->addChild(b);
		b->setPosition(i * visibleSize.width / 4, lineIndex * visibleSize.height / 4);
		//����������
		b->setLineIndex(lineIndex);
	}
	//�����ͨ����ʱ
	linesCount++;
}

void DontTouchWhiteBlock::startGame() {
	//��ʼ����Ϊ0
	linesCount = 0;
	//��ʼû�г��ֽ���
	showEnd = false;

	timerRunning = false;

	//��ӵ�һ��, ��ʼ��
	addStartLine();
	//��ӵڶ���, ��Ϸ��
	addNormalLine(1);
	//��ӵ�����
	addNormalLine(2);
	//��ӵ�����
	addNormalLine(3);
}

void DontTouchWhiteBlock::moveDown() {
	if (linesCount < 50) {
		addNormalLine(4);  //���ӵ�����
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
	//offsetΪ΢��, ��ǰʱ�������ʼ��ʱ��
	long offset = clock() - startTime;
	timerLabel->setString(StringUtils::format("%g", ((double)offset / 1000000)));  //offsetΪ΢�룬ת��Ϊ��

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