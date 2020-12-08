#pragma once
#include "Queue.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <string>
#define _USE_MATH_DEFINES // for pi written like M_PI
#include <math.h>

enum functions { COS, SIN, TG, CTG, LN, LOG, SQRT, PI, EXP, ABS, NOT_FUNCTION };

enum priorities { brecket, minus_plus, multiply_divide, degree, function, not_operator };

extern bool my_error;

bool is_number(char);
bool is_letter(char);
int what_operation_priority(char);
int what_function(string);
Queue* string_processing(ifstream&, ofstream&);
Queue* convert_to_reverse_polish_notation(Queue*, ofstream&);
double calculation(ifstream&, ofstream&);