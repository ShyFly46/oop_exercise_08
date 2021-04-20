#pragma once
#include <iostream>
#include <fstream>

using namespace std;

struct Figure {
	virtual void Print(){
		Write(cout);
	}
	virtual void Write(ostream& file) = 0;
};

template<typename T>
class Square : public Figure {
	using coords = pair<T, T>;
	coords a, b, c, d;
	
public:
	Square(T s = 1){
		a.first  = 0;
		a.second = 0;
		
		b.first  = s;
		b.second = 0;
		
		c.first  = s;
		c.second = 0;
		
		d.first  = s;
		d.second = s;
	}

	void Write(ostream& file) override {
		file << "Sqr: "
		     << "{" << a.first << ", " << a.second << "}  "
		     << "{" << b.first << ", " << b.second << "}  "
		     << "{" << c.first << ", " << c.second << "}  "
		     << "{" << d.first << ", " << d.second << "}\n";
	}
};

template<typename T>
class Triangle : public Figure {
	using coords = pair<T, T>;
	coords a, b, c;

public:
	Triangle(T s = 1) {
		a.first = a.second  = 0;
		
		b.first  = 0;
		b.second = s;
		
		c.first  = s;
		c.second = 0;
	}

	void Write(ostream& file) override {
		file << "Tri: "
		     << "{" << a.first << ", " << a.second << "}  "
		     << "{" << b.first << ", " << b.second << "}  "
		     << "{" << c.first << ", " << c.second << "}\n";
	}
};

template<typename T>
class Rectangle : public Figure {
	using coords = pair<T, T>;
	coords a, b, c, d;

public:
	Rectangle(T s = 1, T h = 1){
		a.first = a.second = b.second = d.first = 0;
		b.first = c.first = s;
		c.second = d.second = h;
	}

	void Write(ostream& file) override {
		file << "Rct: "
		     << "{" << a.first << ", " << a.second << "}  "
		     << "{" << b.first << ", " << b.second << "}  "
		     << "{" << c.first << ", " << c.second << "}  "
		     << "{" << d.first << ", " << d.second << "}\n";
	}
};