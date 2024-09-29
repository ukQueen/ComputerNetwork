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
	void AddMessage(vector<int> message);
	
	void menu();
	void printInfo();
	int checking_input(int max);
	void adding_msg();

	// Сеттеры
	void setGroups(int groups) { GROUPS = groups;}
	void setCommuntators(int commutators) { COMMUTATORS = commutators; }
	void setNodes(int nodes) { NODES = nodes; }
	void setBandwidthInGroup(int bandwidth_in_group) { BANDWIDTH_IN_GROUP = bandwidth_in_group; }
	void setBandwidthBetweenGroup(int bandwidth_between_group) { BANDWIDTH_BETWEEN_GROUP = bandwidth_between_group; }

	// Геттеры
	int getGroups() const { return GROUPS; }
	int getCommutators() const { return COMMUTATORS;}
	int getNodes() const { return NODES;}
	int getBandwidthInGroup() const { return BANDWIDTH_IN_GROUP; }
	int getBandwidthBetweenGroup() const { return BANDWIDTH_BETWEEN_GROUP; }


};

