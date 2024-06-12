#include "TodoList.h"

int main()
{
	TodoList* pTodo = new TodoList();
	pTodo->StartUpdate();

	delete pTodo;
	return 0;
}    