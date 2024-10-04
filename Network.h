#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>


using namespace std;

class Network
{
	int GROUPS; //количество групп
	int COMMUTATORS; //количество коммутаторов в группе
	int NODES; //количество узлов на коммутатор
	int BANDWIDTH_IN_GROUP; //пропускна€ способность внутри группы
	int BANDWIDTH_BETWEEN_GROUP; //пропускна€ способность между группами

	int count_commutators;
	int count_nodes;
	int count_vertex; //количество всех вершин (узлы + коммутаторы)
	vector<vector<int>> messages;
	vector<vector<string>> status;
	vector<vector<int>> path;
	vector<int> reserv;//сколько зарезервировано на шаге1 в каждом сообщении
	vector<int> reminder; //сколько осталось передать от одной вершины к другой
	vector<vector<int>> matrix_bandwidth; //ћатрица пропусных способностей
	vector<vector<int>> matrix_load; //ћатрица загруженности
	int counter;//счетчик шагов

	void print_matrix(string str, vector<vector<int>> matr);
	bool CheckBoolVector(vector<bool>);
	int Min_Index(vector<int>, vector<bool>, int cost);
	bool Can_Make_Route(vector<int> message);
	bool Can_Dijkstra(vector<int> message);
	vector<int> Dijkstra_algorythm(vector<int> message);//, vector<vector<int>> matrix);
	void Print_matrix_bandwidth();
	void NextStep(); 
	void AddMessage(vector<int> message);
	string statusInfo(int index);
	void adding_msg();

public:

	Network();
	Network(int GROUPS,	int COMMUTATORS, int NODES, int BANDWIDTH_IN_GROUP, int BANDWIDTH_BETWEEN_GROUP);
	void menu();
	void printInfo();
	int checking_input(int max);
};

