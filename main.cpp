#include "ToDoList.h"

int main()
{
	ToDoList* pToDo = new ToDoList();
	pToDo->StartUpdate();

	delete pToDo;
	return 0;
}