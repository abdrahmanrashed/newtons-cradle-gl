#include <bits/stdc++.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <windows.h>

using std::array;
using std::vector;
using ld = GLdouble;
constexpr ld PI = 3.1415926535897932384626433832L;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct point{
    ld x, y, z;

    point(ld x = 0, ld y = 0, ld z = 0) : x(x), y(y), z(z) {}
    point(array<ld, 3> p) : x(p[0]), y(p[1]), z(p[2]) {}

    point operator-() {
        x = -x, y = -y, z = -z; return *this;
    }
    point operator+=(point p) {
        x += p.x, y += p.y, z += p.z; return *this;
    }
    point operator-=(point p) {
        return *this += -p;
    }
    ld operator*=(point p) {
        return x * p.x + y * p.y + z * p.x;
    }
    point operator*=(ld c) {
        x *= c, y *= c, z *=c; return *this;
    }
    point operator^=(point p){
        return point(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }
    friend point operator+(point p1, point p2) {
        return p1 += p2;
    }
    friend point operator-(point p1, point p2) {
        return p1 -= p2;
    }
    friend ld operator*(point p1, point p2){
        return p1 *= p2;
    }
    friend point operator*(point p, ld c){
        return p *= c;
    }
    friend point operator*(ld c, point p){
        return p *= c;
    }
    friend point operator^(point p1, point p2){
        return p1 ^= p2;
    }
    friend void glVertex3d(point p){
        return glVertex3d(p.x, p.y, p.z);
    }
    friend void glColor3d(point p){
        return glColor3d(p.x / 255, p.y / 255, p.z / 255);
    }
    friend void glTranslated(point p){
        return glTranslated(p.x, p.y, p.z);
    }
    friend void glRotated(ld angle, point p){
        return glRotated(angle, p.x, p.y, p.z);
    }
};
void square(array<point, 4> p){
    glBegin(GL_POLYGON);
    for(auto& i : p) glVertex3d(i);
    glEnd();
}
// constructs a cylinder with its center at the origin.
// @param radius cylinder radius.
// @param height cylinder height.
void cylinder(double radius, double height){
    auto y = height / 2;
    double theta = 2 * acos(-1) / 50;

    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= 50; i++){
        auto x = radius * cos(theta * i);
        auto z = radius * sin(theta * i);
        glVertex3d(x, y, z);
        glVertex3d(x, -y, z);
    }
    glEnd();
}
//the current position
point currentPosition;
//move to the specified position
void moveTo(point newPosition){
    glTranslated(newPosition - currentPosition);
    currentPosition = newPosition;
}