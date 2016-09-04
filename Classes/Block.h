#ifndef BLOCK_H_
#define BLOCK_H_
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class Block : public cocos2d::Sprite{
private:
	//��̬����, �洢�׿�
	static Vector<Block*> *blocks;
	//��¼�е�����
	int lineIndex;
public:
	//��ȡ���п��touch
	static Vector<Block*> * getBlocks();
	//��̬��ʼ������
	static Block* createWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor);

	//��ʼ������, ָ����ɫ, ��С, �����ַ���, �ַ���С, �ַ���ɫ
	virtual bool initWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor);

	//�Ƴ��׿鷽��
	void removeBlock();
	 
	//��ȡ�е�����
	int getLineIndex();

	//�����е�����
	void setLineIndex(int lineIndex);

	//���п�����
	void moveDown();

};
#endif