#include "Queue.h"

Queue::Queue() {
	front = nullptr;
	rear = nullptr;
}
void Queue::enqueue(int operand) {
	Node* node = new Node(operand);
	if (!Queue::isEmpty()) {
		rear->next = node;
		rear = node;
	}
	else {
		rear = node;
		front = node;
	}
}
void Queue::enqueue(Node::Data data) {
	Node* node = new Node(data);
	if (!Queue::isEmpty()) {
		rear->next = node;
		rear = node;
	}
	else {
		rear = node;
		front = node;
	}
}
Node::Data Queue::dequeue() {
	if (!Queue::isEmpty()) {
		Node::Data token = front->data;
		Node* p = front;
		front = front->next;
		delete p;
		return token;
	}
	Node::Data null;
	return null;
}
bool Queue::isEmpty() const {
	if (front == nullptr) {
		return true;
	}
	else {
		return false;
	}
}
void Queue::Display() const {
	if (front != nullptr) {
		Node* ptr = front;
		while (ptr != nullptr) {
			std::cout << ptr->data << " ";
			ptr = ptr->next;
		}
		printf("\n");
	}
}
