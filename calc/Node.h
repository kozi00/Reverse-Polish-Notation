#pragma once
#include <iostream>
class Node
{
public:
    struct Data {
        int operand = 0;
        char operation = 0;
        int max = 0;
        int min = 0;
    };
    Data data;
    Node* next;
    Node(int operand);
    Node(char operation);
    Node(Data d);
    friend std::ostream& operator<<(std::ostream& out, const Data& node);
};

