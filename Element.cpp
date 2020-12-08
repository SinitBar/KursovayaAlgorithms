#include "Element.h"

Element::Element()
{
	data = -1;
	spelling = "#";
	next = nullptr;
}

Element* Element::get_next() { return next; }
double Element::get_data() { return data; }
string Element::get_spelling() { return spelling; }
void Element::set_next(Element* new_element) { next = new_element; }
void Element::set_data(double information) { data = information; }
void Element::set_data(string information) { spelling = information; }

void Element::set_data(double data_key, string information) 
{ 
	data = data_key;
	spelling = information; 
}
Element::~Element() { delete next; next = nullptr; }