#pragma once

#include <vector>
#include <map>

using namespace std;

typedef vector<double> vec;

double dot(const vec& v1, const vec& v2);

double norm(const vec& v);

void ort(vec& v, const vec& ort);

double normalize(vec& v);

void randomize(vec& v);

class spMatrix
{
private:
	size_t n;
	vector<map<size_t, double>> hors;
	//vector<map<size_t, double>> verts;

public:
	spMatrix(): n(0), hors(0) {}
	spMatrix(size_t n) : n(n), hors(n) {}

	vec getEig(int m, int t, double eps = 1e-7);

	vec mult(const vec& v);
	//void syncHV();
	size_t size();
	void show();

	void dfs(int start, vector<int>& rez);

	int diametr();
	int diametr_fast(int it);

	vec operator *(const vec& v);
	spMatrix operator *(spMatrix& m);
	map<size_t, double>& operator[](size_t i);
};

