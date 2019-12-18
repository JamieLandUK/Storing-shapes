#pragma once

#include "Shape.h"
#include "Movable.h"
#include "Point.h"

#include <math.h>
#include <string>

class Square : public Shape, public Movable {
private:
	// The length of every edge on the square.
	double edge = 0;

	// Area for a square is the length squared.
	void calculateArea() {
		area = pow(edge, 2);
	}

	// Perimeter for a square is 4×length
	void calculatePerimeter() {
		perimeter = 4 * edge;
	}

	// Filling up the inherited "Shape" points vector.
	void calculatePoints() {
		// Get the original coordinates to not have to keep calling the getters.
		int ltX = leftTop.getX();
		int ltY = leftTop.getY();

		// Initialise each point according to coordinate and the direction it is from the leftTop point.
		Point rightTop = Point(ltX + edge, ltY);
		points.push_back(rightTop);
		Point rightBottom = Point(ltX + edge, ltY + edge);
		points.push_back(rightBottom);
		Point leftBottom = Point(ltX, ltY + edge);
		points.push_back(leftBottom);
	}

public:
	// Constructor
	Square(int in_x, int in_y, double in_e) {
		leftTop = Point(in_x, in_y); // Can use leftTop from Shape
		// The input for the single edge
		edge = in_e;

		// Initialise the other variables
		calculatePoints();
		calculateArea();
		calculatePerimeter();
	}

	// Destructor
	~Square() {
		// Says which shape has been deleted (rectangle) and at what coordinates to specify.
		std::cout << "Square at (" << leftTop.getX() << "," << leftTop.getY() << ") has been deleted." << std::endl;
	}


	// Moving the current shape to a new location based off user input.
	void move(int newX, int newY) {
		// Create a point where the user has asked.
		Point newLeftTop = Point(newX, newY);
		// The old is replaced with the new.
		leftTop = newLeftTop;

		// Check if the stored points vector is empty.
		// If it is empty, it has not been calculated in the first place.
		// If it is not empty, the points have been previously calculated.
		if (!points.empty()) {
			// Remove all of the old points from inside.
			points.clear();
		}
		// Calculate the points again.
		calculatePoints();
	}

	// Scaling a square would mean changing the length of every edge.
	// This means that it can only have one input unless it becomes a rectangle.
	// It expands in a diagonal bottom right direction.
	// The check input is used to cover the case where Rectangle could be used and has two different inputs.
	// Must be the same as the first.
	void scale(float scale, float check) {
		// Expand (or shrink) the edge
		edge *= scale;

		// Error checking since an edge can't be 0 long;
		if (edge < 1) {
			edge = 1;
		}

		// The edge is rounded up (or down) so that the points are whole numbers.
		edge = round(edge);

		if (!points.empty()) {
			points.clear();
		}

		// The leftTop point should stay the same, but the other points will have to be recalculated.
		calculatePoints();
		// The area and perimeter will also need to be recalculated due to the changes of height and width.
		calculateArea();
		calculatePerimeter();
	}

	// Outputting the exact dimensions, location and information of the current Rectangle
	std::string toString() {
		std::string text = "Square[e="; text += std::to_string(edge); text += "]\n";
		text += "Points[("; text += std::to_string(leftTop.getX()); text += ","; text += std::to_string(leftTop.getY()); text += ")";
		text += "("; text += std::to_string(points[0].getX()); text += ","; text += std::to_string(points[0].getY()); text += ")";
		text += "("; text += std::to_string(points[1].getX()); text += ","; text += std::to_string(points[1].getY()); text += ")";
		text += "("; text += std::to_string(points[2].getX()); text += ","; text += std::to_string(points[2].getY()); text += ")]\n";
		text += "Area="; text += std::to_string(area); text += " Perimeter="; text += std::to_string(perimeter);
		return text;
	}

	// To be used in the listing function.
	void toStringShort() {
		std::cout << "Square at (" << leftTop.getX() << "," << leftTop.getY() << ")" << std::endl;
	}

	char const* getType() { return "Square"; }
};
