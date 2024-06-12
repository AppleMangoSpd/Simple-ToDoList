#pragma once
#include <vector>
#include <string>
#include <fstream>


enum ESelection
{
	SHOW_ALL_TODO = 1, ADD_TODO, DELETE_TODO, CHECK_TODO, SHOW_ALL_DONE, QUIT
};

class Todo;

class TodoList
{
public:
	TodoList();
	~TodoList();
	void StartUpdate();
private:
	void Init();
	void LoadTxt(std::string name);
	void SaveTxt(std::string name);

	void Update();

	void ShowMenu();
	void SelectMenu();

	void AddTodo();
	void DeleteTodo();
	void PrintTodoVec(std::vector<Todo*> vec) const;
	void CheckTodo();
	void Reset();
	void Quit();

	void DeleteAllTodo(std::vector<Todo*> vec);

	void PauseTillAnyInput() const;


	std::vector<Todo*> todoVec;
	std::vector<Todo*> doneVec;
	std::string todoVecTxtName;
	std::string doneVecTxtName;
	std::ifstream readFile;
	std::ofstream writeFile;
	bool isRun;
};