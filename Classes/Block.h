#ifndef BLOCK_H_
#define BLOCK_H_
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class Block : public cocos2d::Sprite{
private:
	//静态数组, 存储白块
	static Vector<Block*> *blocks;
	//记录行的索引
	int lineIndex;
public:
	//获取所有块的touch
	static Vector<Block*> * getBlocks();
	//静态初始化方法
	static Block* createWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor);

	//初始化方法, 指定颜色, 大小, 传入字符串, 字符大小, 字符颜色
	virtual bool initWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor);

	//移除白块方法
	void removeBlock();
	 
	//获取行的索引
	int getLineIndex();

	//设置行的索引
	void setLineIndex(int lineIndex);

	//所有块下移
	void moveDown();

};
#endif