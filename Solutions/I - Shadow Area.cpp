/*
* Author     : Parvez Mia
 * Problem    : Shadow Area
 * Created on : 27-09-2025
 */
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

class Point {
public:
    double x, y, z;

    Point() {
        x = y = z = 0.0;
    }

    Point(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void getInput() {
        cin >> x >> y >> z;
    }
};

Point shadow(Point s, Point p) // source, point
{
    Point q;
    q.x = s.x + s.z / (s.z - p.z) * (p.x - s.x);
    q.y = s.y + s.z / (s.z - p.z) * (p.y - s.y);
    q.z = 0.0;
    return q;
}

double area(Point a, Point b, Point c) {
    double sum = a.x * b.y - a.y * b.x +
                 b.x * c.y - b.y * c.x +
                 c.x * a.y - c.y * a.x;
    return fabs(sum) / 2.0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cout << fixed << showpoint << setprecision(6);

    Point s, a, b, c;

    int t;
    cin >> t;

    while (t--) {
        s.getInput();
        a.getInput();
        b.getInput();
        c.getInput();

        Point sa = shadow(s, a);
        Point sb = shadow(s, b);
        Point sc = shadow(s, c);
        cout << area(sa, sb, sc) << endl;
    }

    return 0;
}
