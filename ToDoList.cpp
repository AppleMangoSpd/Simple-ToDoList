#include "TodoList.h"

#include <iostream>
#include <conio.h>

#include "Todo.h"

TodoList::TodoList()
{
	todoVec = {};
	doneVec = {};
	todoVecTxtName = "ToDoList.txt";
	doneVecTxtName = "DoneList.txt";

	isRun = false;
	this->Init();
}

TodoList::~TodoList()
{
	if (readFile.is_open())
	{
		readFile.close();
	}
	if (writeFile.is_open())
	{
		writeFile.close();
	}

	std::cout << "Goodbye!." << std::endl;
}

void TodoList::StartUpdate()
{
	isRun = true;
	this->Update();
}

void TodoList::Init()
{
	std::cout << "TO DO List started" << std::endl;
	
	this->LoadTxt(todoVecTxtName);
	this->PauseTillAnyInput();
	this->LoadTxt(doneVecTxtName);
	this->PauseTillAnyInput();

	std::cout << "Load completed" << std::endl;
	this->PauseTillAnyInput();
}

void TodoList::LoadTxt(std::string name)
{
	if (name != todoVecTxtName && name != doneVecTxtName)
	{
		std::cout << "Can not use " << name << " file." << std::endl;
		return;
	}
	// File io set
	readFile.open(name);

	// Check if failed to find/open .txt
	if (!readFile.is_open())
	{
		std::cout << "readFile.is_open() is false." << std::endl;
		std::cout << "Create new file..." << std::endl;

		writeFile.open(name);
		if (!writeFile.is_open())
		{
			std::cout << "Failed to create new file" << std::endl;
			return;
		}
		std::cout << "New file created!" << std::endl;

		writeFile.close();
		return;
	}

	std::cout << "readFile.is_open() is true." << std::endl;
	std::cout << "Load List from " << name <<  "..." << std::endl;

	// Check if .txt is empty
	if (readFile.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << name << " is empty." << std::endl;
		return;
	}

	// Move from .txt to vector with loop
	if (name == todoVecTxtName)
	{
		while (readFile.peek() != std::ifstream::traits_type::eof())
		{
			std::string tempStr;
			getline(readFile, tempStr);
			Todo* todoPtr = new Todo(tempStr, 0);
			todoVec.push_back(todoPtr);
		}
	}
	else if (name == doneVecTxtName)
	{
		while (readFile.peek() != std::ifstream::traits_type::eof())
		{
			std::string tempStr;
			getline(readFile, tempStr);
			Todo* todoPtr = new Todo(tempStr, 0);
			doneVec.push_back(todoPtr);
		}
	}
	std::cout << name << " Load complete!" << std::endl;
	readFile.close();
}

void TodoList::SaveTxt(std::string name)
{
	if (name != todoVecTxtName && name != doneVecTxtName)
	{
		std::cout << "Can not use " << name << " file." << std::endl;
		return;
	}

	//add to txt
	writeFile.open(name);
	if (!writeFile.is_open())
	{
		std::cout << "Failed to open " << name << " for wirteFile" << std::endl;
		return;
	}

	if (name == todoVecTxtName)
	{
		for (Todo* i : todoVec)
		{
			writeFile << i->GetTodoStr() + '\n';
		}
	}
	else if (name == doneVecTxtName)
	{
		for (Todo* i : doneVec)
		{
			writeFile << i->GetTodoStr() + '\n';
		}
	}
	writeFile.close();
}

void TodoList::Update()
{
	while (isRun)
	{
		this->ShowMenu();
		this->SelectMenu(); 
	}
}

void TodoList::ShowMenu()
{
	std::cout << "----------------------------" << std::endl;
	std::cout << "ToDo List Menu" << std::endl;

	std::cout << "1. Show All Todo" << std::endl;
	std::cout << "2. Add Todo" << std::endl;
	std::cout << "3. Delete Todo" << std::endl;
	std::cout << "4. Check Todo" << std::endl;
	std::cout << "5. Show All Done" << std::endl;
	std::cout << "6. Quit" << std::endl;

	std::cout << "----------------------------" << std::endl;
}

void TodoList::SelectMenu()
{
	int input{};
	std::cin >> input;
	std::cin.ignore();
	std::cout << "----------------------------" << std::endl;

	switch (input)
	{
	case SHOW_ALL_TODO:
		std::cout << "Show All Todo" << std::endl;
		this->PrintTodoVec(todoVec);
		break;
	case ADD_TODO:
		std::cout << "Add Todo" << std::endl;
		this->AddTodo();
		break;
	case DELETE_TODO:
		std::cout << "Delete Todo" << std::endl;
		this->DeleteTodo();
		break;
	case CHECK_TODO: 
		std::cout << "Check Todo" << std::endl;
		this->CheckTodo();
		break;
	case SHOW_ALL_DONE:
		std::cout << "Show All Done" << std::endl;
		this->PrintTodoVec(doneVec);
		break;
	case QUIT: 
		std::cout << "Quit" << std::endl;
		this->Quit();
		break;
	default:
		break;
	}

	this->PauseTillAnyInput();
}

void TodoList::AddTodo()
{
	std::string todo;
	std::cout << "Please enter todo : ";
	std::getline(std::cin, todo);

	todoVec.push_back(new Todo(todo));
	std::cout << "Todo added" << std::endl;
	//std::cin.ignore();
}

void TodoList::DeleteTodo()
{
	this->PrintTodoVec(todoVec);

	int index{};
	std::cout << "Enter delete index : ";
	std::cin >> index;
	index--;

	if (index < todoVec.size())
	{
		std::cout << todoVec[index]->GetTodoStr() << " is deleted" << std::endl;
		todoVec.erase(todoVec.begin()+ index);
		return;
	}
	else
	{
		std::cout << "Out of index" << std::endl;
		return;
	}
}

void TodoList::PrintTodoVec(std::vector<Todo*> vec) const
{
	if (vec.empty())
	{
		std::cout << "vec is empty" << std::endl;
		return;
	}
	for (int i = 0; i < vec.size(); i++)
	{
		std::cout << i + 1 << ". " << vec[i]->GetTodoStr() << std::endl;
	}
	return;
}

void TodoList::CheckTodo()
{
	this->PrintTodoVec(todoVec);

	int index{};
	std::cout << "Enter check index : ";
	std::cin >> index;

	if (index < todoVec.size())
	{
		index--;
		std::cout << todoVec[index]->GetTodoStr() << " is check as done" << std::endl;
		doneVec.push_back(todoVec[index]);

		todoVec.erase(todoVec.begin() + index);
		return;
	}
	else
	{
		std::cout << "Out of index" << std::endl;
	}
	this->PauseTillAnyInput();
}

void TodoList::Reset()
{
	todoVec.clear();
	doneVec.clear();
}

void TodoList::Quit()
{
	std::cout << "Quit TO DO Lists." << std::endl;

	// Save all to .txt
	this->SaveTxt(todoVecTxtName);
	this->SaveTxt(doneVecTxtName);

	// Delete all in todoVec
	this->DeleteAllTodo(todoVec);
	this->DeleteAllTodo(doneVec);

	isRun = false;
}

void TodoList::DeleteAllTodo(std::vector<Todo*> vec)
{
	for (Todo* todo : vec)
	{
		delete todo;
	}
}

void TodoList::PauseTillAnyInput() const
{
	std::cout << "Press any key to continue..." << std::endl;
	_getch();
	//clear screen
	std::cout << "\033[2J\033[1;1H";
}