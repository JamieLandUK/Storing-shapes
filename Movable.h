#pragma once

// To be inherited and provide move and scale functions to the three shapes.
class Movable {
public:
	// Virtual so that it can be edited by inheriting shapes and be fully usuable.
	// Move provides the ability for the shape to move along the x and y axis.
	// It will move to the new coordinates from the old.
	// Once leftTop is moved, rightTop, leftBottom and rightBottom are recalculated.
	virtual void move(int newX, int newY) {};
	// Scale a shape in two dimensions.
	// Giving two factors to affect the two coordinates.
	// scaleX will stretch the x in that direction,
	// scaleY would do the same for y.
	// It will update the leftTop and recalculate the other points after changing the height and width.
	// Area and perimeter/circumference of the shape will also need to be updated.
	// In non-rectangular shapes, scale is isotropic.
	virtual void scale(float scaleX, float scaleY) {};
};
