#include "hbpch.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"

#define VEC3_EPSILON 0.000001f

namespace HoneyBadger
{
	float Vec3::Dot(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	Vec3 Vec3::Cross(const Vec3& lhs, const Vec3& rhs)
	{
		return
		{
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		};
	}

	float Vec3::Angle(const Vec3& lhs, const Vec3& rhs)
	{
		float sqMagL = lhs.LenSq();
		float sqMagR = rhs.LenSq();

		if (sqMagL < VEC3_EPSILON || sqMagR < VEC3_EPSILON)
		{
			return 0.0f;
		}

		float dot = Dot(lhs, rhs);
		float len = sqrtf(sqMagL) * sqrtf(sqMagR);
		return acosf(dot / len);
	}

	void Vec3::Normalize()
	{
		float lenSq = x * x + y * y + z * z;
		if (lenSq < VEC3_EPSILON)
		{
			return;
		}
		float invLen = 1.0f / sqrtf(lenSq);

		x *= invLen;
		y *= invLen;
		z *= invLen;
	}

	Vec3 Vec3::Normalized() const
	{
		float lenSq = x * x + y * y + z * z;

		if (lenSq < VEC3_EPSILON)
		{
			return Vec3(x, y, z);
		}
		float invLen = 1.0f / sqrtf(lenSq);

		return Vec3(
			x * invLen,
			y * invLen,
			z * invLen
		);
	}

	float Vec3::LenSq() const
	{
		return x * x + y * y + z * z;
	}

	Vec3& operator+=(Vec3& lhs, Vec3 rhs)
	{
		lhs.x = lhs.x + rhs.x;
		lhs.y = lhs.y + rhs.y;
		lhs.z = lhs.z + rhs.z;
		return lhs;
	}

	Vec3& operator-=(Vec3& lhs, Vec3 rhs)
	{
		lhs.x = lhs.x - rhs.x;
		lhs.y = lhs.y - rhs.y;
		lhs.z = lhs.z - rhs.z;
		return lhs;
	}

	Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
	}

	Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
	}

	Vec3 operator*(const Vec3& vec, float num)
	{
		return { vec.x * num, vec.y * num, vec.z * num };
	}

	bool operator==(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}

	bool operator!=(const Vec3& lhs, const Vec3& rhs)
	{
		return !(lhs == rhs);
	}
}

#undef VEC3_EPSILON