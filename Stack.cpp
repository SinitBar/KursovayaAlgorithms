
#include "Stack.h"

void Stack::set_top(Element* top_element) { top = top_element; }

Stack::Stack()
{
	top = nullptr;
}

bool Stack::is_empty()
{
	if (top == nullptr)
		return true;
	return false;
}

int Stack::size()
{
	int size = 1;
	if (is_empty())
		return 0;
	for (Element* now = top; now->get_next() != nullptr; now = now->get_next())
		size++;
	return size;
}

Element* Stack::peek() // to show who's on the top
{
	return top;
}

Element* Stack::pop() // to delte top and show it
{
	Element* to_delete = top;
	if (is_empty())
		throw out_of_range("the stack is empty");
	else
		top = top->get_next();
	return to_delete;
}

Element* Stack::push(double data) // to push on top and show it
{
	Element* new_element = new Element;
	new_element->set_data(data);
	if (is_empty())
		top = new_element;
	else
	{
		new_element->set_next(top);
		top = new_element;
	}
	return new_element;
}

void Stack::push(Element* new_element) // to push on top and show it
{
	if (is_empty())
		top = new_element;
	else
	{
		new_element->set_next(top);
		top = new_element;
	}
}

Stack::~Stack()
{
	while (!is_empty())
		pop();
}