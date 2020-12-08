#include "Calculator.h"

bool my_error = false; // definition

bool is_number(char symbol)
{
	string can_begin_with_number("0123456789");
	for (char now_symbol : can_begin_with_number)
	{
		if (symbol == now_symbol)
			return true;
	}
	return false;
}

bool is_letter(char symbol)
{
	string can_be_letter("cosintglqrtexpab");
	for (char now_symbol : can_be_letter)
	{
		if (symbol == now_symbol)
			return true;
	}
	return false;
}

int what_operation_priority(char symbol)
{
	if (symbol == ')' || symbol == '(')
		return brecket;
	if (symbol == '+' || symbol == '-')
		return minus_plus;
	if (symbol == '*' || symbol == '/')
		return multiply_divide;
	if (symbol == '^')
		return degree;
	return not_operator;
}

int what_function(string function)
{
	if (function == "cos")
		return COS;
	if (function == "sin")
		return SIN;
	if (function == "tg")
		return TG;
	if (function == "ctg")
		return CTG;
	if (function == "ln")
		return LN;
	if (function == "log")
		return LOG;
	if (function == "sqrt")
		return SQRT;
	if (function == "pi")
		return PI;
	if (function == "exp")
		return EXP;
	if (function == "abs")
		return ABS;
	return NOT_FUNCTION; // not a function of the list
}

double count_function(int function, double argument)
{ // можно вы€вить ошибки типо пи на два аргумента или делени€ на ноль
	double counted = 0;
	switch (function)
	{
	case COS:
		counted = cos(argument);
		break;
	case SIN:
		counted = sin(argument);
		break;
	case TG:
		counted = tan(argument);
		break;
	case CTG:
		counted = (cos(argument)/sin(argument));
		break;
	case LN:
		counted = log(argument);
		break;
	case LOG:
		counted = log10(argument);
		break;
	case SQRT:
		counted = sqrt(argument);
		break;
	case ABS:
		counted = abs(argument);
		break;
	case EXP:
		counted = exp(argument);
		break;
	}
	return counted;
}

double count_operation(string operation, double first_argument, double second_argument)
{
	double result = 0;
	switch (operation[0])
	{
	case '-':
		result = (first_argument - second_argument);
		break;
	case '+':
		result = (first_argument + second_argument);
		break;
	case '*':
		result = (first_argument * second_argument);
		break;
	case '/':
		result = (first_argument / second_argument);
		break;
	case '^':
		result = (pow(first_argument, second_argument));
		break;
	}
	return result;
}

Queue* string_processing(ifstream& in, ofstream& out) // = 1 in start
{
	char now_char;
	Queue* elements = new Queue;
	int left_breckets = 0;
	int right_breckets = 0;
	//out << "got input:" << endl;
	while ((!my_error) && (in.peek() != '\n') && (in.peek() != EOF))
	{
		if (in.peek() == ' ')
		{
			in.get();
			continue;
		}
		in >> now_char;
		if (now_char == '(') // if we met (
		{
			left_breckets++;
			elements->push(what_operation_priority(now_char), "("); // add ( to queue
			out << now_char; // (
			if (what_operation_priority(in.peek()) != not_operator)
			{
				if (in.peek() == '-') //unary minus // ...(-...
					elements->push(0, "unary_minus"); // add null to have 0-A instead of just -A
				else if (in.peek() != '(') // error ...(operator...
				{
					out << endl << "...don't know what does ( " << in.peek() << " mean " << endl;
					my_error = true;
				}
			}
		}
		else if (is_number(now_char)) // met a first digit of a number
		{
			double now_number;
			in.putback(now_char);
			in >> now_number; // read whole number
			elements->push(now_number); // add number to queue (will have -1 priority (not set))
			out << now_number; // number
			if (is_letter(in.peek())) // error ...number letter...
			{
				out << endl << "...action is required after " << now_number << endl;
				my_error = true;
			}
			else if (in.peek() == '(') // error ...number(
			{
				out << endl << "...don't know what does " << now_number << "( mean" << endl;
				my_error = true;
			}
		}
		else if (now_char == ')') // met )
		{
			right_breckets++;
			if (right_breckets > left_breckets) // error like ...())...
			{
				out << endl << "...left brecket is required" << endl;
				my_error = true;
			}
			else if (in.peek() == '(') // error ...)(...
			{
				out << endl << "...don't know what does )( mean" << endl;
				my_error = true;
			}
			else if (is_letter(in.peek())) // error ...)letter...
			{
				out << endl << "...action is required after )" << endl;
				my_error = true;
			}
			else
			{
				elements->push(what_operation_priority(now_char), ")"); // push ) to queue
				out << now_char; // )
			}
		}
		else if (what_operation_priority(now_char) != not_operator) // met an operator
		{
			if ((now_char == '-')&&(elements->is_empty()))
				elements->push(0, "unary_minus"); // add null to have 0-A instead of just -A
			if (in.peek() == ')') // error ...operator)...
			{
				out << endl << "...operand is required after " << now_char << endl;
				my_error = true;
			}
			else if ((what_operation_priority(in.peek()) != not_operator)&&(in.peek() != '(')) // error ...operator operator(not ( )...
			{
				out << endl << "...don't know what does " << now_char << " " << in.peek() << " mean" << endl;
				my_error = true;
			}
			else // no error // push operator to queue
			{
				string math_operator;
				math_operator.push_back(now_char);
				elements->push(what_operation_priority(now_char), math_operator); // operation with priority = 1/2/3
				out << now_char; //operator
			}
		}
		else if (is_letter(now_char)) // met a letter
		{
			string function;
			function.push_back(now_char); // want to have a word if it is cos for example
			while (is_letter(in.peek()))
			{
				in >> now_char;
				function.push_back(now_char);
			} // now we have a word
			while (in.peek() == ' ')
				in.get();
			if (what_function(function) == PI) // pi doesn't need an argument
			{
				out << function;
				elements->push(M_PI, "pi"); // push pi
			}
			else if (what_function(function) == NOT_FUNCTION) // error: if we don't know this word
			{
				out << endl << "...don't know what is " << function << endl;
				my_error = true;
			}
			else if (in.peek() != '(') // error ...function... (cos5 should be cos(5))
			{
				out << endl << "...no argument for " << function << endl;
				my_error = true;
			}
			else
			{
				elements->push(priorities::function, function); // push function to queue
				out << function; // function
			}
		}
		else
		{ // error: unknown symbol (maybe not situated like . )
			out << endl << "...don't know what does " << now_char << " mean here" << endl;
			my_error = true;
		}
	}
	if ((right_breckets < left_breckets)&&(!my_error)) // error like ...(() EOF
	{
		out << endl << "...there is missing one or more right breckets" << endl;
		my_error = true;
	}
	if (my_error)
	{
		out << "try again..." << endl;
		return nullptr;
	}
	return elements;
}

