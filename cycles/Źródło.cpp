#include<iostream>
#include<cstdlib>
#include<array>
#include<chrono>
#include<fstream>
#include<algorithm>
using namespace std;

int druk = 1;


void must1(int*** a, int size) {
	*a = new int* [size + 1];
	for (int p = 0; p < size; p++) {
		(*a)[p] = new int[size + 1];
	}
	for (int c = 0; c < size; c++) {
		for (int d = 0; d < size; d++) {
			(*a)[c][d] = 0;
		}
	}
}
void must2(int*** a, int size) {
	*a = new int* [size + 1];
	for (int p = 0; p < size; p++) {
		(*a)[p] = new int[size + 1];
	}
	for (int c = 0; c < size; c++) {
		for (int d = 0; d < size; d++) {
			(*a)[c][d] = -1;
		}
	}
}
void must3(int** stack, int size) {
	*stack = new int[size + 1];
	for (int b = 0; b < size + 1; b++) {
		(*stack)[b] = -1;
	}
}

void help(int*** a, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((*a)[i][j] != -1) {
				(*a)[i][j]--;
			}
		}
	}
}
void help2(int*** a, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((*a)[i][j] != -1) {
				(*a)[i][j]++;
			}
		}
	}
}
int count1(int*** a, int size) {
	int counter = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((*a)[i][j] == 1) {
				counter++;
			}
		}
	}
	return (counter/2);
}
int count2(int*** a, int size){
	int counter = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((*a)[i][j] != -1) {
				counter++;
			}
		}
	}
	return counter;
}

