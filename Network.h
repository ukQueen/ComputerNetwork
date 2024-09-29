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
	int BANDWIDTH_IN_GROUP; //пропускная способность внутри группы
	int BANDWIDTH_BETWEEN_GROUP; //пропускная способность между группами



	//int count_groups; 
	int count_commutators;
	int count_nodes;
	int count_vertex; //количество всех вершин (узлы + коммутаторы)
	//int bandwidth_in_group;
	//int bandwidth_between_group;
	vector<vector<int>> messages;
	vector<vector<string>> status;

	vector<vector<int>> path;

	
	//vector<vector<int>> matrix_adj; //Матрица смежности
	//vector<vector<int>> matrix_wght; //Матрица весов
	//vector<int> vertex_degree; //степени вершин
	vector<vector<int>> matrix_bandwidth; //Матрица пропусных способностей
	//vector<vector<int>> matrix_cost; //Матрица стоимости
	vector<vector<int>> matrix_load; //Матрица загруженности


	void print_matrix(string str, vector<vector<int>> matr);
	

	bool CheckBoolVector(vector<bool>);
	int Min_Index(vector<int>, vector<bool>, int cost);

public:
	vector<int> Dijkstra_algorythm(vector<int> message);//, vector<vector<int>> matrix);
	Network();
	Network(int GROUPS,	int COMMUTATORS, int NODES, int BANDWIDTH_IN_GROUP, int BANDWIDTH_BETWEEN_GROUP);
	void Print_matrix_bandwidth();
	void NextStep();
	
	void menu();
	int checking_input(int max);
	void adding_msg();

};

