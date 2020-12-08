#include "Queue.h"

Queue::Queue()
{
	head = nullptr;
	tail = nullptr;
}

void Queue::set_head(Element* key) { head = key; }

void Queue::set_tail(Element* key) { tail = key; }

bool Queue::is_empty() // returns true if queue is empty
{
	if (tail == nullptr)
		return true;
	return false;
}

int Queue::size() // return a number of elements in queue
{
	if (is_empty())
		return 0;
	int size = 1;
	for (Element* now = tail; now->get_next() != nullptr; now = now->get_next())
		size++;
	return size;
}

Element* Queue::push(double data_key) // to add in the end of the queue the element with key-data
{
	Element* new_element = new Element;
	new_element->set_data(data_key);
	if (is_empty())
		head = tail = new_element;
	else
	{
		new_element->set_next(tail);
		tail = new_element;
	}
	return new_element;
}

Element* Queue::push(string data) // to add in the end of the queue the element with key-data
{
	Element* new_element = new Element;
	new_element->set_data(data);
	if (is_empty())
		head = tail = new_element;
	else
	{
		new_element->set_next(tail);
		tail = new_element;
	}
	return new_element;
}

Element* Queue::push(double number, string data) // to add in the end of the queue the element with key-data
{
	Element* new_element = new Element;
	new_element->set_data(number, data);
	if (is_empty())
		head = tail = new_element;
	else
	{
		new_element->set_next(tail);
		tail = new_element;
	}
	return new_element;
}

 void Queue::push(Element* new_element) // to add in the end of the queue the element with key-data
{
	if (is_empty())
		head = tail = new_element;
	else
	{
		new_element->set_next(tail);
		tail = new_element;
	}
}

Element* Queue::pop() // to delete first in queue and return it's key-data
{
	Element* to_delete;
	if (is_empty())
		throw out_of_range("the queue is empty");
	else if (size() == 1)
	{
		to_delete = head;
		head = tail = nullptr;
	}
	else
	{
		to_delete = head;
		for (Element* now = tail; now->get_next() != nullptr; now = now->get_next())
			head = now;
		head->next = nullptr;
	}
	return to_delete;
}

Queue::~Queue()
{
	while (!is_empty())
		pop();
}