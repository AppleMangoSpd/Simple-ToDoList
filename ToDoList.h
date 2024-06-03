#pragma once
#include <vector>
#include <string>
#include <fstream>

enum ESelection
{
	SHOW_ALL_TODO = 1, ADD_TODO, DELETE_TODO, CHECK_TODO, SHOW_ALL_DONE, QUIT
};
class ToDoList
{
public:
	ToDoList();
	~ToDoList();
	void StartUpdate();
private:
	void Init();
	void LoadTxt(std::string name);

	void Update();

	void ShowMenu();
	void SelectMenu();

	void AddToDo();
	void DeleteToDo();
	void PrintToDo() const;
	void PrintDone() const;
	void CheckToDo();
	void Reset();
	void Quit();

	void PauseTillAnyInput() const;

	std::vector<std::string> todoList;
	std::vector<std::string> doneList;
	std::ifstream readFile;
	std::ofstream writeFile;
	bool isRun;
};