// MealyAutomata.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include "IncAutomata.h"
#include "ElemTree.h"
#include "Grigorchuk.h"
#include "TrAutomata.h"
#include "spMatrix.h"

void writeVec(std::vector<int> vec) {
	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i];
	std::cout << std::endl;
}

std::string bin(int& n) {
	std::string s;
	int t = n;
	while (t > 0) {
		s = std::to_string(t%2) + s;
		t /= 2;
	}
	return s;
}

int main(int argc, char** argv)
{
	srand(unsigned(time(nullptr)));

	//Grigorchuk automata;
	//TrAutomata automata;
	//IncAutomata automata;

	Automata automata;
	
	std::ifstream in;

	//string s;
	//cin >> s;
	in.open("./Automatas/automata.txt");

	automata.read(in);
	in.close();

	auto start = chrono::high_resolution_clock::now();

	//Do what you need

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << "\nexecution time: " << duration.count() << " miliseconds" << endl;

	int done; cin >> done;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


//1 мaкс складність в інк
//средня складність