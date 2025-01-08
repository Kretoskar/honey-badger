#pragma once

#include "HoneyBadgerCore/Math/Public/Vec4.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"

namespace HoneyBadger
{
	struct Vec3;

	/* 
	 * Column major matrix
	 * |0-4--8-12|
	 * |1-5--9-13|
	 * |2-6-10-14|
	 * |3-7-11-15|
	 * right to left multiplication
	 * 
	 * position is stored in column
	 * |r.x-u.x-f.x-p.x|
	 * |r.y-u.y-f.y-p.y|
	 * |r.z-u.z-f.z-p.z|
	 * |--0---0---0---1|
	 */
	struct Mat4
	{
		union
		{
			float v[16];

			struct
			{
				Vec4 right;
				Vec4 up;
				Vec4 forward;
				Vec4 position;
			};

			struct  
			{
				/*
				* |0-4--8-12|
				* |1-5--9-13|
				* |2-6-10-14|
				* |3-7-11-15|
				*/
				float c0r0; // 0
				float c0r1; // 1
				float c0r2; // 2
				float c0r3; // 3
				float c1r0; // 4
				float c1r1; // 5
				float c1r2; // 6
				float c1r3; // 7
				float c2r0; // 8
				float c2r1; // 9
				float c2r2; // 10
				float c2r3; // 11
				float c3r0; // 12
				float c3r1; // 13
				float c3r2; // 14
				float c3r3; // 15
			};

			struct
			{
				/*
				* |0-4--8-12|
				* |1-5--9-13|
				* |2-6-10-14|
				* |3-7-11-15|
				*/
				float xx; // 0
				float xy; // 1
				float xz; // 2
				float xw; // 3
				float yx; // 4
				float yy; // 5
				float yz; // 6
				float yw; // 7
				float zx; // 8
				float zy; // 9
				float zz; // 10
				float zw; // 11
				float tx; // 12
				float ty; // 13
				float tz; // 14
				float tw; // 15
			};
		};

		// Default constructor creates identity matrix
		Mat4() :
			c0r0(1), c0r1(0), c0r2(0), c0r3(0),
			c1r0(0), c1r1(1), c1r2(0), c1r3(0),
			c2r0(0), c2r1(0), c2r2(1), c2r3(0),
			c3r0(0), c3r1(0), c3r2(0), c3r3(1)
		{}

		Mat4(float c0r0, float c0r1, float c0r2, float c0r3,
			float c1r0, float c1r1, float c1r2, float c1r3,
			float c2r0, float c2r1, float c2r2, float c2r3,
			float c3r0, float c3r1, float c3r2, float c3r3) :
			c0r0(c0r0), c0r1(c0r1), c0r2(c0r2), c0r3(c0r3),
			c1r0(c1r0), c1r1(c1r1), c1r2(c1r2), c1r3(c1r3),
			c2r0(c2r0), c2r1(c2r1), c2r2(c2r2), c2r3(c2r3),
			c3r0(c3r0), c3r1(c3r1), c3r2(c3r2), c3r3(c3r3)
		{}

		static Mat4 Identity;

		static Mat4 Perspective(float fov, float aspect, float znear, float zfar);
		static Mat4 LookAt(const Vec3& position, const Vec3& target, const Vec3& up);
		static Mat4 Frustum(float left, float right, float bottom, float top, float near, float far);
		static Mat4 Scaled(const Mat4& mat, const Vec3& scale);
		static Vec3 TransformVector(const Mat4& m, const Vec3& v);
		static Mat4 FromPosition(const Vec3& pos);
		void SetScale (const Vec3& scale);
		Vec3 GetScale() const;
		float Determinant();
		Mat4 Transposed();
		Mat4 Adjugate();
		Mat4 Inverse();

	};

	bool operator==(const Mat4& a, const Mat4& b);
	bool operator!=(const Mat4& a, const Mat4& b);
	Mat4 operator*(const Mat4& m, float f);
	Mat4 operator+(const Mat4& a, const Mat4& b);
	Mat4 operator*(const Mat4& a, const Mat4& b);
	Vec4 operator*(const Mat4& m, const Vec4& v);
}