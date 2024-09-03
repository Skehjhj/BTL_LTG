#include <Vecto2D.h>

Vector2D::Vector2D(){
    x = 0.0f;
    y = 0.0f;
}

Vector2D::Vector2D(float x, float y){
    this->x = x;
    this->y = y;
}

Vector2D & Vector2D::add(const Vector2D& v){
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector2D & Vector2D::sub(const Vector2D& v){
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vector2D & Vector2D::mul(const Vector2D& v){
    this->x *= v.x;
    this->y *= v.y;
    return *this;
}

Vector2D & Vector2D::div(const Vector2D& v){
    this->x /= v.x;
    this->y /= v.y;
    return *this;
}


Vector2D& operator+(Vector2D& v1, const Vector2D& v2){
    return v1.add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2){
    return v1.sub(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2){
    return v1.mul(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2){
    return v1.div(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& v2){
    return this->add(v2);
}

Vector2D& Vector2D::operator-=(const Vector2D& v2){
    return this->sub(v2);
}

Vector2D& Vector2D::operator*=(const Vector2D& v2){
    return this->mul(v2);
}

Vector2D& Vector2D::operator/=(const Vector2D& v2){
    return this->div(v2);
}

Vector2D& Vector2D::operator*(const int& num){
    this->x *= num;
    this->y *= num;
    return *this;
}

Vector2D& Vector2D::Zero(){
    this->x = 0.0f;
    this->y = 0.0f;
    return *this;
}


std::ostream& operator<<(std::ostream& stream, const Vector2D& vec){
    stream << "(" << vec.x << ", " << vec.y << ")";
    return stream;
}

const Vector2D Vector2D::UP = Vector2D(0.0f, -1.0f);
const Vector2D Vector2D::DOWN = Vector2D(0.0f, 1.0f);
const Vector2D Vector2D::LEFT = Vector2D(-1.0f, 0.0f);
const Vector2D Vector2D::RIGHT = Vector2D(1.0f, 0.0f);
