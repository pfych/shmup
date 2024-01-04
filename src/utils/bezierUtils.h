#include "../Point/Point.h"

template<typename T>
Coordinate lerp(const T &start, const T &end, float distance);

Coordinate BezierPoint(Point &start, Point &control, Point &end, float distance);

Coordinate BezierPoint(Point &start, Point &control, Point &control2, Point &End, float distance);

sf::VertexArray createLine(const Point *start, const Point *end);