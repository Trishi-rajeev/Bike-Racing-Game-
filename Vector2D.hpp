#pragma once
#include <cmath>
#include <iostream>

class Vector2D {
public:
    float x, y;

    Vector2D() : x(0.0f), y(0.0f) {}
    Vector2D(float x, float y) : x(x), y(y) {}

    // Vector operations
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    
    Vector2D operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    
    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    Vector2D& operator-=(const Vector2D& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    
    Vector2D& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // Vector math
    float Length() const {
        return std::sqrt(x * x + y * y);
    }
    
    float LengthSquared() const {
        return x * x + y * y;
    }
    
    void Normalize() {
        float len = Length();
        if (len > 0) {
            x /= len;
            y /= len;
        }
    }
    
    Vector2D Normalized() const {
        Vector2D result = *this;
        result.Normalize();
        return result;
    }
    
    float Dot(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }
    
    float Cross(const Vector2D& other) const {
        return x * other.y - y * other.x;
    }
    
    float Angle() const {
        return std::atan2(y, x);
    }
    
    static Vector2D FromAngle(float angle) {
        return Vector2D(std::cos(angle), std::sin(angle));
    }

    // Comparison operators
    bool operator==(const Vector2D& other) const {
        const float EPSILON = 0.0001f;
        return std::abs(x - other.x) < EPSILON && std::abs(y - other.y) < EPSILON;
    }

    bool operator!=(const Vector2D& other) const {
        return !(*this == other);
    }

    // Utility functions
    static Vector2D Lerp(const Vector2D& start, const Vector2D& end, float t) {
        return start + (end - start) * std::max(0.0f, std::min(1.0f, t));
    }

    static float Distance(const Vector2D& a, const Vector2D& b) {
        return (b - a).Length();
    }

    void Rotate(float angle) {
        float newX = x * std::cos(angle) - y * std::sin(angle);
        float newY = x * std::sin(angle) + y * std::cos(angle);
        x = newX;
        y = newY;
    }

    Vector2D Rotated(float angle) const {
        Vector2D result = *this;
        result.Rotate(angle);
        return result;
    }

    // Stream operator for easy debugging
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "Vector2D(" << v.x << ", " << v.y << ")";
        return os;
    }
};
