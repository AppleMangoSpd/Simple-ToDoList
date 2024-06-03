#include "ToDoList.h"

#include <iostream>
#include <conio.h>

ToDoList::ToDoList()
{
	todoList = {};
	doneList = {};
	isRun = false;
	this->Init();
}

ToDoList::~ToDoList()
{
	//add to txt
	writeFile.open("ToDoList.txt");
	if (writeFile.is_open())
	{
		for (std::string i : todoList)
		{
			writeFile << i + '\n';
		}
	}
	writeFile.close();
	
	writeFile.open("DoneList.txt");
	if (writeFile.is_open())
	{
		for (std::string i : doneList)
		{
			writeFile << i + '\n';
		}
	}
	writeFile.close();

	if (readFile.is_open())
	{
		readFile.close();
	}
	if (writeFile.is_open())
	{
		writeFile.close();
	}

}

void ToDoList::StartUpdate()
{
	isRun = true;
	this->Update();
}

void ToDoList::Init()
{
	std::cout << "TO DO List started" << std::endl;
	
	this->LoadTxt("ToDoList.txt");
	this->LoadTxt("DoneList.txt");

	this->PauseTillAnyInput();
}

void ToDoList::LoadTxt(std::string name)
{
	if (name != "ToDoList.txt" && name != "DoneList.txt")
	{
		std::cout << "Can not use " << name << " file." << std::endl;
		return;
	}
	// File io set
	readFile.open(name);

	// Failed to find/open .txt
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
		this->PauseTillAnyInput();
		return;
	}

	std::cout << "readFile.is_open() is true." << std::endl;
	std::cout << "Load List from " << name <<  "..." << std::endl;

	// Check if .txt is empty
	if (readFile.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << name << " is empty." << std::endl;
		this->PauseTillAnyInput();
		return;
	}

	if (name == "ToDoList.txt")
	{
		// Move list from .txt to vector with loop
		while (readFile.peek() != std::ifstream::traits_type::eof())
		{
			std::string tempStr;
			getline(readFile, tempStr);
			todoList.push_back(tempStr);
		}
	}
	else if (name == "DoneList.txt")
	{
		// Move list from .txt to vector with loop
		while (readFile.peek() != std::ifstream::traits_type::eof())
		{
			std::string tempStr;
			getline(readFile, tempStr);
			doneList.push_back(tempStr);
		}
	}
	std::cout << "ToDoList.txt Load complete!" << std::endl;
	readFile.close();
}

void ToDoList::Update()
{
	while (isRun)
	{
		this->ShowMenu();
		this->SelectMenu(); 
	}
}

void ToDoList::ShowMenu()
{
	std::cout << "----------------------------" << std::endl;
	std::cout << "ToDo List Menu" << std::endl;

	std::cout << "1. Show All ToDo" << std::endl;
	std::cout << "2. Add ToDo" << std::endl;
	std::cout << "3. Delete ToDo" << std::endl;
	std::cout << "4. Check ToDo" << std::endl;
	std::cout << "5. Show All Done" << std::endl;
	std::cout << "6. Quit" << std::endl;

	std::cout << "----------------------------" << std::endl;
}

void ToDoList::SelectMenu()
{
	int input{};
	std::cin >> input;
	std::cin.ignore();

	std::cout << "----------------------------" << std::endl;

	switch (input)
	{
	case SHOW_ALL_TODO:
		this->PrintToDo();
		break;
	case ADD_TODO:
		this->AddToDo();
		break;
	case DELETE_TODO:
		this->DeleteToDo();
		break;
	case CHECK_TODO: 
		this->CheckToDo();
		break;
	case SHOW_ALL_DONE:
		this->PrintDone();
		break;
	case QUIT: 
		this->Quit();
		break;
	default:
		break;
	}
}

void ToDoList::AddToDo()
{
	std::string todo;
	std::cout << "Please enter todo : ";
	std::getline(std::cin, todo);

	todoList.push_back(todo);
	std::cout << "Todo added" << std::endl;

	//std::cin.ignore();
	this->PauseTillAnyInput();
}

void ToDoList::DeleteToDo()
{
	if (todoList.empty())
	{
		std::cout << "Todo List is empty!" << std::endl;
		this->PauseTillAnyInput();
		return;
	}
	for (int i = 0; i < todoList.size(); i++)
	{
		std::cout << i + 1 << " " << todoList[i] << std::endl;
	}

	int index{};
	std::cout << "Enter delete index : ";
	std::cin >> index;
	std::cin.ignore();

	if (index < todoList.size())
	{
		std::cout << todoList[index - 1] << " is deleted" << std::endl;
		todoList.erase(todoList.begin()+ index - 1);
		this->PauseTillAnyInput();
		return;
	}
	else
	{
		std::cout << "Out of index" << std::endl;
		this->PauseTillAnyInput();
		return;
	}
}

void ToDoList::PrintToDo() const
{
	if (todoList.empty())
	{
		std::cout << "Todo List is empty!" << std::endl;
		this->PauseTillAnyInput();
		return;
	}

	for (int i = 0; i < todoList.size(); i++)
	{
		std::cout << i + 1 << " " << todoList[i] << std::endl;
	}

	this->PauseTillAnyInput();
}

void ToDoList::PrintDone() const
{
	if (doneList.empty())
	{
		std::cout << "Done List is empty!" << std::endl;
		this->PauseTillAnyInput();
		return;
	}

	for (int i = 0; i < doneList.size(); i++)
	{
		std::cout << i + 1 << " " << doneList[i] << std::endl;
	}

	this->PauseTillAnyInput();
}

void ToDoList::CheckToDo()
{
	if (todoList.empty())
	{
		std::cout << "Todo List is empty!" << std::endl;
		this->PauseTillAnyInput();
		return;
	}

	for (int i = 0; i < todoList.size(); i++)
	{
		std::cout << i + 1 << " " << todoList[i] << std::endl;
	}

	int index{};
	std::cout << "Enter check index : ";
	std::cin >> index;
	std::cin.ignore();

	if (index < todoList.size())
	{
		std::cout << todoList[index - 1] << " is check as done" << std::endl;
		doneList.push_back(todoList[index - 1]);

		todoList.erase(todoList.begin() + index - 1);
		this->PauseTillAnyInput();
		return;
	}
	else
	{
		std::cout << "Out of index" << std::endl;
	}

	PauseTillAnyInput();
}

void ToDoList::Reset()
{
	todoList.clear();
	doneList.clear();
}

void ToDoList::Quit()
{
	std::cout << "Quit TO DO Lists." << std::endl;
	std::cout << "Goodbye!." << std::endl;

	isRun = false;
}

void ToDoList::PauseTillAnyInput() const
{
	std::cout << "Press any key to continue..." << std::endl;
	_getch();
	//clear screen
	std::cout << "\033[2J\033[1;1H";
}