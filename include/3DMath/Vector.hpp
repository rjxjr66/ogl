#pragma once
#include <cmath>

const float Pi = 4 * std::atan(1.0f);
const float TwoPi = 2 * Pi;

template <typename T>
struct Vector2 {
    Vector2() {}
    Vector2(T x, T y) : x(x), y(y) {}
    T Dot(const Vector2& v) const
    {
        return x * v.x + y * v.y;
    }
    Vector2 operator+(const Vector2& v) const
    {
        return Vector2(x + v.x, y + v.y);
    }
	 Vector2 operator/(const Vector2& v) const
    {
        return Vector2(x / v.x, y / v.y);
    }
    Vector2 operator-(const Vector2& v) const
    {
        return Vector2(x - v.x, y - v.y);
    }
    Vector2 operator-() const
    {
        return Vector2(-x, -y);
    }
    void operator+=(const Vector2& v)
    {
        *this = Vector2(x + v.x, y + v.y);
    }
    void operator-=(const Vector2& v)
    {
        *this = Vector2(x - v.x, y - v.y);
    }
    Vector2 operator/(T s) const
    {
        return Vector2(x / s, y / s);
    }
    Vector2 operator*(float s) const
    {
        return Vector2(x * s, y * s);
    }
    void operator/=(float s)
    {
        *this = Vector2(x / s, y / s);
    }
    void operator*=(float s)
    {
        *this = Vector2(x * s, y * s);
    }
    void Normalize()
    {
        float s = 1.0f / Length();
        x *= s;
        y *= s;
    }
    Vector2 Normalized() const 
    {
        Vector2 v = *this;
        v.Normalize();
        return v;
    }
    T LengthSquared() const
    {
        return x * x + y * y;
    }
    T Length() const
    {
        return sqrtf((float)LengthSquared());
    }
    operator Vector2<float>() const
    {
        return Vector2<float>(x, y);
    }
    bool operator==(const Vector2& v) const
    {
        return x == v.x && y == v.y;
    }
    Vector2 Lerp(float t, const Vector2& v) const
    {
        return Vector2(x * (1 - t) + v.x * t,
                       y * (1 - t) + v.y * t);
    }
    const T* Pointer() const
    {
        return &x;
    }
    template <typename P>
    P* Write(P* pData)
    {
        Vector2* pVector = (Vector2*) pData;
        *pVector++ = *this;
        return (P*) pVector;
    }
    T x;
    T y;
};

template <typename T>
struct Vector3 {
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

