#include "pch.h"
#include "StringEditor.h"
#include <iostream>
#include <string>
#include <algorithm>

StringEditor::StringEditor()
{
}


StringEditor::~StringEditor()
{
}

std::string StringEditor::RemoveSpaces(std::string str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}
