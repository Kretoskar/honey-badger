#pragma once


namespace HoneyBadger
{
	struct Vec3
	{
		union
		{
			struct 
			{
				float x;
				float y;
				float z;
			};

			struct
			{
				float r;
				float g;
				float b;
			};
		};

		Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

		static float Dot(const Vec3& lhs, const Vec3& rhs);
		static Vec3 Cross(const Vec3& lhs, const Vec3& rhs);
	};

	Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
	Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
	Vec3 operator*(const Vec3& vec, float num);

	bool operator==(const Vec3& lhs, const Vec3& rhs);
	bool operator!=(const Vec3& lhs, const Vec3& rhs);
}