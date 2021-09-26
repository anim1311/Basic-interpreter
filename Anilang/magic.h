#pragma once
#include<iostream>
#include <list>
#include <iterator>
#include"basicFunction.h"
using namespace std;

//Constants
string digits = "0123456789";

//ERRORS YAY!!!!!!!!!!!

class Errors {
public:
	string error_name, details;
	explicit Errors(string error_name, string details) {
		this->error_name = error_name;
		this->details = details;
	}
	string errorAsString() {
		return this->error_name + " : " + this->details;
	}
};


//Tokens Class

string TT_INT = "TT_INT";
string TT_FLOAT = "TT_FLOAT";
string TT_PLUS = "TT_PLUS";
string TT_MINUS = "TT_MINUS";
string TT_MUL = "TT_MUL";
string TT_DIV = "TT_DIV";
string TT_LPAREN = "TT_LPAREN";
string TT_RPAREN = "TT_RPAREN";



class Tokens {

public:
	string type_, value;
	Tokens(string type_, string value="") {
		this->type_ = type_;
		this->value = value;
		
	}
	string rper() {
		if (this->value != "") {
			return this->type_ + " : " + this->value + "\n";
		}
		else
			return this->type_ + "\n";
	}

};

// LEXER CLASS

class Lexer {
public:
	string query;
	int pos;
	char currentChar;
	Lexer(string query) {
		this->query = query;
		this->pos = -1;
		this->currentChar = NULL;
		this->advance();
	}
	void advance() {
		
		this->pos++;
		if (this->pos < this->query.length())
			this->currentChar = this->query[this->pos];
		else
			this->currentChar = NULL;
	} 

	list<Tokens> makeTokens() {
		list<Tokens> tokens;
		while (this->currentChar!=NULL)
		{
			if (this->currentChar == ' ' || this->currentChar == '\t') {
				this->advance();
			}else if (checkIfNumber(this->currentChar)) {
				tokens.push_back(makeNumber());
			}else if (this->currentChar == '+') {
				tokens.push_back(Tokens(TT_PLUS, ""));
				this->advance();
			}else if (this->currentChar == '-') {
				tokens.push_back(Tokens(TT_MINUS, ""));
				this->advance();
			}else if (this->currentChar == '*') {
				tokens.push_back(Tokens(TT_MUL, ""));
				this->advance();
			}else if (this->currentChar == '/') {
				tokens.push_back(Tokens(TT_DIV, ""));
				this->advance();
			}else if (this->currentChar == '(') {
				tokens.push_back(Tokens(TT_LPAREN, ""));
				this->advance();
			}else if (this->currentChar == ')') {
				tokens.push_back(Tokens(TT_RPAREN, ""));
				this->advance();
			}
			else {
				string e = (string)"'" + this->currentChar + (string)"'";
				this->advance();
				Errors error("IllegalCharError",e);
				cout << error.errorAsString() << endl;
				exit(-1);

			}
		}
		return tokens;
	}
	Tokens makeNumber() {
		string num = "";
		int dotCount = 0;
		while (this->currentChar != NULL && (checkIfNumber(this->currentChar) || this->currentChar == '.')) {
			if (this->currentChar == '.') {
				if (dotCount == 1) break;
				dotCount++; 
				num += ".";

			}
			else {
				num += this->currentChar;
			}
			this->advance();
		}

		if (dotCount == 0) {
			return(Tokens(TT_INT, num));
		}
		return(Tokens(TT_FLOAT, num));

	}

};

// RUN

list<Tokens> run(string query) {

	Lexer lexer(query);
	list<Tokens> tokens = lexer.makeTokens();
	
	return tokens;
}
