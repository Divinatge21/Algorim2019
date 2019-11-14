#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>

using namespace std;


int** get_empty_contiguity_matrix(int vertex_count)
{

	int** matrix = new int* [vertex_count];


	for (int i = 0; i < vertex_count; i++)
		matrix[i] = new int[vertex_count];


	for (int i = 0; i < vertex_count; i++)
		for (int j = 0; j < vertex_count; j++)
			matrix[i][j] = 0;


	return matrix;
}


int** read_from_file_contiguity_matrix(char const* filename, int* vertex_count)
{

	ifstream file;


	file.open(filename);


	if (!file.is_open())
	{
		cout << "Failed to open file" << endl;
		return nullptr;
	}


	file >> *vertex_count;


	int** matrix = new int* [*vertex_count];


	for (int i = 0; i < *vertex_count; i++)
		matrix[i] = new int[*vertex_count];


	for (int i = 0; i < *vertex_count; i++)
		for (int j = 0; j < *vertex_count; j++)
			matrix[i][j] = 0;


	int a, b;
	while (file >> a >> b) {
		a--; b--;
		matrix[a][b] = 1;
		matrix[b][a] = 1;
	}


	for (int i = 0; i < *vertex_count; ++i)
	{
		for (int j = 0; j < *vertex_count; ++j)
			cout << matrix[i][j] << " ";
		cout << endl;
	}


	file.close();


	return matrix;
}


bool write_to_file_contiguity_matrix(char const* filename, int** contiguity_matrix, int vertex_count)
{

	ofstream file;


	file.open(filename);


	if (!file.is_open())
	{
		cout << "Failed to open file" << endl;
		return false;
	}


	file << vertex_count << endl;


	for (int i = 0; i < vertex_count; i++)
		for (int j = i; j < vertex_count; j++)
			if (contiguity_matrix[i][j] == 1)
			{
				file << i + 1 << ' ' << j + 1 << endl;
			}


	file.close();


	return true;
}


void demo_empty_contiguity_matrix()
{

	int** contiguity_matrix = nullptr;


	contiguity_matrix = get_empty_contiguity_matrix(10);


	for (int i = 0; i < 10; ++i)
		delete[] contiguity_matrix[i];
	delete[] contiguity_matrix;
}


void demo_file_contiguity_matrix()
{

	int** contiguity_matrix = nullptr;


	int* vertex_count = new int();


	contiguity_matrix = read_from_file_contiguity_matrix("contiguity_matrix.in", vertex_count);


	write_to_file_contiguity_matrix("contiguity_matrix.out", contiguity_matrix, *vertex_count);


	for (int i = 0; i < *vertex_count; ++i)
		delete[] contiguity_matrix[i];
	delete[] contiguity_matrix;
}


int** get_empty_incidence_matrix(int vertex_count, int edge_count)
{

	int** matrix = new int* [vertex_count];


	for (int i = 0; i < vertex_count; i++)
		matrix[i] = new int[edge_count];


	for (int i = 0; i < vertex_count; i++)
		for (int j = 0; j < edge_count; j++)
			matrix[i][j] = 0;


	return matrix;
}


void demo_incidence_matrix()
{

	int** incidence_matrix = nullptr;


	incidence_matrix = get_empty_incidence_matrix(10, 5);
}

vector<list<int>*>* get_empty_list_contiguity(int vertex_count)
{

	vector<list<int>*>* vec = new vector<list<int>*>;


	for (int i = 0; i < vertex_count; i++)
	{
		list<int>* lst = new list<int>();
		vec->push_back(lst);
	}


	for (int i = 0; i < vertex_count; i++)
	{
		(*vec)[i]->push_back(i);
	}


	return vec;
}


