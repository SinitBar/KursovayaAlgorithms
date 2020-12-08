#include "pch.h"
#include "CppUnitTest.h"
#include "/Users/varka/source/repos/Calculator/Calculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//extern bool my_error;

namespace CalculatorTest
{
	TEST_CLASS(CalculatorTest)
	{
	public:
		TEST_METHOD(test_error_breckets)
		{
			my_error = false;
			ofstream out("/Users/varka/source/repos/Calculator/in.txt");
			out << "cos((1-(2+3))*4)^(5+6)";
			out.close();
			ifstream in("/Users/varka/source/repos/Calculator/in.txt");
			out.open("/Users/varka/source/repos/Calculator/out.txt");
			double result = calculation(in, out);
			out.close();
			Assert::IsFalse(my_error);
		}
		TEST_METHOD(test_error_unknown_symbol)
		{
			my_error = false;
			ofstream out("/Users/varka/source/repos/Calculator/in.txt");
			out << "cos((1.2534.173-(2+3))*4)^(5+6))";
			out.close();
			ifstream in("/Users/varka/source/repos/Calculator/in.txt");
			out.open("/Users/varka/source/repos/Calculator/out.txt");
			double result = calculation(in, out);
			out.close();
			Assert::IsTrue(my_error);
		}
		TEST_METHOD(test_error_double_operator)
		{
			my_error = false;
			ofstream out("/Users/varka/source/repos/Calculator/in.txt");
			out << "cos(1-(2++3))*4^(5+6)";
			out.close();
			ifstream in("/Users/varka/source/repos/Calculator/in.txt");
			out.open("/Users/varka/source/repos/Calculator/out.txt");
			double result = calculation(in, out);
			out.close();
			Assert::IsTrue(my_error);
		}
		TEST_METHOD(test_error_no_operator)
		{
			my_error = false;
			ofstream out("/Users/varka/source/repos/Calculator/in.txt");
			out << "cos(1(2+3))*4^(5+6)";
			out.close();
			ifstream in("/Users/varka/source/repos/Calculator/in.txt");
			out.open("/Users/varka/source/repos/Calculator/out.txt");
			double result = calculation(in, out);
			out.close();
			Assert::IsTrue(my_error);
		}
		TEST_METHOD(readInput)
		{
			ofstream out("/Users/varka/source/repos/Calculator/in.txt");
			out << "(cos((1-(2+3))*4))^(5+6)";
			out.close();
			ifstream in("/Users/varka/source/repos/Calculator/in.txt");
			out.open("/Users/varka/source/repos/Calculator/out.txt");
			Queue* elements = string_processing(in, out);
			in.close();
			out.close();
			in.open("/Users/varka/source/repos/Calculator/in.txt");
			while ((in.peek() != '\n') && (in.peek() != EOF))
			{
				while (in.peek() == ' ')
					in.get();
					if (elements->is_empty())
						Assert::Fail();
					Element* element = elements->pop();
					string function = element->get_spelling();
					double data = element->get_data();
					if (function == "unary_minus")
						continue;
					if (function != "#")
					{
						char now_char;
						for (unsigned int i = 0; i < function.size(); i++)
						{
							in >> now_char;
							char in_string = function[i];
							Assert::AreEqual(in_string, now_char);
							while ((in.peek() == ' ') && (in.peek() != '\n') && (in.peek() != EOF))
								in.get();
						}
					}
					else
					{
						if (in.peek() == 'p') // pi case
						{
							in.get();
							if (in.peek() == 'i')
							{
								in.get();
								Assert::AreEqual(data, M_PI);
							}
							else
								in.putback('p');
						}
						else
						{
							double number;
							in >> number;
							Assert::AreEqual(data, number);
						}
					}
			}
			Assert::IsTrue(true);
		}

		TEST_METHOD(test_convert_to_reverse_polish_notation)
		{
			ofstream out("/Users/varka/source/repos/Calculator/in.txt");
			out << "(cos((1-(2+3))*4))^(5+6)";
			string right_result = "1 2 3 + - 4 * cos 5 6 + ^";
			out.close();
			ifstream in("/Users/varka/source/repos/Calculator/in.txt");
			out.open("/Users/varka/source/repos/Calculator/out.txt");
			Queue* elements = string_processing(in, out);
			in.close();
			out.close();
			out.open("/Users/varka/source/repos/Calculator/out.txt");
			convert_to_reverse_polish_notation(elements, out);
			out.close();
			in.open("/Users/varka/source/repos/Calculator/out.txt");
			string result;
			string current;
			while ((in.peek() != '\n') && (in.peek() != EOF))
			{
				in >> current;
				result += " " + current;
			}
			result.erase(0, 1);
			in.close();
			Assert::AreEqual(result, right_result);
		}
		TEST_METHOD(test_count)
		{
			ofstream out("/Users/varka/source/repos/Calculator/in.txt");
			out << "(cos((1-(2+3))*4))^(5+6)";
			out.close();
			ifstream in("/Users/varka/source/repos/Calculator/in.txt");
			out.open("/Users/varka/source/repos/Calculator/out.txt");
			double result = calculation(in, out);
			out << endl << "result = " << result << endl;
			double right_result = pow(cos(-16), 11);
			out.close();
			Assert::AreEqual(result, right_result);
		}
		TEST_METHOD(test_1_count)
		{
			my_error = false;
			ofstream out("/Users/varka/source/repos/Calculator/in.txt");
			out << "-cos(3)";
			out.close();
			ifstream in("/Users/varka/source/repos/Calculator/in.txt");
			out.open("/Users/varka/source/repos/Calculator/out.txt");
			double result = calculation(in, out);
			out << endl << "result = " << result << endl;
			double right_result = -cos(3);
			out.close();
			Assert::AreEqual(result, right_result);
		}
		TEST_METHOD(test_2_count)
		{
			my_error = false;
			ofstream out("/Users/varka/source/repos/Calculator/in.txt");
			out << "ln(23.1278*exp(-4))";
			out.close();
			ifstream in("/Users/varka/source/repos/Calculator/in.txt");
			out.open("/Users/varka/source/repos/Calculator/out.txt");
			double result = calculation(in, out);
			out << endl << "result = " << result << endl;
			double right_result = log(23.1278 * exp(-4));
			out.close();
			Assert::AreEqual(result, right_result);
		}
		TEST_METHOD(test_3_count)
		{
			my_error = false;
			ofstream out("/Users/varka/source/repos/Calculator/in.txt");
			out << "tg(log(abs(ln(23.1278*exp(-4)))))";
			out.close();
			ifstream in("/Users/varka/source/repos/Calculator/in.txt");
			out.open("/Users/varka/source/repos/Calculator/out.txt");
			double result = calculation(in, out);
			out << endl << "result = " << result << endl;
			double right_result = tan(log10(abs(log(23.1278 * exp(-4)))));
			out.close();
			Assert::AreEqual(result, right_result);
		}
		TEST_METHOD(test_4_count)
		{
			my_error = false;
			ofstream out("/Users/varka/source/repos/Calculator/in.txt");
			out << "cos(pi)*tg(log(abs(ln(23.1278*exp(-4)))))/13.0498-sin(3^7)";
			out.close();
			ifstream in("/Users/varka/source/repos/Calculator/in.txt");
			out.open("/Users/varka/source/repos/Calculator/out.txt");
			double result = calculation(in, out);
			out << endl << "result = " << result << endl;
			double right_result = cos(M_PI) * tan(log10(abs(log(23.1278 * exp(-4))))) / 13.0498 - sin(pow(3, 7));
			out.close();
			Assert::AreEqual(result, right_result);
		}
		TEST_METHOD(test_5_count)
		{
			my_error = false;
			ofstream out("/Users/varka/source/repos/Calculator/in.txt");
			out << "-cos(-pi+1)*tg(log(abs(ln(23.1278*exp(-4)))))/13.0498-sin(3^7)";
			out.close();
			ifstream in("/Users/varka/source/repos/Calculator/in.txt");
			out.open("/Users/varka/source/repos/Calculator/out.txt");
			double result = calculation(in, out);
			out << endl << "result = " << result << endl;
			double right_result = -cos(-M_PI+1) * tan(log10(abs(log(23.1278 * exp(-4))))) / 13.0498 - sin(pow(3, 7));
			out.close();
			Assert::AreEqual(result, right_result);
		}
		TEST_METHOD(test_6_count)
		{
			my_error = false;
			ofstream out("/Users/varka/source/repos/Calculator/in.txt");
			out << "cos( pi) * tg(- log(abs(-ln(23.1278* exp(-4)))))  /   13.0498-sin(3^ 7) ";
			out.close();
			ifstream in("/Users/varka/source/repos/Calculator/in.txt");
			out.open("/Users/varka/source/repos/Calculator/out.txt");
			double result = calculation(in, out);
			out << endl << "result = " << result << endl;
			double right_result = cos(M_PI) * tan(-log10(abs(-log(23.1278 * exp(-4))))) / 13.0498 - sin(pow(3, 7));
			out.close();
			Assert::AreEqual(result, right_result);
		}
	};
}
