/* ------------------------------------------------------
CMP2801M: Advanced Programming
Driver program for assignment
Fall 2019

Written by Ayse Kucukyilmaz

This file is a representative test file.
During marking, we will use the exact same notation
as provided in the brief, so make sure
you follow that guideline. Also make sure that you don't
change the main body provided to you here.
Otherwise, your code may not pass the test cases...

GOOD LUCK!

------------------------------------------------------ */

#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Movable.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	string userCommand;
	vector <Shape*> shapes;     // this one will hold your shapes
	vector <string> parameters; // this one will hold parameters for the commands

	while (userCommand.compare("exit") != 0)
	{
		std::cout << "Enter the command: ";
		getline(cin, userCommand);

		// Creates a cstring and copies the input into it.
		char * cstr = new char[userCommand.length() + 1];
		strcpy_s(cstr, userCommand.length() + 1, userCommand.c_str());

		// Empty pointer for strtok_s
		char* next_token = NULL;
		// Tokenises the first input
		char* token = strtok_s(cstr, " ", &next_token);

		// Until there are no more parameters...
		while (token != NULL) {
			// Write into the parameters
			if (token != NULL) {
				parameters.push_back(token);
				// Tokenise next parameter
				token = strtok_s(NULL, " ", &next_token);
			}
		}

		string command = parameters[0];

		// Rectangles
		if (command.compare("addR") == 0) {
			// Force the parameters to be correct per statement
			if (parameters.size() != 5) {
				std::cout << "This command takes four (4) inputs." << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				// Loop 
				continue;
			}

			int x, y;
			double h, w;

			// stoi is string to int
			// stod is string to double
			// surrounded in a try in case someone has not input a number
			try {
				x = stoi(parameters[1].c_str());
				y = stoi(parameters[2].c_str());
				h = stod(parameters[3].c_str());
				w = stod(parameters[4].c_str());
			}
			catch (const exception& e) {
				std::cout << "You did not enter a correct number" << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			// Make sure there are no negative numbers
			if (x < 1 || y < 1 || h < 1 || w < 1) {
				std::cout << "You need to input all positive numbers" << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			// Create the rectangle
			Rectangle* r = new Rectangle(x, y, h, w);
			// Put it into the list of shapes
			shapes.push_back(r);
			// Print the string output
			std::cout << r->toString();
		}
		// Squares
		else if (command.compare("addS") == 0) {
			if (parameters.size() != 4) {
				std::cout << "This command takes three (3) inputs." << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			int x, y;
			double e;

			try {
				x = stoi(parameters[1].c_str());
				y = stoi(parameters[2].c_str());
				e = stod(parameters[3].c_str());
			}
			catch (const exception& e) {
				std::cout << "You did not enter a correct number" << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			if (x < 1 || y < 1 || e < 1) {
				std::cout << "You need to input all positive numbers" << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			Square* s = new Square(x, y, e);
			shapes.push_back(s);
			std::cout << s->toString();
		}
		// Circles
		else if (command.compare("addC") == 0) {
			if (parameters.size() != 4) {
				std::cout << "This command takes three (3) inputs." << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			int x, y;
			double r;

			try {
				x = stoi(parameters[1].c_str());
				y = stoi(parameters[2].c_str());
				r = stod(parameters[3].c_str());
			}
			catch (const exception& e) {
				std::cout << "You did not enter a correct number" << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			if (x < 1 || y < 1 || r < 1) {
				std::cout << "You need to input all positive numbers" << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			Circle* c = new Circle(x, y, r);
			shapes.push_back(c);
			std::cout << c->toString();
		}
		// scale command
		else if (command.compare("scale") == 0) {
			if (parameters.size() != 4) {
				std::cout << "This command takes three (3) inputs." << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			// If the list of shapes is empty, can't be used.
			if (shapes.empty()) {
				std::cout << "Please input a shape before using this!" << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				// Loop
				continue;
			}

			int shapeNo;
			double scale1, scale2;

			try {
				shapeNo = stoi(parameters[1].c_str());
				scale1 = stod(parameters[2].c_str());
				scale2 = stod(parameters[3].c_str());
			}
			catch (const exception& e) {
				std::cout << "You did not enter a correct number." << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			if (shapeNo < 0 || scale1 < 0 || scale2 < 1) {
				std::cout << "You need to input all positive numbers" << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			// If the shape does not exist in the list of shapes
			if (shapeNo > shapes.size()) {
				std::cout << "That shape does not exist in the created list" << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			// If said shape is not a rectangle...
			if (strcmp(shapes[shapeNo - 1]->getType(), "Rectangle") != 0) {
				// And the two other inputs are not the same
				if (scale1 != scale2) {
					std::cout << "When using a Circle or Square, please input the same number twice for the scale." << endl << endl;
					userCommand = "";
					command = "";
					parameters.clear();
					// Loop
					continue;
				}
			}

			// Casting to make a movable object for scaling.
			Movable *m = dynamic_cast<Movable*>(shapes[shapeNo - 1]);
			// call scale on the two inputs
			m->scale(scale1, scale2);
			// Recalling toString to print the new output.
			std::cout << shapes[shapeNo - 1]->toString();
		}
		// move command
		else if (command.compare("move") == 0) {
			if (parameters.size() != 4) {
				std::cout << "This command takes three (3) inputs." << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			if (shapes.empty()) {
				std::cout << "Please input a shape before using this!" << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			int shapeNo, x, y;

			try {
				shapeNo = stoi(parameters[1].c_str());
				x = stoi(parameters[2].c_str());
				y = stoi(parameters[3].c_str());
			}
			catch (const exception& e) {
				std::cout << "You did not enter a correct number." << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			if (x < 0 || y < 0 || shapeNo < 1) {
				std::cout << "You need to input all positive numbers" << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			if (shapeNo > shapes.size()) {
				std::cout << "That shape does not exist in the created list" << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			Movable *m = dynamic_cast<Movable*>(shapes[shapeNo - 1]);
			m->move(x, y);

			std::cout << shapes[shapeNo - 1]->toString();
		}
		// display command
		else if (command.compare("display") == 0) {
			if (parameters.size() != 1) {
				std::cout << "This command does not take any inputs." << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			if (shapes.empty()) {
				std::cout << "Please input a shape before using this!" << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}

			// For every shape in the list
			for (int i = 1; i < shapes.size() + 1; i++) {
				// Print the number of the item
				std::cout << i << ") ";
				// And output a short form of the information
				shapes[i - 1]->toStringShort();
			}
		}
		else {
			if (command.compare("exit") != 0) {
				std::cout << "You did not input a valid command." << endl << endl;
				userCommand = "";
				command = "";
				parameters.clear();
				continue;
			}
			break;
		}

		// Clearing all used variables at the end
		userCommand = "";
		command = "";
		parameters.clear();

		std::cout << endl << endl;
	}

	std::cout << "Press any key to continue...";
	std::getchar();

	return 0;
}