vector<list<int>*>* read_from_file_list_contiguity(char const* filename, int* vertex_count)
{

	ifstream file;


	file.open(filename);

	if (!file.is_open())
	{
		cout << "Failed to open file" << endl;
		return nullptr;
	}


	file >> *vertex_count;

	vector<list<int>*>* vec = new vector<list<int>*>;


	for (int i = 0; i < *vertex_count; i++)
	{
		list<int>* lst = new list<int>();
		vec->push_back(lst);
	}

	vector<int> values;
	int vertex = 0;
	for (string line; getline(file, line); )
	{
		while (line.length() == 0) getline(file, line);
		stringstream iss(line);
		int number;
		while (iss >> number) values.push_back(number - 1);

		if (values[0] == -1)
		{
			continue;
		}
		else
		{
			for (vector<int>::const_iterator i = values.begin(); i != values.end(); ++i)
				(*vec)[vertex]->push_back(*i);
		}
		vertex++;
		values.clear();
	}

	for (int i = 0; i < *vertex_count; i++)
	{
		cout << "vertex " << i + 1 << endl;
		for (list<int>::iterator j = (*vec)[i]->begin(); j != (*vec)[i]->end(); j++)
			cout << *j + 1 << " ";
		cout << endl;
	}


	file.close();


	return vec;
}


bool write_to_file_list_contiguity(char const* filename, vector<list<int>*> * list_contiguity, int vertex_count)
{

	ofstream file;


	file.open(filename);


	if (!file.is_open())
	{
		cout << "Failed to open file" << endl;
		return false;
	}


	file << vertex_count << endl;


	for (int i = 0; i < vertex_count; i++)
	{
		if ((*list_contiguity)[i]->size() > 0)
		{
			for (list<int>::iterator j = (*list_contiguity)[i]->begin(); j != (*list_contiguity)[i]->end(); j++) file << *j + 1 << " ";
			file << endl;
		}
		else
		{
			file << -1 << endl;
		}
	}


	file.close();

	return true;
}

int list_contiguity_get_edge_count(vector<list<int>*> * list_contiguity, int vertex_count)
{

	int edge_count = 0;


	for (int i = 0; i < vertex_count; i++)
	{
		int edge_count_cur_vertex = (*list_contiguity)[i]->size();
		edge_count += edge_count_cur_vertex;
	}


	edge_count = edge_count / 2;


	return edge_count;
}

void demo_list_contiguity()
{

	vector<list<int>*>* list_contiguity = nullptr;

	list_contiguity = get_empty_list_contiguity(10);


	for (int i = 0; i < 10; i++)
	{
		delete (*list_contiguity)[i];
	}
	delete list_contiguity;
}


void demo_file_list_contiguity()
{

	vector<list<int>*>* list_contiguity = nullptr;


	int* vertex_count = new int();


	list_contiguity = read_from_file_list_contiguity("list_contiguity.in", vertex_count);


	write_to_file_list_contiguity("list_contiguity.out", list_contiguity, *vertex_count);


	for (int i = 0; i < *vertex_count; i++)
	{
		delete (*list_contiguity)[i];
	}
	delete list_contiguity;
}


vector<list<int>*>* get_empty_list_edge(int edge_count)
{

	vector<list<int>*>* vec = new vector<list<int>*>;


	for (int i = 0; i < edge_count; ++i)
	{
		list<int>* lst = new list<int>();
		vec->push_back(lst);
	}


	for (int i = 0; i < 2; i++)
	{
		(*vec)[i]->push_back(0);
		(*vec)[i]->push_back(1);
	}


	return vec;
}


vector<list<int>*>* read_from_file_list_edge(char const* filename, int* edge_count)
{

	ifstream file;


	file.open(filename);


	if (!file.is_open())
	{
		cout << "Failed to open file" << endl;
		return nullptr;
	}


	file >> *edge_count;


	vector<list<int>*>* vec = new vector<list<int>*>;


	for (int i = 0; i < *edge_count; ++i)
	{
		list<int>* lst = new list<int>();
		vec->push_back(lst);
	}


	int a, b;
	int edge = 0;
	while (file >> a >> b) {
		a--; b--;
		(*vec)[edge]->push_back(a);
		(*vec)[edge]->push_back(b);
		edge++;
	}


	for (int i = 0; i < *edge_count; i++)
	{
		for (list<int>::iterator j = (*vec)[i]->begin(); j != (*vec)[i]->end(); j++)
			cout << *j + 1 << " ";
		cout << endl;
	}

	file.close();


	return vec;
}


bool write_to_file_list_edge(char const* filename, vector<list<int>*> * list_edge, int edge_count)
{

	ofstream file;


	file.open(filename);


	if (!file.is_open())
	{
		cout << "Failed to open file" << endl;
		return false;
	}


	file << edge_count << endl;


	for (int i = 0; i < edge_count; i++)
	{
		for (list<int>::iterator j = (*list_edge)[i]->begin(); j != (*list_edge)[i]->end(); j++) file << *j + 1 << " ";
		file << endl;
	}


	file.close();


	return true;
}


