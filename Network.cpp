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


	for (int i = 0, ii=count_nodes, k = NODES; i < count_nodes;i++) {
		k--;
		matrix_bandwidth[i][ii] = BANDWIDTH_IN_GROUP; //пропускная способность в группе
		matrix_bandwidth[ii][i] = BANDWIDTH_IN_GROUP;
		if (k == 0) {
			ii++;
			k = NODES;
		}	
	}


	for (int i = 0, back=COMMUTATORS-1, group=GROUPS-1; i < COMMUTATORS; i++, back--, group-=GROUPS/COMMUTATORS) {


		for (int ii = count_nodes + i, group_right=group ; ii < count_vertex; ii+=COMMUTATORS, group_right++) {
			if (group_right >= GROUPS) {
				group_right -= GROUPS;
			}
			for (int iii = 0, current_group = group_right; iii < GROUPS/COMMUTATORS; iii++) {
				current_group = (group_right - iii) < 0 ? GROUPS + (group_right - iii) : group_right - iii;
				int buf = count_nodes + current_group * COMMUTATORS + back; 
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
				int buf = cost / matrix_load[current][i];
				buf = cost % matrix_load[current][i]==0? buf :buf + 1;
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

	//TODO: закончить реализацию маршрута
	//cuurent_node будет хранить новый маршрут 
	//допустим был маршрут 1->(2/5 + 4/5 + 5/5 + фтраф) 20-> (2/5 + 4/5 + 5/5 + фтраф) 21-> (2/5 + 4/5 + 5/5) 2
	//преобразуется в 1 20 1 20 1 20 20 20 ! 20 21 20 21 20 21 21 21 ! 21 2 21 2 21 2  
	//шаг по два элемента в массиве (так будет проще)

	vector<int> current_route;
	for (int i = 0; i < route[index_to].size() - 1; i++) {
		int index_1;
		int index_2;
		int cost_inner;
		int broad;
		if (i != route[index_to].size() - 2) {
			index_1 = route[index_to][i];
			index_2 = route[index_to][i + 1];
			cost_inner = matrix_load[index_1][index_2];

			broad = cost / cost_inner;
			broad = cost % cost_inner == 0 ? broad : broad+1;
			for (int ii = 0; ii < broad; ii++) {
				current_route.push_back(index_1);
				current_route.push_back(index_2);
			}

			//добавим штраф
			current_route.push_back(index_2);
			current_route.push_back(index_2);
		}
		else {
			cost_inner = this->BANDWIDTH_IN_GROUP;
			index_1 = route[index_to][i];
			index_2 = route[index_to][i+1];

			broad = cost / cost_inner;
			broad = cost % cost_inner == 0 ? broad : broad+1;
			for (int ii = 0; ii < broad; ii++) {
				current_route.push_back(index_1);
				current_route.push_back(index_2);
			}
		}
	}


	cout << "\nПуть: ";
	if (route[index_to].size() == 0) {
		cout << "Пути не существует\n";
	}
	else
		for (int i = 0; i < current_route.size(); i++) {
			cout << current_route[i];
			if (i != current_route.size() - 1)
				cout << " -> ";
		}

	return current_route;
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

	/*messages.push_back(vector<int>());
	messages.back().push_back(dep);
	messages.back().push_back(length);
	messages.back().push_back(arr);*/
	this->AddMessage({dep, length, arr});
	
	print_matrix("Матрица сообщений", messages);

}

string Network::statusInfo(int index) {

	if(status[index].size() != 0) return status[index][0];
	else {

		int a = path[index][0];
		int b = path[index][1];

		if (path[index][0] == path[index][1]) {
			string str = "Штраф. Находится в" + to_string(a) + "коммутаторе";
			return str;
		}

		int i = 0;
		while (path[index][i] == a && path[index][i + 1] == b) {
			i += 2;
		}

		int done = reminder[index];
		string str = "На этом шаге передано " + to_string(done) + "/" + to_string(messages[index][1]);

		return str;

	}

}


void Network::menu() {

	bool mainMenu = true;
	bool secondMenu = false;
	int msg_count;

	while (true) {

		if (!secondMenu) {

			cout << "\n Выберите действие: \n";
			cout << " [1] Отправить сообщения (до 10 штук) \n";
			cout << " [0] Сменить студента \n";

			int b = checking_input(1);

			switch (b) {

			case 1:

				cout << "Введите количество сообщений, которое хотите отправить (от 0 до 10): ";
				msg_count = checking_input(11);

				for (int i = 0; i < msg_count; i++) {
					adding_msg();
				}
				secondMenu = true;
				break;

			case 0:
				cout << "Выход в главное меню...\n";
				return;
			}
		}
		else {

			if (messages.size() != 0) {
				for (int i = 0; i < messages.size(); i++) {
					cout << "{" << messages[i][0] << "," << messages[i][1] << "," << messages[i][2];
					cout << "} : " << statusInfo(i) << endl;
				}
			}
			else cout << "Нет сообщений для пересылки!" << endl;
			
			cout << "\n Выберите действие: \n";
			cout << " [1] Отправить сообщения (до 10 штук) \n";
			cout << " [2] Следующий шаг \n";
			cout << " [0] Сменить студента \n";

			int b = checking_input(2);

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
				NextStep();
				break;

			case 0:
				cout << "Выход в главное меню...\n";
				return;
			}
		}
	}
}


void Network::AddMessage(vector<int> message) {

	//обработать ситуацию когда соо из одного источника
	auto path = Dijkstra_algorythm(message);
	this->messages.push_back(message);
	this->path.push_back(path);
	this->status.push_back({ "Сообщение ожидает отправки" });
	this->reminder.push_back(message[1]);
	this->reserv.push_back(true);////////////////////

}

void Network::printInfo() {

	cout << "\nКоличество групп: " << GROUPS << endl;
	cout << "Количество коммутаторов в группе: " << COMMUTATORS << endl;
	cout << "Количество узлов на коммутатор: " << NODES << endl;
	cout << "Пропускная способность внутри группы: " << BANDWIDTH_IN_GROUP << endl;
	cout << "Пропускная способность между группами: " << BANDWIDTH_BETWEEN_GROUP << endl;

}

void Network::NextStep() {

	for (int i = 0; i < messages.size(); i++) {
		if (status[i][0].size() == 0) {//рассматриваются ситации когда сообщение уже передается

			int local_from = path[i][0]; //точка в которой сейчас находится сообщение
			int local_to = path[i][1]; //точка в которую передается шаг на данном шаге
			int index_from = messages[i][0]; //отправитель
			int index_to = messages[i][2]; //получатель
			int message_cost = messages[i][1]; //длина сообщения


			if (local_from == path[i][1]) {// ситауция когда сообщение находится в одном узле из за штрафа (то есть никуда не передается)
				matrix_load[local_from][local_to] += reserv[i];
				matrix_load[local_to][local_from] += reserv[i];
				reserv[i] = 0;
				vector<int> new_path = Dijkstra_algorythm({ local_from, message_cost, index_to });
				new_path.insert(new_path.begin(), { path[i][0],path[i][1] });
				path[i] = new_path;
				reminder[i] = message_cost;
			}
			else { //ситуация когда передается сообщение из одного узда в другой
				//пропускная способность изменяется
				int can_send = reminder[i] < matrix_load[local_from][local_to] ? reminder[i] : matrix_load[local_from][local_to];

				int need_steps = reminder[i] / can_send;
				need_steps = reminder[i] % can_send == 0 ? need_steps : need_steps + 1;

				matrix_load[index_from][index_to] -= can_send;
				matrix_load[index_to][index_from] -= can_send;
				reserv[i] = can_send;

				if (path.size() > 2) {//сообщение может измениться если пропускная способность увеличилась

					int old_steps;//считаем сколько было шагов 
					for (int ii = 0; ii < path.size() - 2; ii += 2) {
						if (!(local_from == path[i][ii] && local_to == path[i][ii + 1])) {
							old_steps = ii / 2;
							break;
						}
					}
					if (old_steps != need_steps) {

						path[i].erase(path[i].begin(), path[i].begin() + old_steps * 2);
						for (int iii = 0; iii < need_steps; iii++) {
							path[i].insert(path[i].begin(), { local_from, local_to });
						}
					}
				}

				reminder[i] -= can_send;

			}

			//в конце шага нам нужн удалить данный шаг
			if (path[i].size() != 0) {
				path[i].erase(path[i].begin());
				//status[i].erase(status[i].begin());
			}
			else {
				messages.erase(messages.begin());
				path.erase(path.begin());
				//status.erase(status.begin());
			}
		}
		else {
			status[i].erase(status[i].begin());

		}
	}
}