void Hcycle1(int size, int** O, int** path, int*** a, int** vis) {
	bool end = true;
	for (int start = 0; start < size; start++) {
		bool end = true;
		int current = start;
		int counter = 0;
		for (int i = 0; i < size; i++) {
			(*vis)[i] = -1;
			(*O)[i] = -1;
			(*path)[i] = -1;
		}
		while (end) {
			(*path)[counter] = current;
			(*vis)[current] = 1;
			int helper = -1;
			for (int i = size - 1; i >= 0; i--) {
				if ((*a)[current][i] == 1 && i > (*O)[current] && (*vis)[i] != 1) {
					helper = i;
				}
			}
			if (helper != -1) {
				(*O)[current] = helper;
				current = helper;
				counter++;
			}
			int helper2 = 0;
			for (int i = 1; i < size; i++) {
				if ((*path)[i] == -1) {
					helper2 = 1;
				}
			}
			if (helper2 == 0) {
				if ((*a)[current][start] == 1) {
					cout << "loop:";
					for (int i = 0; i < size; i++) {
						cout << (*path)[i] + 1 << " ";
					}
					cout << start+1 << "\n";
					return;
				}
			}
			if (helper == -1) {
				if (counter == 0) {
					end = false;
				}
				else {
					(*vis)[current] = -1;
					current = (*path)[counter-1];
					int p = 0;
					for (int i = 0; i < size; i++) {
						p = (*vis)[i];
						if (p != 1) {
							(*O)[i] = -1;
						}
					}
					(*path)[counter] = -1;
					counter--;
				}
			}
		}
	}
	cout << "no loop\n";
	return;
}
void Hcycle2(int size, int** O, int** path, int*** a, int** vis) {
	bool end = true;
	help(a, size);
	for (int start = 0; start < size; start++) {
		end = true;
		int current = start;
		int counter = 0;
		for (int i = 0; i < size; i++) {
			(*vis)[i] = -1;
			(*O)[i] = -1;
			(*path)[i] = -1;
		}
		while (end) {
			(*path)[counter] = current;
			(*vis)[current] = 1;
			int helper = -1;
			for (int i = size - 1; i >= 0; i--) {
				if ((*a)[current][i] != -1 && i > (*O)[current] && (*vis)[(*a)[current][i]] != 1) {
					helper = ((*a)[current][i]);
				}
			}
			if (helper != -1) {
				(*O)[current] = helper;
				current = helper;
				counter++;
			}
			int helper2 = 0;
			for (int i = 1; i < size; i++) {
				if ((*path)[i] == -1) {
					helper2 = 1;
				}
			}
			int helper3 = 0;
			int w = 0;
			while ((*a)[current][w] != -1 && w < size) {
				if ((*a)[current][w] == start) {
					helper3 = 1;
			}
				w++;	
			}
			if (helper2 == 0) {
				if (helper3 == 1) { 
					cout << "loop:";
					for (int i = 0; i < size; i++) {
						cout << (*path)[i] + 1 << " ";
					}
					cout << start + 1 << "\n";
					help2(a, size);
					return;
				}
			}
			if (helper == -1) {
				if (counter == 0) {
					end = false;
				}
				else {
					(*vis)[current] = -1;
					current = (*path)[counter - 1];
					int p = 0;
					for (int i = 0; i < size; i++) {
						p = (*vis)[i];
						if (p != 1) {
							(*O)[i] = -1;
						}
					}
					(*path)[counter] = -1;
					counter--;
				}
			}
		}
	}
	cout << "no loop\n";
	help2(a, size);
	return;
}
void Acycle1(int size, int** O, int** path, int*** a, int*** vis) {
	bool end = true;
	int vert = count1(a, size);
	for (int start = 0; start < size; start++) {
		bool end = true;
		int current = start;
		int counter = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				(*vis)[i][j] = -1;
				(*O)[i] = -1;
			}
		}
		for (int i = 0; i < 2 * size; i++) {
			(*path)[i] = -1;
		}
		while (end) {
			(*path)[counter] = current;
			int helper = -1;
			for (int i = size - 1; i >= 0; i--) {
				if ((*a)[current][i] == 1 && i > (*O)[current] && (*vis)[current][i] != 1) {
					helper = i;
				}
			}
			if (helper != -1) {
				(*O)[current] = helper;
				(*vis)[current][helper] = 1;
				(*vis)[helper][current] = 1;
				current = helper;
				counter++;
			}
			int helper2 = 0;
			for (int i = 1; i < vert+1; i++) { //tu trzeba, bo path mo¿e mieæ -1
				if ((*path)[i] == -1) {
					helper2 = 1;
				}
			}
			if (helper2 == 0) {
				if (current == start) {
					cout << "loop:";
					for (int i = 0; i < vert+1; i++) {
						cout << (*path)[i] + 1 << " ";
					}
					return;
				}
			}
			if (helper == -1) {
				if (counter == 0) {
					end = false;
				}
				else {
					(*vis)[current][(*path)[counter]] = -1;
					(*vis)[(*path)[counter ]][current] = -1;
					current = (*path)[counter - 1];
					int p = 0;
					for (int i = counter; i < vert; i++) {
						p = (*path)[i];
						if (p != -1) {
							(*O)[i] = -1;
						}
					}
					(*path)[counter] = -1;
					counter--;
				}
			}
			if (counter > vert) {
				end = false;
			}
		}
	}
	cout << "no loop\n";
	return;
}
void Acycle2(int size, int** O, int** path, int*** a, int*** vis) {
	bool end = true;
	int vert = count2(a, size);
	help(a, size);
	for (int start = 0; start < size; start++) {
		bool end = true;
		int current = start;
		int counter = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				(*vis)[i][j] = -1;
				(*O)[i] = -1;
			}
		}
		for (int i = 0; i < 2 * size; i++) {
			(*path)[i] = -1;
		}
		while (end) {
			(*path)[counter] = current;
			int helper = -1;
			for (int i = size - 1; i >= 0; i--) {
				if ((*a)[current][i] != -1 && i > (*O)[current] && (*vis)[current][(*a)[current][i]] != 1) {
					helper = (*a)[current][i];
				}
			}
			if (helper != -1) {
				(*O)[current] = helper;
				(*vis)[current][helper] = 1;
				current = helper;
				counter++;
			}
			int helper2 = 0;
			for (int i = 1; i < vert + 1; i++) { 
				if ((*path)[i] == -1) {
					helper2 = 1;
				}
			}
			if (helper2 == 0) {
				if (current == start) {
					cout << "loop:";
					for (int i = 0; i < vert + 1; i++) {
						cout << (*path)[i] + 1 << " ";
					}
					help2(a, size);
					return;
				}
			}
			if (helper == -1) {
				if (counter == 0) {
					end = false;
				}
				else {
					(*vis)[current][(*path)[counter]] = -1;
					current = (*path)[counter - 1];
					int p = 0;
					for (int i = counter; i < vert; i++) {
						p = (*path)[i];
						if (p != -1) {
							(*O)[i] = -1;
						}
					}
					(*path)[counter] = -1;
					counter--;
				}
			}
			if (counter > vert) {
				end = false;
			}
		}
	}
	cout << "no loop\n";
	help2(a, size);
	return;
}






