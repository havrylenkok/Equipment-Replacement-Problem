#pragma once
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iomanip>
#include <regex>
#include <locale>

using namespace std;

class Controller 
{
	//�������� �������� � <int>, ���� - � <double>. vector<bool> �� ����� subscript ���������� ��
	//������������ ��������, �������� ������������� (���� ��� ��� ���-�� � ������������ �� �����)

private:
	//����������
	int t; // t - ������� ���
	int p; // p - ���� ������� ������ ������������
	int T; // T - ������������ �������
	int stableT; // const T
	int k = 1; // k - �������� �� �������
	int maxZ = 0; //������������ �������. ���������� �����, ����� �� �������� � ��������� � ���������
	int showingT; //����� T ��� ������� ������

	map<int, int> r; // r(t) - ������� �� ���������� ���
	map<int, int> u; // u(t) - ������� �� ������������ �� ���������� ���

	//������� ������� ��� �������� � �����, ����� ������� � 1, � �� 0
	vector<int> nullVectorOfInt{ 0 }; 
	vector<double> nullVectorOfBool{ 0 };

	map<int, vector<int> > tableInterResultValues; // ������������� ��������, �������� fk(t)
	map<int, vector<double> > tableInterStrategy; // ������������� ��������, ���������
	
	int resultTable(vector<int> final); //��������� �������
	vector<int> fullCycle(); //������ �� ���� k
	tuple<vector<int>, vector<double>> fkt(); //������ �� ���� t
	tuple<int, bool> functionFrom1(int t); //������� ��� �������
	tuple<int, bool> functionFromK(int t); //������� ��� k-����
	int functionFromLast(int t); //������� ��� ����������
	void saveConditions(); //���������� ������� � ����� ������

public:
	void startProcess(); //������ ��������
	Controller(map<int, int> r, map<int, int> u, int p, int T);

};

