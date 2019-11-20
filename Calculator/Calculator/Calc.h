#include <iostream>
#include <string>
#include <list>

#include "StringEditor.h"


struct Node
{
	int data;
	Node *next;
	Node *last;

	Node()
	{
		next = nullptr;
		last = nullptr;
	}

	~Node()
	{
		delete next;
		delete last;
	}
};

#pragma once
class Calc
{
private :
	const std::string undo = "undo";
	const std::string redo = "redo";

	const std::string quit = "quit";
public:
	Calc();
	~Calc();

	void Use();

	void Input();
	void Output();
	void Calculate();

	int OperatorPosition(std::string s);


	bool CheckForUndoRedo();
	void Undo();
	void Redo();

	bool CheckForQuit();

	void NewNode(int i);
	Node * FreeNodesAfterNode(Node *n);

	Node * Header(Node *n);
	
	Node *currentNode;
	Node *InitialValue;
	std::string str;

	bool inUse;
};