int load1(int*** a) {
	fstream newfile;
	newfile.open("input.txt", ios::in);
	int size = 0;
	if (newfile.is_open()) {
		int line;
		int line2;
		int line3;
		newfile >> line;
		size = line;
		must1(a, line);
		newfile >> line;
		for (int q = 0; q < line; q++) {
			newfile >> line2;
			newfile >> line3;
			if (line2 <= line + 1 && line3 <= line + 1 && line2 > 0 && line3 > 0) {
				(*a)[line2 - 1][line3 - 1] = 1;
				(*a)[line3 - 1][line2 - 1] = 1;
			}
			else { cout << "Error loading " << line2 << " to " << line3 << "\n"; return 0; }
		}
		newfile.close();
	}
	else {
		cout << "Plik nie znaleziony\n";
		return size;
	}
	if (druk == 1) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << (*a)[i][j] << " ";
			}
			cout << "\n";
		}
	}
	return size;
}
int load2(int*** a) {
	fstream newfile;
	newfile.open("input.txt", ios::in);
	int size = 0;
	if (newfile.is_open()) {
		int line;
		int line2;
		int line3;
		newfile >> line;
		size = line;
		must1(a, line);
		newfile >> line;
		for (int q = 0; q < size; q++) {
			for (int w = 0; w < size; w++) {
				(*a)[q][w] = size+1;
			}
		}
		for (int q = 0; q < line; q++) {
			newfile >> line2;
			newfile >> line3;
			if (line2 <= line + 1 && line3 <= line + 1 && line2 > 0 && line3 > 0) {
				(*a)[line2 - 1][line3 - 1] = line3;
			}
			else { cout << "Error loading " << line2 << " to " << line3 << "\n"; return 0; }
		}
		newfile.close();
	}
	else {
		cout << "Plik nie znaleziony\n";
		return size;
	}
	for (int i = 0; i < size; i++) {
		sort((*a)[i], (*a)[i] + size);
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((*a)[i][j] == size + 1) {
				(*a)[i][j] = -1;
			}
		}
	}
	if (druk == 1) {
		for (int q = 0; q < size; q++) {
			int w = 0;
			while ((*a)[q][w] != -1 && w < size) {
				cout << q + 1 << ", " << (*a)[q][w] << "\n";
				w++;
			}
		}
	}
	return size;
}


void generate1(int*** a, int size, int x) {
	must1(a, size);
	for (int q = 0; q < size; q++) {
		for (int w = 0; w < size; w++) {
			(*a)[q][w] = 0;
		}
	}
	for (int q = 1; q < size; q++) {
		for (int w = 0; w < q; w++) {
			if ((rand() % 100) < x) {
				(*a)[w][q] = 1;
				(*a)[q][w] = 1;
			}
			else {
				(*a)[w][q] = 0;
				(*a)[q][w] = 0;
			}
		}
	}
	//print
	if (druk == 1) {
		for (int q = 0; q < size; q++) {
			for (int w = 0; w < size; w++) {
				cout << (*a)[q][w] << " ";
			}
			cout << "\n";
		}
	}
}
void generate2(int*** a, int size, int x) {
	must2(a, size);
	int counter = 0;
	srand((unsigned)time(NULL));
	for (int q = 0; q < size; q++) {
		for (int w = 0; w < size; w++) {
			if ((rand() % 100) < x ) {
				(*a)[q][counter] = w+1;
				counter++;
			}
		}
		counter = 0;
	}
	if (druk == 1) {
		for (int q = 0; q < size; q++) {
			int w = 0;
			while((*a)[q][w] != -1 && w < size) {
				cout << q+1 << ", " << (*a)[q][w] << "\n";
				w++;
			}
		}
	}
}

void loop11(int*** a, int size) {
	int* O;
	int* path;
	int* vis;
	must3(&O, size);
	must3(&vis, size);
	must3(&path, size);
	Hcycle1(size, &O, &path, a, &vis);
	delete[] O;
	delete[] path;
	delete[] vis;
}
void loop12(int*** a, int size) {
	int* O;
	int* path;
	int* vis;
	must3(&O, size);
	must3(&vis, size);
	must3(&path, size);
	Hcycle2(size, &O, &path, a, &vis);
	delete[] O;
	delete[] path;
	delete[] vis;
}
void loop21(int*** a, int size) {
	int* O;
	int* path;
	int** vis;
	must3(&O, size);
	must2(&vis, size);
	must3(&path, 2*size);
	Acycle1(size, &O, &path, a, &vis);
	delete[] O;
	delete[] path;
	delete[] vis;
}
void loop22(int*** a, int size) {
	int* O;
	int* path;
	int** vis;
	must3(&O, size);
	must2(&vis, size);
	must3(&path, 2 * size);
	Acycle2(size, &O, &path, a, &vis);
	delete[] O;
	delete[] path;
	delete[] vis;
}

int main() {
	srand((unsigned)time(NULL));
	int** a; //arr sasiedztwa
	int arrsize = 5; //iloœæ wierzcho³ków
	int nas = 60; //nasycenie
	arrsize = load2(&a);
	loop22(&a, arrsize);
}