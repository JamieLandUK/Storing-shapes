#pragma once

#include "Point.h"

#include <iostream>
#include <vector>
#include <string>

class Shape {
public:
	// Inputs used in the three different kinds of shapes.
	double area;
	double perimeter;
	// Default boolean to false, if it is making a circle, set to true.
	bool isCircular = false;
	// The one main point that is to be used throughout the program,
	// it is possible to fetch all data for the shape from just this one point and other information.
	// For example, to find the bottom right point of a rectangle from the top left point, it is the x+width and y+height.
	Point leftTop;
	// For rectangles and squares: All four points in order: LeftTop, RightTop, LeftBottom, RightBottom
	// For circles: just the LeftTop is where it would be as a square, and the RightBottom is x+2*the radius and y+2*the radius
	std::vector<Point> points;

	// The standard constructor.
	Shape(int in_x, int in_y) {};
	Shape() = default;

	// Virtual destructor so that the inherited destuctors are called in the correct cases.
	virtual ~Shape() {
		std::cout << "Default shape destructed" << std::endl;
	};

	// Prints the position of the shape.
	// Virtual so it can be edited properly and provide the full data for the final shape.
	virtual std::string toString() {
		std::string text = "Shape: x="; text += leftTop.getX(); text += ", y="; text += leftTop.getY();
		return text;
	};

	virtual void toStringShort() {
		std::cout << "Default Shape shortform called." << std::endl;
	};

	// To be overridden in the child functions ==
	virtual void calculateArea() {};
	virtual void calculatePerimeter() {};
	// ==
	// CalculatePoints is an abstract function
	virtual void calculatePoints() = 0;
	virtual char const* getType() = 0;
};
