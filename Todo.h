#pragma once
#include <string>
class Todo
{
public:
	Todo() = delete;
	Todo(std::string str, int priority = 0) : TodoStr(str) {};
	~Todo() {};

	const std::string GetTodoStr() const { return TodoStr; }
private:
	const std::string TodoStr;
};