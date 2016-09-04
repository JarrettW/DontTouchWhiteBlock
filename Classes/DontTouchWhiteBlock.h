#ifndef _DONT_TOUCH_WHITE_BLOCK_H_
#define _DONT_TOUCH_WHITE_BLOCK_H_

#include "cocos2d.h"
#include "Block.h"
USING_NS_CC;
class DontTouchWhiteBlock : public cocos2d::Layer
{
private:
	//�ɼ���С
	Size visibleSize;
	//��ʱ���ֵ�����
	int linesCount;
	//�Ƿ���ֽ�����
	bool showEnd;
	//����ʱ��
	Label *timerLabel;
	//�ֲ�: ���ʱ��label�Ĳ�
	Node *gameLayer;
	//ʱ���Ƿ�������
	bool timerRunning;
	//��Ϸ���ĵ�ʱ��
	long startTime;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(DontTouchWhiteBlock);

	//��ӿ�ʼ��
	void addStartLine();
	//��ӽ�����
	void addEndLine();
	//��Ӻڰ׿��У�����ͨ��ÿһ��
	void addNormalLine(int lineIndex);

	//��ʼ��Ϸ����
	void startGame();
	//���Ʋ���
	void moveDown();

	//��ʼ��ʱ
	void startTimer();
	//������ʱ
	void stopTimer();

	//��ʱ����
	virtual void update(float dt);
};

#endif // _DONT_TOUCH_WHITE_BLOCK_H_
