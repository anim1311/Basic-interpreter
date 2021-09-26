#pragma once
#include<iostream>
#include <string>
#include<cstring>
#include <list>
#include <iterator>
using namespace std;

bool checkIfNumber(char c) {
	try {
		int a = stoi(&c);
		return true;
	}
	catch(...){
		return false;
	}
	return false;
}

