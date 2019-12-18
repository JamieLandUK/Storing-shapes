#pragma once

#include <iostream>
#include <vector>

// Used for points on the table.
class Point {
protected:
	// The two coordinates for the point.
	int x = 0;
	int y = 0;

public:
	// Standard constructor.
	Point(int in_x, int in_y) {
		x = in_x;
		y = in_y;
	};

	// Returns to the default method of construction by the compiler.
	Point() = default;

	// Destructor
	~Point() {
		// Needs to be empty to not spam the console
	}

	// For reading x coords in toString() methods.
	int getX() {
		return x;
	}

	// For reading y coords in toString() methods.
	int getY() {
		return y;
	}
};
