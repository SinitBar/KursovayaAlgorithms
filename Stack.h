#pragma once
#include "Element.h"
class Stack
{
private:
	Element* top;
	void set_top(Element*);
public:
	Stack();
	bool is_empty();
	int size();
	Element* peek(); // to show who's on the top
	Element* pop(); // to delte top and show it
	Element* push(double); // to push on top and show it
	void push(Element*);
	~Stack();
};