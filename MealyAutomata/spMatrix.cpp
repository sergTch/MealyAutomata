#include "spMatrix.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <queue> 

vec spMatrix::getEig(int m, int t, double eps)
{
	int sgn;
	double diff;
	vec rez(1);
	vec buf;
	vector<vec> v(m, vec(n));
	v[0] = vec(n, 1);
	normalize(v[0]);
	
	size_t sz = size();
	randomize(v[1]);

	int log_fr = 1e8 / sz;
	cout << "find eig: " << m << "\nelements in matrix: " << sz << "\nmatrix size: " << n << "\nlog freq: " << log_fr << endl;

	double last = 0, cur = 0;

	for (int i = 1; i < m; i++) {
		last = 0;
		for (int j = 1; j < t; j++) {
			if (j % log_fr == 0)
				cout << j << " " << last << endl;
			cur = normalize(v[i]);

			if (abs(last - cur) < eps)
				break;
			last = cur;

			v[i] = mult(v[i]);

			for (int k = max(0, i - 2); k < i; k++)
				ort(v[i], v[k]);

			if (j == 0 || norm(v[i]) < 1e-10) {
				randomize(v[i]);

				for (int k = 0; k < i; k++) {
					normalize(v[i]);
					ort(v[i], v[k]);
				}
			}

			//if (j % (t / 20) == 0)
			//	cout << norm(v[i]) << endl;
		}

		buf = mult(v[i]);
		for (int k = max(0, i - 2); k < i; k++)
			ort(buf, v[k]);
		normalize(buf);

		diff = 0;
		sgn = 2 * int((v[i][0] > 0) ^ (buf[0] > 0)) - 1;

		for (int j = 0; j < n; j++) {
			if (abs(v[i][j] + sgn * buf[j]) > diff)
				cout << j << " " << buf[j] << " " << v[i][j] << endl;
			diff = max(abs(v[i][j] + sgn * buf[j]), diff);
			//diff += (v[i][j] + sgn * buf[j]) * (v[i][j] - sgn * buf[j]);
		}
		cout << "diff: " << diff << endl << endl;

		rez.push_back(cur);
		if (i + 1 < m)
			randomize(v[i + 1]);

		//cout << "rez\t\t" << rez.back() << endl;
	}

	return rez;
}

vec spMatrix::mult(const vec& v)
{
	if (n != v.size())
		throw exception("wrong size");
	vec rez(n);

	for (size_t i = 0; i < n; i++) {
		for (auto j = hors[i].begin(); j != hors[i].end(); j++) {
			rez[i] += j->second * v[j->first];
		}
	}

	return rez;
}
//
//void spMatrix::syncHV() {
//	verts = vector<map<size_t, double>>(n);
//
//	for (size_t i = 0; i < n; i++)
//		for (auto j = hors[i].begin(); j != hors[i].end(); j++)
//			verts[j->first][i] = j->second;
//}

size_t spMatrix::size() {
	size_t sum = 0;

	for (size_t i = 0; i < n; i++) {
		sum += hors[i].size();
	}

	return sum;
}

void spMatrix::show() {
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			if (hors[i].find(j) != hors[i].end())
				cout << hors[i][j] << " ";
			else cout << double(0) << " ";
		}
		cout << '\n';
	}
}

void spMatrix::dfs(int start, vector<int>& rez)
{
	int k;
	rez = vector<int>(n, -1);
	rez[start] = 0;
	queue<int> que;
	que.push(start);

	while (!que.empty()) {
		k = que.front();
		que.pop();

		for (auto i : hors[k]) {
			if (rez[i.first] == -1) {
				que.push(i.first);
				rez[i.first] = rez[k] + 1;
			}
		}
	}
}

int spMatrix::diametr() {
	int d = 0;
	vector<int> dist;

	for (int i = 0; i < n; i++) {
		dfs(i, dist);

		for (int j = 0; j < n; j++) {
			d = max(d, dist[j]);
		}
	}

	return d;
}

int spMatrix::diametr_fast(int it) {
	int d = 0, start, mx;
	vector<int> dist;

	start = rand() % n;

	for (int i = 0; i < it; i++) {	
		dfs(start, dist);

		mx = -1;
		for (int j = 0; j < n; j++) {
			if (dist[j] > mx) {
				start = j;
				mx = dist[j];
			}
		}
		d = max(d, mx);
	}

	return d;
}

vec spMatrix::operator *(const vec& v) {
	if (n != v.size())
		throw exception("wrong size");
	vec rez(n);

	for (size_t i = 0; i < n; i++)
		for (auto j = hors[i].begin(); j != hors[i].end(); j++)
			rez[i] += j->second * v[j->first];

	return rez;
}

spMatrix spMatrix::operator *(spMatrix& m) {
	if (n != m.n)
		throw exception("wrong size");
	spMatrix rez(n);

	for (size_t i = 0; i < n; i++) {
		for (auto j = hors[i].begin(); j != hors[i].end(); j++) {
			for (auto k = m[j->first].begin(); k != m[j->first].end(); k++) {
				rez[i][k->first] += j->second * k->second;
			}
		}
	}

	return rez;
}

map<size_t, double>& spMatrix::operator[](size_t i)
{
	return hors[i];
}

double dot(const vec& v1, const vec& v2)
{
	double t = 0;
	for (size_t i = 0; i < v1.size(); i++)
		t += v1[i] * v2[i];
	return t;
}

double norm(const vec& v)
{
	return sqrt(dot(v, v));
}

void ort(vec& v, const vec& ort)
{
	double t = dot(v, ort) / dot(ort, ort);
	
	for (size_t i = 0; i < v.size(); i++) {
		v[i] -= t * ort[i];
	}
}

double normalize(vec& v)
{
	double t = norm(v);
	for (size_t i = 0; i < v.size(); i++)
		v[i] /= t;
	return t;
}

void randomize(vec& v)
{
	generate(v.begin(), v.end(), rand);
}
