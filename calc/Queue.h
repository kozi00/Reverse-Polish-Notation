#pragma once
#include "Node.h"
#include <iostream>
class Queue
{
public:
	Node* front;
	Node* rear;
	Queue();
	bool isEmpty() const;
	void enqueue(int operand);
	void enqueue(Node::Data data);
	Node::Data dequeue();
	void Display() const;
};

