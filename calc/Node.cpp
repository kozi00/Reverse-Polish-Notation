#include "Node.h"

Node::Node(int operand) {
	data.operand = operand;
	next = nullptr;
}
Node::Node(char operation) {
	data.operation = operation;
	next = nullptr;
}
Node::Node(Data d) {
	data.operation = d.operation;
	data.operand = d.operand;
	data.max = d.max;
	data.min = d.min;
	next = nullptr;
}
std::ostream& operator<<(std::ostream& out, const Node::Data& node) {
	if (&node != nullptr) {
		if (node.operation) {
			if (node.operation == 'I') {
				out << "IF ";
			}
			else if (node.operation == 'M') {
				out << "MIN" << node.min + 1 << " ";
			}
			else if (node.operation == 'X') {
				out << "MAX" << node.max + 1 << " ";
			}
			else {
				out << node.operation << " ";
			}
		}
		else {
			out << node.operand << " ";
		}
	}
	return out;

}
