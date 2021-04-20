#pragma once
#include <memory>
#include "figures.h"

using namespace std;

template<typename T>
std::shared_ptr<Figure> CreateFigure(char type, T side){
	std::shared_ptr<Figure> fig;
	switch(type){
		default:
		case 'q':
			return make_shared<Square<T>>(side);
		case 't':
			return make_shared<Triangle<T>>(side);
		case 'r':
			{
				T height;
				cin >> height;
				return make_shared<Rectangle<T>>(side, height);
			}
	}
}