/**
 * Савченко И.В.
 * М8О-208Б-19
 * https://github.com/ShyFly46/oop_exercise_08
 *
 * Вариант 1:
 * "Асинхронное программирование"
 * Треугольник, квадрат, прямоугольник
 **/

#include <pthread.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>	// stringstream

#include "factory.h"
#include "handler.h"

using namespace std;

using FigPtr = shared_ptr<Figure>;

void help() {
    cout
		//<< "t q r\n"
		<< "h - this help text\n"
		<< "x - exit\n"
		<< "t - add triangle\n"
		<< "q - add square\n"
		<< "r - add reactangle (2 sides)\n";
}


int main(int argc, char** argv) {
    size_t bufferSize = 3;

    if (argc == 2) {
        stringstream argc;
        argc << argv[1];
        argc >> bufferSize;
    }

    Handler handler(bufferSize);

    handler.AddFuction([](const vector<FigPtr>& figs) {
        for (auto& fig : figs) {
            fig->Print();
        }
    });

    handler.AddFuction([](const vector<FigPtr>& figs) {
        int fileNumber = rand() % 30;
        string fileName = "figs_" + to_string(fileNumber) + ".txt";
        ofstream file(fileName);
        for (auto items : figs) {
            items->Write(file);
        }
        file.close();
    });

    help();
	char cmd;
	cout << "> ";
    while(cin >> cmd){
        switch(cmd){
        case 't':
		case 'q':
		case 'r':
			{
				double side;
				cin >> side;
				handler.Push(CreateFigure(cmd, side));
			}
			cout << "Added ";
			if     (cmd == 't') cout << "triangle\n";
			else if(cmd == 'q') cout << "square\n";
			else         /*'r'*/cout << "rectangle\n";
            break;
		case 'h':
			help();
			break;
        case 'x':
            cout << "Stop\n";
            return 0;
        default:
            cout << "???\n";
            break;
        }
        cout << "> ";
    }
}
