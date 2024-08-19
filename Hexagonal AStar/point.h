#include <cmath>

// represents point in 2D space, with magnitude from the origin.
class Point {
public:
    Point() : x(0), y(0), magnitude(0) {};
    Point(int x_, int y_) : x(x_), y(y_), magnitude(sqrt((x * x) + (y * y))) {}

    const int x;
    const int y;
    const float magnitude;

    friend bool operator== (Point &p1, Point &p2);
    friend Point operator+ (Point &p1, Point &p2);
    friend Point operator- (Point &p1, Point &p2);
};

bool operator== (Point &p1, Point &p2) { return p1.x == p2.x && p1.y == p2.y; }
bool operator== (Point &p1, const Point &p2) { return p1.x == p2.x && p1.y == p2.y; }
bool operator== (const Point &p1, Point &p2) { return p1.x == p2.x && p1.y == p2.y; }
bool operator== (const Point &p1, const Point &p2) { return p1.x == p2.x && p1.y == p2.y; }

Point operator+ (Point &p1, Point &p2) { return Point(p1.x + p2.x, p1.y + p2.y); }
Point operator+ (const Point &p1, Point &p2) { return Point(p1.x + p2.x, p1.y + p2.y); }
Point operator+ (Point &p1, const Point &p2) { return Point(p1.x + p2.x, p1.y + p2.y); }
Point operator+ (const Point &p1, const Point &p2) { return Point(p1.x + p2.x, p1.y + p2.y); }

Point operator- (Point &p1, Point &p2) { return Point(p1.x - p2.x, p1.y - p2.y); }
Point operator- (const Point &p1, Point &p2) { return Point(p1.x - p2.x, p1.y - p2.y); }
Point operator- (Point &p1, const Point &p2) { return Point(p1.x - p2.x, p1.y - p2.y); }
Point operator- (const Point &p1, const Point &p2) { return Point(p1.x - p2.x, p1.y - p2.y); }