#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;



bool check(int i, string infix);

int evaluate(string infix, string& postfix, bool& result)
{

	//create postfix expression
	int length = infix.length();

	postfix = "";
	stack<char> op;
	for (int i = 0; i < length; i++)
	{
		if (infix[i] == ' ')	//remove sall spaces
		{
			for (int j = i; j < length; j++)
			{
				infix[j] = infix[j + 1];
			}
			infix.resize(infix.length() - 1);	//adjust size of string
			length = infix.length();
			i--;
		}
	}

	int open = 0;	//number of open brackets
	int close = 0;	//number of closing brackets
	for (int i = 0; i < length; i++)
	{
		
		switch (infix[i])
		{
		case ('T'): case('F'):

			postfix += infix[i];
			break;

		case ('('):
			open++;	//count number of open brackets
			if (i > 0 && infix[i-1] != '&' && infix[i - 1] != '^' && infix[i - 1] != '!' && infix[i - 1] != '(')
				return 1;
			op.push(infix[i]);
			break;

		case(')'):
			close++;	//count number of close brackets
			if (close > open)	//if more close bracekt comes before open bracket, return 1
				return 1;
			if (i < length - 1 && infix[i + 1] != '&' && infix[i + 1] != '^' && infix[i + 1] != '!' && infix[i+1] != ')')
				return 1;
			while (op.top() != '(')
			{
				postfix += op.top();
				op.pop();
			}
			op.pop();
			break;

		case ('!'):
			while (!op.empty() && op.top() != '(' && infix[i] >= op.top())
			{
				postfix = postfix + op.top();
				op.pop();
			}
			op.push(infix[i]);
			break;

		case ('&'):
			if (!check(i, infix))
				return 1;
			while (!op.empty() && op.top() != '(' && infix[i] >= op.top() && infix[i] != '!')	//lower precedence than !
			{
				postfix += op.top();
				op.pop();
			}
			op.push(infix[i]);
			break;

		case ('^'):
			if (!check(i, infix))
				return 1;
			while (!op.empty() && op.top() != '(' && infix[i] >= op.top() && infix[i] != '!' && infix[i] != '&')	//lowest precedence
			{
				postfix = postfix + op.top();
				op.pop();
			}
			op.push(infix[i]);
			break;
		default:
			return 1;	//invalid character returns 1
		}

	}

	if (open != close)	//if not same number of opening and closing brackets
		return 1;

	while (!op.empty())
	{
		postfix += op.top();
		op.pop();
	}


	//evaluate

	stack<bool> operand;
	bool r;
	length = postfix.length();
	for (int i = 0; i < length; i++)
	{
		if (postfix[i] == 'T')
			operand.push(1);
		else if( postfix[i] == 'F')
			operand.push(0);
		else if (postfix[i] == '!')
		{
			bool a = operand.top();
			operand.pop();
			operand.push(!a);
		}
		else
		{
			int operand1 = operand.top();
			operand.pop();
			if (operand.empty())	//if only one operand and operator
				return 1;
			int operand2 = operand.top();	//find second operand
			operand.pop();

			if (postfix[i] == '&')
			{
				r = (operand1 && operand2);
				operand.push(r);
			}
			if (postfix[i] == '^')
			{
				r = (operand1 ^ operand2);	//exclusive or
				operand.push(r);
			}
		}	

	}
	if (operand.empty())	//if expression is empty
		return 1;
	bool first = operand.top();
	operand.pop();
	if (!operand.empty())	//operand should only have one item
	{
		return 1;
	}
	result = first;
	return 0;
	
}

bool check(int i, string infix)	//checks that there is an operand before and after operator
{
	int b = i - 1;
	int a = i + 1;
	int length = infix.length();
	if (b == -1 || a == length)	//if operand is at beginning or end of infix string
		return false;
	if ((infix[a] == ')' || infix[a] == '&' || infix[a] == '^' )&&( infix[a] != 'T' && infix[a] != 'F'))	//if not valid character after operand
		return false;
	if ((infix[b] == '(' || infix[b] == '&' || infix[b] == '^' )&&( infix[b] != 'T' && infix[b] != 'F'))	//if not valid character before operand
		return false;
	return true;
}

int main()
{
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^"  &&  answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()) &T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
	assert(evaluate(" !(T&F)", pf, answer) == 0 && pf == "TF&!" && answer);
	assert(evaluate(" (F)&T", pf, answer) == 0 && pf == "FT&" && !answer);
	assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0 && answer);
	assert(evaluate("T^F&F", pf, answer) == 0 && answer);
	assert(evaluate("!T&F", pf, answer) == 0 && !answer);
	assert(evaluate("!(T&F)", pf, answer) == 0 && answer);
	assert(evaluate("T ^ !F", pf, answer) == 0 && !answer);
	assert(evaluate("T^(F)", pf, answer) == 0 && answer);
	assert(evaluate("(F)", pf, answer) == 0 && !answer);
	assert(evaluate("T", pf, answer) == 0 && answer);
	assert(evaluate("(T^T)(T^T)", pf, answer) == 1);
	assert(evaluate("F^(&T)", pf, answer) == 1);
	assert(evaluate("F^&T)", pf, answer) == 1);
	assert(evaluate("&T)", pf, answer) == 1);
	cout << "Passed all tests" << endl;

}