#ifndef Vecto2D_h
#define Vecto2D_h
#include <iostream>
#include <cmath>

class Vector2D{
    public:
        float x;
        float y;

        Vector2D();
        Vector2D(float x, float y);

        void set(float x, float y);
        void normalize(){
            float length = sqrt(x * x + y * y);
            if(length != 0){
                x /= length;
                y /= length;
            }
        }
        float length(){
            return sqrt(x * x + y * y);
        }

        Vector2D& add(const Vector2D& v);
        Vector2D& sub(const Vector2D& v);
        Vector2D& mul(const Vector2D& v);
        Vector2D& div(const Vector2D& v);
    
        friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

        Vector2D& operator+=(const Vector2D& v2);
        Vector2D& operator-=(const Vector2D& v2);
        Vector2D& operator*=(const Vector2D& v2);
        Vector2D& operator/=(const Vector2D& v2);

        Vector2D& operator*(const int& num);
        Vector2D& Zero();
        static const Vector2D UP;
        static const Vector2D DOWN;
        static const Vector2D LEFT;
        static const Vector2D RIGHT;

        friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};

#endif