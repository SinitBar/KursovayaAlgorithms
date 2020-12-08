#pragma once
#include <stdexcept>
using namespace std;
class Element
{
	Element* next;
	double data;
	string spelling;
	void set_next(Element*);
	void set_data(double);
	void set_data(string);
	void set_data(double, string);
public:
	Element();
	Element* get_next();
	double get_data();
	string get_spelling();
	~Element();
	friend class Queue;
	friend class Stack;
	//friend void string_processing(ifstream&, int);
};

