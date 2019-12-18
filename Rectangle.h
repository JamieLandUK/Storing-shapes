#pragma once

#include "Shape.h"
#include "Movable.h"
#include "Point.h"

#include <math.h>

class Rectangle : public Shape, public Movable {
private:
	// Extra data outside of the points
	// Default to 0 to cover error cases.
	double height = 0;
	double width = 0;

	// Area in rectangles is width × length
	void calculateArea() {
		area = height * width;
	}

	// Perimeter in rectangles is 2×(length+width)
	void calculatePerimeter() {
		perimeter = 2 * (height + width);
	}

	// Filling up the inherited "Shape" points vector.
	void calculatePoints() {
		// Get the original coordinates to not have to keep calling the getters.
		int ltX = leftTop.getX();
		int ltY = leftTop.getY();

		// Initialise each point according to coordinate and the direction it is from the leftTop point.
		Point rightTop = Point(ltX + width, ltY);
		points.push_back(rightTop);
		Point rightBottom = Point(ltX + width, ltY + height);
		points.push_back(rightBottom);
		Point leftBottom = Point(ltX, ltY + height);
		points.push_back(leftBottom);
	}

public:
	// Constructor
	Rectangle(int in_x, int in_y, double in_h, double in_w) {
		leftTop = Point(in_x, in_y); // Can use leftTop from Shape
		// The height and width of the rectangle
		height = in_h;
		width = in_w;

		// Initialise the other variables in play here.
		calculatePoints();
		calculateArea();
		calculatePerimeter();
	}

	// Destructor
	~Rectangle() {
		// Says which shape has been deleted (rectangle) and at what coordinates to specify.
		std::cout << "Rectangle at (" << leftTop.getX() << "," << leftTop.getY() << ") has been deleted." << std::endl;
	}


	// Moving the current shape to its new destination leftTop point
	// ...based off the two input parameters.
	void move(int newX, int newY) {
		// Create the new point.
		Point newLeftTop = Point(newX, newY);
		// Change the current leftTop to the new.
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

	// Scaling up (or down) the current shape along specified axis.
	// If one of the inputs is 1, then it remains the same.
	// 1< means that it is becoming smaller.
	// 1> means that it is becoming larger.
	void scale(float scaleX, float scaleY) {
		// Multiplying with the height and width will stretch them.
		height *= scaleX;
		width *= scaleY;

		// Error checking.
		// If either the height or the width become too small, return to 1.
		// Something can't have 0 height or width, because it would be a line.
		// A number between 0-1 would have a chance of messing with the mathematics.
		if (height < 1) {
			height = 1;
		}
		if (width < 1) {
			width = 1;
		}

		// Rounding the heights and widths so that it can't cause a problem for the coordinates.
		// The coordinates are integers, so they can't deal with non-whole numbers
		height = round(height);
		width = round(width);

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
		std::string text = "Rectangle[h="; text += std::to_string(height); text += ",w="; text += std::to_string(width); text += "]\n";
		text += "Points[("; text += std::to_string(leftTop.getX()); text += ","; text += std::to_string(leftTop.getY()); text += ")";
		text += "("; text += std::to_string(points[0].getX()); text += ","; text += std::to_string(points[0].getY()); text += ")";
		text += "("; text += std::to_string(points[1].getX()); text += ","; text += std::to_string(points[1].getY()); text += ")";
		text += "("; text += std::to_string(points[2].getX()); text += ","; text += std::to_string(points[2].getY()); text += ")]\n";
		text += "Area="; text += std::to_string(area); text += " Perimeter="; text += std::to_string(perimeter);
		return text;
	}

	// To be used in the listing function.
	void toStringShort() {
		std::cout << "Rectangle at (" << leftTop.getX() << "," << leftTop.getY() << ")" << std::endl;
	}

	char const* getType() { return "Rectangle"; }
};
