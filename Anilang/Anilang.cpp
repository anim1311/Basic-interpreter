
#include <iostream>
#include <list>
#include <iterator>
using namespace std;
#include"basicFunction.h"
#include"magic.h"


int main() {
	string query;
	
	while (true)
	{
		cout << "AniLang> ";
		cin >> query;
		if (query == "close")
			exit(0);
		else
			list<Tokens> result = run(query);
		
		
	}
}