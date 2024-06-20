#include "Stack.h"
#include <iostream>


Stack::Stack() {
	top = nullptr;
}
bool Stack::isEmpty() const {
	if (top == NULL) {
		return true;
	}
	else {
		return false;
	}
}
Node::Data Stack::pop() {
	if (!Stack::isEmpty()) {
		Node::Data token = top->data;
		Node* p = top;
		top = top->next;
		delete p;
		return token;
	}
	Node::Data null;
	return null;
}
void Stack::push(char operation)
{
	Node* node = new Node(operation);
	node->next = top;
	top = node;
}
void Stack::push(int operand)
{
	Node* node = new Node(operand);
	node->next = top;
	top = node;
}
void Stack::push(Node::Data d) {
	Node* node = new Node(d);
	node->next = top;
	top = node;
}
void Stack::Display() const {
	if (top != nullptr) {
		Node* ptr = top;
		while (ptr != nullptr) {
			std::cout << ptr->data;
			ptr = ptr->next;
		}
		printf("\n");
	}
}





