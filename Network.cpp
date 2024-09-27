#include "Network.h"

Network::Network() {
	count_commutators = GROUPS * COMMUTATORS; 
	count_nodes = count_commutators * NODES; 
	count_vertex = count_commutators + count_nodes;

	vector<vector<int>> buf_adj(count_vertex, vector<int>(count_vertex, 0));
	/*for (int i = 0; i < count_vertex; i++) {
		matrix_adj.push_back(vector<int>(count_vertex, 0));
	}*/
	matrix_adj = buf_adj;

	for (int i = 0, ii=count_nodes; i < count_nodes;i++) {
			matrix_adj[i][ii] = 1;
			matrix_adj[ii][i] = 1;
			if (i & 1) {
				ii++;
			}	
	}

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


void Network::Print_matrix_adj() {
	print_matrix("Matrix_adj", matrix_adj);
}
