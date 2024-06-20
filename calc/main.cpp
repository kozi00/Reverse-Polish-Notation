#include "Node.h"
#include "Stack.h"
#include "Queue.h"
#include <iostream>

#define MIN 'M'
#define MAX 'X'
#define IF 'I'

using namespace std;

bool CheckPriority(char token, char top) {
	int priorityOfToken;
	int priorityOfTop;
	if (token == '+' || token == '-') { priorityOfToken = 1; }
	else if (token == '*' || token == '/') { priorityOfToken = 3; }
	else if (token == 'N') { priorityOfToken = 6; }
	else if (token == IF) { priorityOfToken = 8; }
	else if (token == MAX || token == MIN) { priorityOfToken = 9; }
	else { priorityOfToken = 11; }

	if (top == '+' || top == '-') { priorityOfTop = 2; }
	else if (top == '*' || top == '/') { priorityOfTop = 4; }
	else if (top == 'N') { priorityOfTop = 5; }
	else if (top == IF) { priorityOfTop = 7; }
	else if (top == MAX || top == MIN) { priorityOfTop = 10; }
	else { priorityOfTop = 0; }

	return priorityOfToken < priorityOfTop;

}
bool isOperand(char token) {
	if (token == '+' || token == '-' || token == '*' || token == '/' || token == 'N' || token == IF || token == ',' || token == ')' || token == '(' || token == MIN || token == MAX) {
		return false;
	}
	else {
		return true;
	}
}

void CountComma(Node* pointer) {//dodaj do licznika przecinkow (MIN i MAX) znalezionego operatora
	if (pointer->data.operation == MAX) {
		pointer->data.max++;
	}
	else {
		pointer->data.min++;
	}
}
Node* FindFunction(Stack* s) {//znajdz operator IF lub MAX lub MIN ktory jest najwyzej w stacku
	Node* ptr = s->top;
	while (ptr != NULL && ptr->data.operation != MAX && ptr->data.operation != MIN && ptr->data.operation != IF) {
		ptr = ptr->next;
	}
	return ptr;
}
int NumberParser(char token) {
	Stack n;

	char number = token;
	int parsedNumber = 0;
	int value = 1;
	while (number >= '0' && number <= '9') {
		n.push(number);
		cin.get(number);
	}
	while (!n.isEmpty()) {
		parsedNumber += (n.pop().operation - '0') * value;
		value *= 10;//mnozenie o potegi 10 aby powstala liczba dziesietna
	}
	return parsedNumber;
}
void OperatorParser(char* token) {//zapisanie tylko jednego znaku
	char x;
	if (*token == IF) {
		cin >> x;
	}
	else if (*token == 'M') {
		cin >> x;
		if (x == 'A') {
			*token = MAX;
		}
		else {
			*token = MIN;
		}
		cin >> x;
	}
}
int MakeOperation(Stack* out) {
	int a, b, c, size, number;

	Node::Data token = out->pop();
	switch (token.operation) {
	case '+':
		b = out->pop().operand;
		a = out->pop().operand;
		return a + b;
		break;
	case '-':
		b = out->pop().operand;
		a = out->pop().operand;
		return a - b;
		break;
	case '*':
		b = out->pop().operand;
		a = out->pop().operand;
		return a * b;
		break;
	case '/':
		b = out->pop().operand;
		a = out->pop().operand;
		if (b != 0) {
			return a / b;
		}
		else {//dzielenie przez 0
			while (out->top != nullptr) {//free memory
				Node* temp = out->top;
				out->top = out->top->next;
				delete temp;
			}
			throw std::invalid_argument("Dividing by zero");
		}
		break;
	case 'N':
		a = out->pop().operand;
		return -a;
	case IF:
		c = out->pop().operand;
		b = out->pop().operand;
		a = out->pop().operand;
		return a > 0 ? b : c;
	case MIN:
		size = token.min;
		number = out->pop().operand;
		for (int i = 0; i < size; i++) {
			if (number >= out->top->data.operand) number = out->top->data.operand;
			out->pop().operand;
		}
		return number;
		break;
	case MAX:
		size = token.max;
		number = out->pop().operand;
		for (int i = 0; i < size; i++) {
			if (number <= out->top->data.operand) number = out->top->data.operand;
			out->pop().operand;
		}
		return number;
		break;
	default:
		return 0;
		break;
	}
}
void PostfixOutput(Queue* output) {
	Stack out;
	int result = 0;

	output->Display();

	while (!output->isEmpty()) {
		if (output->front->data.operation) {
			out.push(output->dequeue());
			out.Display();
			result = MakeOperation(&out);
			out.push(result);
		}
		else {
			out.push(output->dequeue().operand);
		}
	}
	printf("%d\n", result);
}
Queue ONPConversion() {
	char token;
	Stack operatorStack;
	Node* functionPointer = nullptr;//uzywane przy liczeniu przecinkow MAX I MIN
	Queue output;
	while (cin >> token)
	{
		if (token == '.') { break; }
		else if (isOperand(token)) {//jesli to liczba to sprarsuj i dodaj na wyjscie
			int parsed = NumberParser(token);
			output.enqueue(parsed);
		}
		else if (token == ',') {//wyjmij ze stacka wszystko do momentu '('
			while (!operatorStack.isEmpty()) {
				if (operatorStack.top->data.operation == '(') { break; }
				else {
					output.enqueue(operatorStack.pop());
				}
			}
			functionPointer = FindFunction(&operatorStack);//liczenie MIN i MAX
			CountComma(functionPointer);
		}
		else if (token == '(') {
			operatorStack.push(token);
		}
		else if (token == ')') {//wyjmij ze stacka wszystko do momentu '(' lacznie z nawiasem
			while (!operatorStack.isEmpty()) {
				Node::Data data = operatorStack.pop();
				if (data.operation == '(') {
					break;
				}
				else {
					output.enqueue(data);
				}
			}
		}
		else {
			OperatorParser(&token);
			while (!operatorStack.isEmpty() && CheckPriority(token, operatorStack.top->data.operation)) {//do momentu kiedy priorytet tokenu jest mniejszy to usuwaj ze stacka i dodawaj na wyjscie
				Node::Data operatorData = operatorStack.pop();
				output.enqueue(operatorData);
			}
			operatorStack.push(token);
		}
	}
	while (!operatorStack.isEmpty()) {//oproznij stack
		Node::Data operatorData = operatorStack.pop();
		output.enqueue(operatorData);
	}
	return output;
}
int main() {
	int n;
	Queue output;
	cin >> n;
	for (int i = 0; i < n; i++) {
		try {
			output = ONPConversion();
			PostfixOutput(&output);
		}
		catch (const std::invalid_argument& e) {
			while (output.front != nullptr) {//free memory
				Node* temp = output.front;
				output.front = output.front->next;
				delete temp;
			}
			output.rear = nullptr;

			printf("ERROR\n\n");
		}
	}
}