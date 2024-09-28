#include "Network.h"

Network::Network():Network(5,2,1,4,2) {}

Network::Network(int GROUPS, int COMMUTATORS, int NODES, int BANDWIDTH_IN_GROUP, int BANDWIDTH_BETWEEN_GROUP)  {
	this->GROUPS = GROUPS; 
	this->COMMUTATORS = COMMUTATORS;
	this->NODES = NODES;
	this->BANDWIDTH_IN_GROUP = BANDWIDTH_IN_GROUP;
	this->BANDWIDTH_BETWEEN_GROUP = BANDWIDTH_BETWEEN_GROUP;

	count_commutators = GROUPS * COMMUTATORS; 
	count_nodes = count_commutators * NODES; 
	count_vertex = count_commutators + count_nodes;

	vector<vector<int>> new_bandwidth(count_vertex, vector<int>(count_vertex, 0));
	matrix_bandwidth = new_bandwidth;

<<<<<<< HEAD
	for (int i = 0, k = NODES, ii = count_nodes; i < count_nodes; i++) {
=======
	for (int i = 0, ii=count_nodes, k = NODES; i < count_nodes;i++) {
>>>>>>> origin/TestingMain
		k--;
		matrix_bandwidth[i][ii] = BANDWIDTH_IN_GROUP; //пропускная способность в группе
		matrix_bandwidth[ii][i] = BANDWIDTH_IN_GROUP;
		if (k == 0) {
			ii++;
			k = NODES;
<<<<<<< HEAD
		}
=======
		}	
>>>>>>> origin/TestingMain
	}

	for (int i = 0, back=COMMUTATORS-1, group=GROUPS-1; i < COMMUTATORS; i++, back--, group-=COMMUTATORS) {

		for (int ii = count_nodes + i, group_right=group ; ii < count_vertex; ii+=COMMUTATORS, group_right++) {
			if (group_right >= GROUPS) {
				group_right -= GROUPS;
			}
			for (int iii = 0, current_group = group_right; iii < GROUPS/COMMUTATORS; iii++) {
				current_group = (group_right - iii) < 0 ? GROUPS + (group_right - iii) : group_right - iii;
				matrix_bandwidth[ii][count_nodes + current_group * COMMUTATORS + back] = BANDWIDTH_BETWEEN_GROUP;//пропускная способность между группами
				matrix_bandwidth[count_nodes + current_group * COMMUTATORS + back][ii] = BANDWIDTH_BETWEEN_GROUP;
			}
		}
	}

	for (int i = 0; i < GROUPS; i++) {
		for (int ii = count_nodes + i * COMMUTATORS; ii < count_nodes + (i + 1) * COMMUTATORS; ii++) {
			for (int iii = ii; iii < count_nodes + (i + 1) * COMMUTATORS; iii++) {
				if (ii != iii) {
					matrix_bandwidth[ii][iii] = BANDWIDTH_IN_GROUP;//пропускная способность в группе
					matrix_bandwidth[iii][ii] = BANDWIDTH_IN_GROUP;
				}
			}
		}
	}

	matrix_load = matrix_bandwidth;
}

void Network::print_matrix(string str, vector<vector<int>> matr) {
	
	string s = to_string(matr.size());
	cout << "\n   ";
	cout << str << "\n\n";

	for (int i = 0; i < s.size(); i++) {
		cout << " ";
	}
	cout << " | ";
	for (int i = 0; i < matr[0].size(); i++) {
		if (i != 0)
			cout << setw(4);
		else
			cout << setw(2);
		cout << i;
	}
	cout << endl;

	for (int i = 0; i < s.size(); i++) {
		cout << "-";
	}
	for (int i = 0; i < matr[0].size(); i++) {
		cout << "----";
	}
	cout << endl;
	for (int i = 0; i < matr.size(); i++) {
		cout << setw(s.size()) << i << " | ";
		for (int j = 0; j < matr[i].size(); j++) {
			if (j != 0)
				cout << setw(4);
			else
				cout << setw(2);
			cout << matr[i][j];
		}
		cout << "\n";
	}
	cout << "\n";
}


void Network::Print_matrix_bandwidth() {
	print_matrix("Matrix_adj", matrix_bandwidth);	
}

<<<<<<< HEAD

