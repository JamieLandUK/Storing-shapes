#pragma once

#include "Shape.h"
#include "Movable.h"
#include "Point.h"

#include <math.h>
#include <string>

class Circle : public Shape, public Movable {
private:
	// Need a constant for pi.
	const double PI = 3.14159;
	// The added data to make up the circle.
	double radius = 0;

	// To calculate the area of a circle is PI×r squared
	void calculateArea() {
		area = PI * pow(radius, 2);
	}

	// To calculate the perimeter (circumference) of a circle is 2×PI×r
	void calculatePerimeter() {
		perimeter = 2 * PI * radius;
	}

	// Calculating the other point rather than leftTop
	void calculatePoints() {
		// To get the other side, it is a diameter added to x and y (base+2×r)
		Point rightBottom = Point(leftTop.getX() + 2 * radius, leftTop.getY() + 2 * radius);
		points.push_back(rightBottom);
	}

public:
	// Constructor
	Circle(int in_x, int in_y, double in_r) {
		leftTop = Point(in_x, in_y); // Can use leftTop from Shape
		// The input for the radius
		radius = in_r;
		// Swapping isCircular for later use.
		isCircular = true;

		// Sending off to the calculations for the other items.
		// Adding the other point to the vector.
		calculatePoints();
		// Calculating the area and circumference.
		calculateArea();
		calculatePerimeter();
	}

	// Destructor
	~Circle() {
		// Points at a specific Circle object that is being deleted.
		std::cout << "Circle at (" << leftTop.getX() << "," << leftTop.getY() << ") has been deleted." << std::endl;
	}


	// Moving the circle from the old location to a new location specified by the user.
	void move(int newX, int newY) {
		// Creating the point which will become the new position.
		Point newLeftTop = Point(newX, newY);
		// Replacing old with the new.
		leftTop = newLeftTop;

		// Checking if the points vector is empty.
		if (!points.empty()) {
			// If it is, delete everything within.
			points.clear();
		}

		// Recalculate the points
		calculatePoints();
	}

	// Scaling a circle in this way is to expand the radius.
	// The radius is multiplied by the scale.
	// Check as the second input is used to make sure the input is right, must the be the same as scale.
	void scale(float scale, float check) {
		radius *= scale;

		// Error checking for if the radius is smaller than possible.
		if (radius < 1) {
			radius = 1;
		}

		// Rounding the radius to the nearest digit so can't mess with the integers in points.
		radius = round(radius);

		// Clearing the previous points
		if (!points.empty()) {
			points.clear();
		}

		// Recalculating all of the information.
		calculatePoints();
		calculateArea();
		calculatePerimeter();
	}

	std::string toString() {
		std::string text = "Circle[r="; text += std::to_string(radius); text += "]\n";
		text += "Points[("; text += std::to_string(leftTop.getX()); text += ","; text += std::to_string(leftTop.getY()); text += ")";
		text += "("; text += std::to_string(points[0].getX()); text += ","; text += std::to_string(points[0].getY()); text += ")]\n";
		text += "Area="; text += std::to_string(area); text += " Circumference="; text += std::to_string(perimeter);
		return text;
	}

	// To be used in the listing function.
	void toStringShort() {
		std::cout << "Circle at (" << leftTop.getX() << "," << leftTop.getY() << ")" << std::endl;
	}

	char const* getType() { return "Circle"; }
};