int list_edge_get_vertex_count(vector<list<int>*> * list_edge, int edge_count)
{

	int max_vertex = -1;


	for (int i = 0; i < edge_count; i++)
	{
		for (list<int>::iterator j = (*list_edge)[i]->begin(); j != (*list_edge)[i]->end(); j++)
			if ((*j + 1) > max_vertex)
			{
				max_vertex = *j + 1;
			}
	}


	return max_vertex;
}


void demo_list_edge()
{

	vector<list<int>*>* list_edge = nullptr;


	list_edge = get_empty_list_edge(10);
}


void demo_file_list_edge()
{

	vector<list<int>*>* list_edge = nullptr;


	int* edge_count = new int();


	list_edge = read_from_file_list_edge("list_edge.in", edge_count);


	write_to_file_list_contiguity("list_edge.out", list_edge, *edge_count);


	for (int i = 0; i < *edge_count; i++)
	{
		delete (*list_edge)[i];
	}
	delete list_edge;
}


vector<list<int>*>* list_contiguity_2_list_edge(vector<list<int>*> * list_contiguity, int vertex_count, int* edge_count)
{

	vector<list<int>*>* list_edge = nullptr;


	*edge_count = list_contiguity_get_edge_count(list_edge, vertex_count) * 2;


	list_edge = get_empty_list_edge(*edge_count);


	int edge_index = 0;
	for (int i = 0; i < vertex_count; i++)
	{
		if ((*list_contiguity)[i]->size() > 0)
		{
			for (list<int>::iterator j = (*list_contiguity)[i]->begin(); j != (*list_contiguity)[i]->end(); j++)
			{
				(*list_edge)[edge_index]->push_back(i);
				(*list_edge)[edge_index]->push_back(*j);
				edge_index++;
			}
		}
	}


	return list_edge;
}


vector<list<int>*>* list_edge_2_list_contiguity(vector<list<int>*> * list_edge, int edge_count, int* vertex_count)
{

	vector<list<int>*>* list_contiguity = nullptr;


	*vertex_count = list_edge_get_vertex_count(list_edge, edge_count);


	list_contiguity = get_empty_list_contiguity(*vertex_count);


	for (int i = 0; i < edge_count; i++)
	{
		int vertexes[2];
		int vertex_index = 0;
		for (list<int>::iterator j = (*list_edge)[i]->begin(); j != (*list_edge)[i]->end(); j++) {
			vertexes[vertex_index] = *j + 1;
			vertex_index++;
		}

		(*list_contiguity)[vertexes[0]]->push_back(vertexes[1]);
		(*list_contiguity)[vertexes[1]]->push_back(vertexes[0]);
	}


	return list_contiguity;
}

/// <summary>Вариант 1. Демонстрация работы</summary>
void first_variant()
{

	demo_file_list_contiguity();

	demo_file_list_edge();


}

/// Матрица инциденций
void incidence_matrix(char const* filename)
{
	ifstream file;
	file.open(filename);

	if (!file.is_open())
	{
		cout << "fail is not open" << endl;
		return;
	}
	int count;
	file >> count;
	int countlines;
	file >> countlines;
	cout << count << endl;
	cout << countlines << endl;
	int a, b;
	int** matrix = new int* [countlines];
	for (int i = 0; i < countlines; ++i)
		matrix[i] = new int[count];
	for (int i = 0; i < countlines; ++i)
		for (int j = 0; j < count; ++j)
			matrix[i][j] = 0;


	for (int i = 0; i < countlines; i++)
	{
		file >> a >> b;
		cout << a << " " << b << endl;
		a--; b--;
		matrix[i][a] = 1;
		matrix[i][b] = 1;
	}

	for (int i = 0; i < countlines; ++i)
	{
		for (int j = 0; j < count; ++j)
			cout << matrix[i][j] << " ";
		cout << endl;
	}

	for (int i = 0; i < countlines; ++i)
		delete[] matrix[i];
	delete[] matrix;

	file.close();


}

int main()
{
	first_variant();
	return 0;
}
