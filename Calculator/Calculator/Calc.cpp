#include "pch.h"
#include "Calc.h"
#include <iostream>
#include <string>
#include <list>

#include "StringEditor.h"

Calc::Calc()
{
	inUse = true;

	InitialValue = new Node();

	InitialValue->data = 0;
	currentNode = InitialValue;
}
Calc::~Calc()
{
}
void Calc::Use()
{
	while (inUse)
	{
		Input();
		Output();
	}
}
void Calc::Input()
{
	std::string input;
	StringEditor stringEditor;

	std::cout << "Calculator: (type 'undo' to undo and 'redo' to redo) ('quit' to quit)" << std::endl;
	std::cout << "Current Value: " << currentNode->data << std::endl;

	std::getline(std::cin, input);

	str = input;

	str = stringEditor.RemoveSpaces(str);
}

void Calc::Output()
{
	Calculate();
}

void Calc::Calculate()
{
	if (!CheckForUndoRedo() && !CheckForQuit())
	{
		int firstNumber = 0;
		int secondNumber = 0;

		int multiplyer = 1;

		int position = OperatorPosition(str);

		if (position > 0 && position < str.length())
		{
			for (int i = position - 1; i >= 0; i--)
			{
				int value = str.at(i) - '0';
				firstNumber += value * multiplyer;
				multiplyer *= 10;
			}

			multiplyer = 1;

			for (int i = str.length() - 1; i >= position + 1; i--)
			{
				int value = str.at(i) - '0';
				secondNumber += value * multiplyer;
				multiplyer *= 10;
			}

			switch (str.at(position))
			{
			case '+':
				NewNode(firstNumber + secondNumber);
				break;
			case '-':
				NewNode(firstNumber - secondNumber);
				break;
			case '*':
				NewNode(firstNumber * secondNumber);
				break;
			case '/':
				NewNode(firstNumber / secondNumber);
				break;
			default:
				break;
			}
		}
		else
		{
			std::cout << "Invalid Expresion" << std::endl;
		}
	}
}

int Calc::OperatorPosition(std::string s)
{
	int position = -1;
	int count = 0;

	for (int i = 0; i < s.length(); i++)
		if (s.at(i) == '+' || s.at(i) == '-' || s.at(i) == '*' || s.at(i) == '/')
		{
			position = i;
			count++;
		}

	if (count > 1)
		position = -2;
	std::cout << "Too Many Operators" << std::endl;

	if (position == -1)
		std::cout << "No Operator Found" << std::endl;

	return position;
}

bool Calc::CheckForUndoRedo()
{
	if (str == undo)
	{
		Undo();
		return true;
	}
	else if (str == redo)
	{
		Redo();
		return true;
	}
	else
		return false;
}

void Calc::Undo()
{
	if (currentNode->last != nullptr)
	{
		currentNode = currentNode->last;
	}
	else
	{
		std::cout << "There is nothing to undo!" << std::endl;
	}
}

void Calc::Redo()
{
	if (currentNode->next != nullptr)
	{
		currentNode = currentNode->next;
	}
	else
	{
		std::cout << "There is nothing to redo!" << std::endl;
	}
}

bool Calc::CheckForQuit()
{
	if (str == quit)
	{
		FreeNodesAfterNode(Header(currentNode));
		inUse = false;
		return true;
	}
	else
		return false;
}

void Calc::NewNode(int i)
{
	Node *newNode = new Node();
	newNode->data = i;
	newNode->last = currentNode;
	currentNode->next = newNode;
	currentNode = newNode;
	
}

Node * Calc::FreeNodesAfterNode(Node * n)
{
	if (n->next == nullptr)
	{
		delete n;
		return n;
	}
	else
	{
		FreeNodesAfterNode(n->next);
	}
}

Node * Calc::Header(Node * n)
{
	if (n->last == nullptr)
	{
		return n;
	}
	else
	{
		return Header(n->last);
	}
}
