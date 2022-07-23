#include <iostream>
#include <stack>
#include <stdlib.h>
using namespace std;

struct Point
{
    int x, y;
};

Point p0;

Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// A utility function to swap two points
void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0;             // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}

double polygonArea(Point *points, int n)
{
    // Initialize area
    double area = 0.0;

    // Calculate value of shoelace formula
    int j = n - 1;
    for (int i = 0; i < n; i++)
    {
        area += (points[j].x + points[i].x) * (points[j].y - points[i].y);
        j = i; // j is previous vertex to i
    }

    // Return absolute value
    return abs(area / 2.0);
}

// Prints convex hull of a set of n points.
void convexHull(Point points[], int n)
{
    // Find the bottommost point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    swap(points[0], points[min]);

    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    int m = 1; // Initialize size of modified array
    for (int i = 1; i < n; i++)
    {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;

        points[m] = points[i];
        m++; // Update size of modified array
    }

    if (m < 3)
        return;

    stack<Point> S;
    Point convexhull_points[1000];
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    for (int i = 3; i < m; i++)
    {
        while (S.size() > 1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    int index = 0;
    while (!S.empty())
    {
        Point p = S.top();
        convexhull_points[index] = p;
        index++;
        cout << "(" << p.x << ", " << p.y << ")" << endl;
        S.pop();
    }
    cout << "Dien tich: " << polygonArea(convexhull_points, index);
}

// Driver program to test above functions
int main()
{
    Point points[] = {{5, 8}, {7, 10}, {8, 9}, {9, 10}, {10, 10}, {6, 13}, {5, 12}, {6, 12}, {9, 14}, {9, 8}};
    int n = sizeof(points) / sizeof(points[0]);
    convexHull(points, n);
    return 0;
}