    T LengthSquared() const
    {
        return x * x + y * y + z * z;
    }
    T Length() const
    {
		return std::sqrt(LengthSquared());
    }
    void Normalize()
    {
        float s = 1.0f / Length();
        x *= s;
        y *= s;
        z *= s;
    }
    Vector3 Normalized() const 
    {
        Vector3 v = *this;
        v.Normalize();
        return v;
    }
    Vector3 Cross(const Vector3& v) const
    {
        return Vector3(y * v.z - z * v.y,
                       z * v.x - x * v.z,
                       x * v.y - y * v.x);
    }
    T Dot(const Vector3& v) const
    {
        return (x * v.x) + (y * v.y) + (z * v.z);
    }
    Vector3 operator+(const Vector3& v) const
    {
        return Vector3(x + v.x, y + v.y,  z + v.z);
    }
    void operator+=(const Vector3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }
    void operator-=(const Vector3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }
    void operator/=(T s)
    {
        x /= s;
        y /= s;
        z /= s;
    }
    Vector3 operator-(const Vector3& v) const
    {
        return Vector3(x - v.x, y - v.y,  z - v.z);
    }
    Vector3 operator-() const
    {
        return Vector3(-x, -y, -z);
    }
    Vector3 operator*(T s) const
    {
        return Vector3(x * s, y * s, z * s);
    }
    Vector3 operator/(T s) const
    {
        return Vector3(x / s, y / s, z / s);
    }
    bool operator==(const Vector3& v) const
    {
        return x == v.x && y == v.y && z == v.z;
    }
    Vector3 Lerp(float t, const Vector3& v) const
    {
        return Vector3(x * (1 - t) + v.x * t,
                       y * (1 - t) + v.y * t,
                       z * (1 - t) + v.z * t);
    }
	Vector3 RotateAxis(const Vector3& axis, T degrees) {
		Vector3 rotator;
		Vector3 rx;
		Vector3 ry;
		Vector3 rz;

		Vector3 result(*this);

		// Normalize the axis and store in rz for later
		// potential use.
		rz = axis / axis.Length();

		// If this vector is parallel to the axis (Now in rz),
		// don't bother rotating it. Check with Cauchy-Schwartz
		// u dot v == length of u * length of v iff u is linearly
		// dependant on v. Length of rz is one, because it is
		// normalized.
		if (!(fabs(Dot(rz)) == Length())) {
			// If we're not already rotating around the Z, transform to Z
			if (axis.x == 0 && axis.y == 0) {
				// In this case, the axis is along Z already, so we
				// wont bother rotating our axis of rotation to Z.
				// Since we're checking directly for 0, this is going
				// to happen extremely rarely. However, if it does
				// happen, some of the below math falls apart. So,
				// we check.
				rotator = result;
			}
			else {
				// Build the rotation matrix
				// rz was assigned already while normalizing the axis.
				rx = Cross(axis);
				rx.Normalize();
				ry = rz.Cross(rx);

				// Move this vector such that the axis would be in Z
				rotator = Vector3(rx.Dot(*this), ry.Dot(*this), rz.Dot(*this));
			}

			// Rotate this vector around Z
			rotator = (Matrix4<T>::RotateZ(degrees) * Vector4<T>(rotator, 0)).ToVec3();

			if (axis.x == 0 && axis.y == 0) {
				result = rotator;
			}
			else {
				// Move back so axis is in original location.
				result.x = rotator.x * rx.x +
					rotator.y * ry.x +
					rotator.z * rz.x;
				result.y = rotator.x * rx.y +
					rotator.y * ry.y +
					rotator.z * rz.y;
				result.z = rotator.x * rx.z +
					rotator.y * ry.z +
					rotator.z * rz.z;
			}
		}

		return result;
	}
    const T* Pointer() const
    {
        return &x;
    }
    template <typename P>
    P* Write(P* pData)
    {
        Vector3<T>* pVector = (Vector3<T>*) pData;
        *pVector++ = *this;
        return (P*) pVector;
    }
    T x;
    T y;
    T z;
};

template <typename T>
struct Vector4 {
    Vector4() {}
    Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    Vector4(const Vector3<T>& v, T w) : x(v.x), y(v.y), z(v.z), w(w) {}
    T Dot(const Vector4& v) const
    {
        return x * v.x + y * v.y + z * v.z + w * v.w;
    }
    Vector4 operator-() const
    {
        return Vector4(-x, -y, -z, -w);
    }
    Vector4 Lerp(float t, const Vector4& v) const
    {
        return Vector4(x * (1 - t) + v.x * t,
                       y * (1 - t) + v.y * t,
                       z * (1 - t) + v.z * t,
                       w * (1 - t) + v.w * t);
    }
    Vector4 operator+(const Vector4& v) const
    {
        return Vector4(x + v.x, y + v.y,  z + v.z, w + v.w);
    }
    Vector4 operator*(T s) const
    {
        return Vector4(x * s, y * s, z * s, w * s);
    }
    const T* Pointer() const
    {
        return &x;
    }

	Vector3<T> ToVec3() {
		return Vector3<T>(x, y, z);
	}

    T x;
    T y;
    T z;
    T w;
};

typedef Vector2<bool> bvec2;

typedef Vector2<int> ivec2;
typedef Vector3<int> ivec3;
typedef Vector4<int> ivec4;

typedef Vector2<float> vec2;
typedef Vector3<float> vec3;
typedef Vector4<float> vec4;

