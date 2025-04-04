#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <stack>
#include <stdexcept>

using namespace std;

class ExpressionEvaluator
{
public:
	double evaluate(const string &expression)
	{
		stringstream ss(expression);
		stack<double> values;
		stack<char> operators;

		while (!ss.eof())
		{
			char c = ss.get();

			if (isspace(c))
			{
				continue;
			}

			if (isdigit(c) || c == '.')
			{
				ss.putback(c);
				double value;
				ss >> value;
				values.push(value);
			}
			else if (c == '(')
			{
				operators.push(c);
			}
			else if (c == ')')
			{
				while (!operators.empty() && operators.top() != '(')
				{
					performOperation(values, operators);
				}
				operators.pop();
			}
			else if (c == '^')
			{
				operators.push(c);
			}
			else if (c == '+')
			{
				operators.push(c);
			}
			else if (c == '-')
			{
				operators.push(c);
			}
			else if (c == '/')
			{
				operators.push(c);
			}
			else if (c == '*')
			{
				operators.push(c);
			}
		}

		while (!operators.empty())
		{
			performOperation(values, operators);
		}

		if (values.size() != 1)
		{
			throw invalid_argument("Invalid expression");
		}
		return values.top();
	}

private:
	void performOperation(stack<double> &values, stack<char> &operators)
	{
		if (values.size() < 2)
		{
			throw invalid_argument("Insufficient values in expression");
		}

		double b = values.top();
		values.pop();
		double a = values.top();
		values.pop();

		char op = operators.top();
		operators.pop();
		double result;

		switch (op)
		{
		case '+':
			result = a + b;
			break;
		case '-':
			result = a - b;
			break;
		case '*':
			result = a * b;
			break;
		case '/':
			result = a / b;
			break;
		case '^':
			result = pow(a, b);
			break;
		default:
			throw invalid_argument("Unknown operator");
		}

		values.push(result);
	}
};

int main()
{
	ExpressionEvaluator evaluator;
	string expression;

	cout << "Enter a mathematical expression: ";
	getline(cin, expression);

	try
	{
		double result = evaluator.evaluate(expression);
		cout << "Result: " << result << endl;
	}
	catch (const exception &e)
	{
		cout << "Error: " << e.what() << endl;
	}
	return 0;
}
