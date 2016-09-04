#include "Block.h"
//��̬��Ա�洢�׿��Vector��ʼ��
Vector<Block*>* Block::blocks = new Vector<Block*>();

Vector<Block*>* Block::getBlocks() {
	return Block::blocks;
}

Block* Block::createWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor) {
	//����Block
	auto b = new Block();
	b->initWithArgs(color, size, label, fontSize, textColor);
	//�Զ��ͷ�
	b->autorelease();
	//ÿ����һ���׿�ͷŵ�Vector
	blocks->pushBack(b);

	return b;
}

bool Block::initWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor) {
	//ִ�и����ʼ��
	Sprite::init();
	//��¼�е�������ʼ��Ϊ0;
	lineIndex = 0;
	//�������ݴ�С
	setContentSize(size);
	//���½Ƕ���
	setAnchorPoint(Point::ZERO);
	//������״
	setTextureRect(Rect(0, 0, size.width, size.height));
	//������ɫ
	setColor(color);

	//����ı�
	auto l = Label::create();
	l->setString(label);
	l->setSystemFontSize(fontSize); //ϵͳ�ֺ�
	l->setTextColor(textColor); //�ı���ɫ
	addChild(l);
	l->setPosition(size.width / 2, size.height / 2);

	return true;
}

void Block::removeBlock() {
	removeFromParent();
	blocks->eraseObject(this);
}

void Block::setLineIndex(int v) {
	this->lineIndex = v;
}

int Block::getLineIndex() {
	return this->lineIndex;
}

void Block::moveDown() {
	this->lineIndex--;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	runAction(Sequence::create(MoveTo::create(0.1f, Point(getPositionX(), lineIndex * visibleSize.height / 4)), CallFunc::create([this]() {
		if (lineIndex < 0)
			this->removeBlock();
	}), NULL));
}