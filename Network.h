#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>


using namespace std;

class Network {

	int GROUPS = 5; //количество групп
	int COMMUTATORS= 2; //количество коммутаторов в группе
	int NODES = 1; //количество узлов на коммутатор
	int BANDWIDTH_IN_GROUP = 4; //пропускная способность внутри группы
	int BANDWIDTH_BETWEEN_GROUP = 2; //пропускная способность между группами


	//int count_groups; 
	int count_commutators;
	int count_nodes;
	int count_vertex; //количество всех вершин (узлы + коммутаторы)
	//int bandwidth_in_group;
	//int bandwidth_between_group;
	vector<vector<int>> messages;
	vector<vector<string>> status;
	
	//vector<vector<int>> matrix_adj; //Матрица смежности
	//vector<vector<int>> matrix_wght; //Матрица весов
	//vector<int> vertex_degree; //степени вершин
	vector<vector<int>> matrix_bandwidth; //Матрица пропусных способностей
	//vector<vector<int>> matrix_cost; //Матрица стоимости


	void print_matrix(string str, vector<vector<int>> matr);
	

public:
	Network();
	
	void Print_matrix_bandwidth();
	
	void menu();
	int checking_input(int max);
	void adding_msg();

};

