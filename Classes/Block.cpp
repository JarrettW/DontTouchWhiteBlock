#include "Block.h"
//静态成员存储白块的Vector初始化
Vector<Block*>* Block::blocks = new Vector<Block*>();

Vector<Block*>* Block::getBlocks() {
	return Block::blocks;
}

Block* Block::createWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor) {
	//创建Block
	auto b = new Block();
	b->initWithArgs(color, size, label, fontSize, textColor);
	//自动释放
	b->autorelease();
	//每创建一个白块就放到Vector
	blocks->pushBack(b);

	return b;
}

bool Block::initWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor) {
	//执行父类初始化
	Sprite::init();
	//记录行的索引初始化为0;
	lineIndex = 0;
	//设置内容大小
	setContentSize(size);
	//左下角对齐
	setAnchorPoint(Point::ZERO);
	//呈现形状
	setTextureRect(Rect(0, 0, size.width, size.height));
	//设置颜色
	setColor(color);

	//添加文本
	auto l = Label::create();
	l->setString(label);
	l->setSystemFontSize(fontSize); //系统字号
	l->setTextColor(textColor); //文本颜色
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