#pragma once
#include "Node.h"
class Stack
{
public:
	Node* top;
	Stack();
	Node::Data pop();
	void push(char operation);
	void push(int operand);
	void push(Node::Data d);
	bool isEmpty() const;
	void Display() const;
};

