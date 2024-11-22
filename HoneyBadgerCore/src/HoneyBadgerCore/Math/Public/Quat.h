#pragma once

#include "HoneyBadgerCore/Math/Public/Vec3.h"

namespace HoneyBadger
{
	struct Mat4;

	struct Quat
	{
		union 
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};

			struct
			{
				Vec3 vector;
				float scalar;
			};

			float v[4];
		};


		Quat() :
			x(0), y(0), z(0), w(1) {}

		Quat(float x, float y, float z, float w) :
			x(x), y(y), z(z), w(w) {}
		 
		Quat(float angle, const Vec3& axis);

		Vec3 GetAxis() const;
		float GetAngle() const;
		float LenSq() const;
		float Len() const;
		void Normalize();
		Quat Normalized() const;
		Quat Inverse() const;
		Mat4 ToMat4();

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Quat, x,y,z,w)
	};

	Quat operator+(const Quat& a, const Quat& b);
	Quat operator-(const Quat& a, const Quat& b);
	Quat operator*(const Quat& a, float b);
	Quat operator-(const Quat& q);
	bool operator==(const Quat& left, const Quat& right);
	bool operator!=(const Quat& a, const Quat& b);

	Quat operator*(const Quat& Q1, const Quat& Q2);
	Quat operator*(const Quat& Q1, const Quat& Q2);
	Vec3 operator*(const Quat& q, const Vec3& v);
	Quat operator^(const Quat& q, float f);
}