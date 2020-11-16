#include <iostream>
#include <ctime>
#include <algorithm>


//������������ �������� ���� = 1000000
#define INF 1000000

using namespace std;
const double InfinitiesPercent = 50.0;
const double RandomDataMultiplier = 10;

//��������� ������� ��������� ��� ����� � �������� ������ ������
void RandomDataInitialization(int** Matrix, int Size) {
	srand((unsigned)time(0));
	int tmp = 0;
	for (int i = 0; i < Size; i++)
		for (int j = 0; j < Size; j++)
			if (i != j) {
				tmp = rand();
				if ((tmp % 100) < InfinitiesPercent) {
					Matrix[i][j] = INF;
				}
				else if (rand() % 100 < 5)
				{
					Matrix[i][j] = (-1)*tmp % 1001 + 1;
				}
				else
				{
					Matrix[i][j] = tmp % 1001 + 1;
				}
			}
			else
				Matrix[i][j] = 0;
}

//����� ������� �� �����
void printMatrix(int** matrix, int dim) {
	for (int i = 0; i < dim; ++i) {
		for (int j = 0; j < dim; ++j) {
			if (matrix[i][j] == INF) {
				cout << "INF" << " ";
			}
			else {
				cout <<  matrix[i][j] << " ";
			}

			
		}
		cout << endl;
	}
	cout << endl;
}


bool checkNegativeCircle(int **matrix, int numberOfVert) {

	for (int i = 0; i < numberOfVert; ++i)
	{
		if (matrix[i][i] < 0) return true;
	}
	return false;

}
//matrix - ������� ���������
//���������� ��������� �����-��������
int originalFloydWarshall(int **matrix, int numberOfVert) {
	clock_t tic = clock();
	bool with_negative_circle = false;
	//����������� �� ���� �������� � ���� ����� �������� ����
	//����� ������� k
	
		for (int k = 0; k < numberOfVert; k++) {
			for (int i = 0; i < numberOfVert; i++) {
				for (int j = 0; j < numberOfVert; j++) {
					//����� �������� ����� ����� ������������ ����� ������
					//� ������ ����� i <-> k + k <-> j (���� ����� k ������ �������)
					if (matrix[i][k] < INF && matrix[k][j] < INF) {
						matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
					}
				}
			}
		}
		
	tic = clock() - tic;
	with_negative_circle = checkNegativeCircle(matrix, numberOfVert);
	cout << "���� � �������������(�) ������(���)" << endl;
	return (tic);
}


//�������� �������
void del(int** Matrix, int Size) {
	for (int i = 0; i < Size; ++i)
		delete Matrix[i];
	delete[] Matrix;
}

int main() {
	int numberOfVert = 1000;

	//������� ��������� � ������ ����� �����(INF - ����� ���, 0 ����� � ����)
	int **matrix = new int*[numberOfVert];
	for (int i = 0; i < numberOfVert; ++i)
		matrix[i] = new int[numberOfVert];


	for (int vert = 50; vert <= 1000; vert += 50){
		int sum = 0;
	double time_alg = 0;
	for (int i = 0; i < 20; ++i) {
		RandomDataInitialization(matrix, vert);
		time_alg = originalFloydWarshall(matrix, vert);
		sum += time_alg;
	}
	time_alg = sum / 20.0;
	cout << "Vert: "<< vert << " | Time:  " << time_alg / 1000.0 << "  sec" << endl;
}
	
	del(matrix, numberOfVert);
	system("pause");
	return 0;
}