Queue* convert_to_reverse_polish_notation(Queue* elements, ofstream& out)
{
	Queue* reversed = new Queue;
	if (elements == nullptr)
		return nullptr;
	Stack stack;
	while (!elements->is_empty())
	{
		Element* now_element = new Element;
		now_element = elements->pop();
		string now_string = now_element->get_spelling();
		double now_data = now_element->get_data();
		if (now_string == "(")
			stack.push(now_element);
		else if ((now_string == "#") || (now_string == "unary_minus") || (now_string == "pi")) // operand
		{
			out << now_data << " ";
			reversed->push(now_element);
		}
		else if (now_string == ")")
		{
			while (stack.peek()->get_spelling() != "(")
			{
				out << stack.peek()->get_spelling() << " ";
				reversed->push(stack.pop());
			}
			stack.pop(); // (
		}
		else // operator or function
		{
			if (!stack.is_empty())
			{
				while (now_data <= stack.peek()->get_data())// comparing priorities
				{
					out << stack.peek()->get_spelling() << " ";
					reversed->push(stack.pop());
					if (stack.is_empty())
						break;
				}
			}
			stack.push(now_element);
		}
	}
	while (!stack.is_empty())
	{
		out << stack.peek()->get_spelling();
		reversed->push(stack.pop());
	}
	return reversed;
}

double calculation(ifstream& in, ofstream& out)
{
	out << "got input:" << endl;
	Queue* elements = string_processing(in, out);
	if ((elements == nullptr)&&(!my_error))
	{
		out << "error: no elements" << endl;
		my_error = true;
		return 0;
	}
	if (my_error)
		return 0;
	out << endl << "reverse polish notation of input:" << endl;
	elements = convert_to_reverse_polish_notation(elements, out);
	if ((elements == nullptr) && (!my_error))
	{
		out << "error: no reversed elements" << endl;
		my_error = true;
		return 0;
	}
	double result = 0;
	if (my_error)
		return 0;
	Stack stack;
	while ((!elements->is_empty())&&(!my_error))
	{
		Element* now_element = elements->pop();
		string now_string = now_element->get_spelling();
		double now_data = now_element->get_data();
		if ((now_string == "#") || (now_string == "unary_minus") || (now_string == "pi"))
		{
			stack.push(now_element); // operand
		}
		else // function or operator
		{
			double first_operand = 0;
			if ((now_data == priorities::function) && (!stack.is_empty()))
			{
				result = count_function(what_function(now_string), stack.pop()->get_data());
				stack.push(result);
			}
			else if (!stack.is_empty()) //»Ќј„≈
			{
				result = stack.pop()->get_data(); // second operand
				if (stack.is_empty())
				{
					out << endl << "error: not enough operands" << endl;
					out << now_data << endl;
					my_error = true;
					return 0;
				}
				first_operand = stack.pop()->get_data();
				result = count_operation(now_string, first_operand, result);
				stack.push(result);
			}
		}
	}
	return result;
}