vector<int> Network::Dijkstra_algorythm(vector<int> message) {
	int index_from = message[0];
	int index_to = message[2];
	int cost = message[1];

	int count = 0;
	vector<int> vertex(count_vertex);
	for (int i = 0; i < vertex.size(); i++) {
		vertex[i] =  INT_MAX;
	}
	vector<bool> vertex_check(count_vertex, false);
	vector<vector<int>> route(count_vertex);
	vertex[index_from] = 0;

	int current;

	while (CheckBoolVector(vertex_check) == false) {
		current = Min_Index(vertex, vertex_check, cost) ;
		if (current == -1)
			break;
		vertex_check[current] = true;

		for (int i = 0; i < matrix_load[current].size(); i++) {
			if (matrix_load[current][i] != 0) {
				//bool condition = vertex[current] + matrix_load[current][i] <= vertex[i];
				int buf = cost / matrix_load[current][i] + 1;
				if (!(current == index_from || current == index_to)) {
					buf++; //прибавляем штраф
				}
				//bool condition = vertex[current] + matrix_load[current][i] <= vertex[i];
				bool condition = vertex[current] + buf <= vertex[i];
					if (condition) {

					vertex_check[i] = false;
					route[i].clear();
					route[i] = route[current];
					route[i].push_back(current);
					vertex[i] = vertex[current] + buf;
				}
			}
		}
	}
	for (int i = 0; i < vertex.size(); i++) {
		if (vertex[i] == INT_MAX || vertex[i] == INT_MAX + 1)
			vertex[i] = 0;
	}
	for (int i = 0; i < route.size(); i++) {
		if (route[i].size() != 0)
			route[i].push_back(i);
	}

	cout << "Растояние/стоимость: " << vertex[index_to] << endl;
	cout << "Путь: ";
	if (route[index_to].size() == 0) {
		cout << "Пути не существует\n";
	}
	else
		for (int i = 0; i < route[index_to].size(); i++) {
			cout << route[index_to][i];
			if (i != route[index_to].size() - 1)
				cout << " -> ";
		}

	return route[index_to];
}


int Network::Min_Index(vector<int> v, vector<bool> fl, int cost) {
	int result = INT_MAX;
	int index = -1;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < result && fl[i] == false) {
			result = v[i];
			index = i;
		}
	}
	return index;
}


bool Network::CheckBoolVector(vector<bool> v) {
	bool result = true;
	for (int i = 0; i < v.size(); i++) {
		result = result && v[i];
	}
	return result;
}

void Network::NextStep(){}
=======
int Network::checking_input(int max) {
	int n;

	while (true) {
		cin >> n;
		// Проверяем, является ли введенное значение целым числом и находится в допустимых пределах
		if (cin.fail() || n < 0 || n > max || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер ввода
			cout << "Ошибка! Некорректный ввод! " << endl;
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break; // Ввод корректен, выходим из цикла
		}
	}
	return n;
}


void Network::adding_msg() {
	string input;
	int dep, length, arr;
	char space1, space2;

	cout << "Введите сообщение в формате АДРЕС_ИСТОЧНИКА ДЛИНА_СООБЩЕНИЯ АДРЕС_ПОЛУЧАТЕЛЯ, " << endl;
	cout << "где адреса находятся в пределах от 0 до " << count_nodes - 1 << " включительно" << endl;

	do {

		getline(cin, input);
		istringstream iss(input);

		if (iss >> dep >> length >> arr) {

			if (dep == arr) {
				cout << "Введите различные узел отправления и прибытия" << endl;
			}
			else if (length <= 0) {
				cout << "Длина сообщения должна быть положительной!" << endl;
			}
			else if (dep >= 0 && dep < count_nodes && arr >= 0 && arr < count_nodes && iss.eof()) {
				break;
			}
			else {
				cout << "Некорретный ввод! Попробуйте снова" << endl;
			}
		}
		else cout << "Некорретный ввод! Попробуйте снова" << endl;

	} while (true);

	messages.push_back(vector<int>());
	messages.back().push_back(dep);
	messages.back().push_back(length);
	messages.back().push_back(arr);
	
	print_matrix("Матрица сообщений", messages);

}


void Network::menu() {

	cout << "Программа, моделирующая работу механизма передачи сообщения в коммуникационной сети суперкомпьютера" << endl;

	bool secondMenu = false;

	while (true) {
		if (!secondMenu) {

			cout << "\n Выберите действие: \n";
			cout << " [1] Отправить сообщение \n";
			cout << " [0] Выход из программы \n";

			int b = checking_input(1);

			switch (b) {

			case 1:
				adding_msg();
				secondMenu = true;
				break;


			case 0:
				cout << "Выход из программы...\n";
				return;
			}
		}
		else {

			cout << "\n Выберите действие: \n";
			cout << " [1] Отправить сообщения (до 10 штук) \n";
			cout << " [2] Следующий шаг \n";
			cout << " [0] Выход из программы \n";

			int b = checking_input(2);
			int msg_count;

			switch (b) {
			case 1:

				cout << "Введите количество сообщений, которое хотите отправить (от 0 до 10): ";
				msg_count = checking_input(11);

				for (int i = 0; i < msg_count; i++) {
					adding_msg();
				}
				
				break;

			case 2:
				if (messages.size() == 0) {
					cout << " Нет активных процессов передачи сообщений!" << endl;
					secondMenu = false;
					break;
				}

				cout << "Переход к следующему шагу.\n";
				break;

			case 0:
				cout << "Выход из программы...\n";
				return;
			}
		}
	}
}




>>>>>>> origin/TestingMain
