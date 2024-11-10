#include "hbpch.h"
#include "HoneyBadgerCore/Math/Public/Mat4.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "HoneyBadgerCore/Math/Public/MathCore.h"

#define MAT4_EPSILON 0.000001f

namespace HoneyBadger
{
	Mat4 Identity = 
	{
	  1,0,0,0,
	  0,1,0,0,
	  0,0,1,0, 
	  0,0,0,1 
	};

	bool operator==(const Mat4& a, const Mat4& b)
	{
		for (int i = 0; i < 16; ++i)
		{
			if (fabsf(a.v[i] - b.v[i]) > MAT4_EPSILON)
			{
				return false;
			}
		}
		return true;
	}

	bool operator!=(const Mat4& a, const Mat4& b)
	{
		return !(a == b);
	}

	Mat4 operator*(const Mat4& m, float f)
	{
		return Mat4(
			m.xx * f, m.xy * f, m.xz * f, m.xw * f,
			m.yx * f, m.yy * f, m.yz * f, m.yw * f,
			m.zx * f, m.zy * f, m.zz * f, m.zw * f,
			m.tx * f, m.ty * f, m.tz * f, m.tw * f
		);
	}

	Mat4 operator+(const Mat4& a, const Mat4& b)
	{
		return Mat4(
			a.xx + b.xx, a.xy + b.xy, a.xz + b.xz, a.xw + b.xw,
			a.yx + b.yx, a.yy + b.yy, a.yz + b.yz, a.yw + b.yw,
			a.zx + b.zx, a.zy + b.zy, a.zz + b.zz, a.zw + b.zw,
			a.tx + b.tx, a.ty + b.ty, a.tz + b.tz, a.tw + b.tw
		);
	}

#define M4D(aRow, bCol) \
    a.v[0 * 4 + aRow] * b.v[bCol * 4 + 0] + \
    a.v[1 * 4 + aRow] * b.v[bCol * 4 + 1] + \
    a.v[2 * 4 + aRow] * b.v[bCol * 4 + 2] + \
    a.v[3 * 4 + aRow] * b.v[bCol * 4 + 3]

	Mat4 operator*(const Mat4& a, const Mat4& b)
	{
		return Mat4(
			M4D(0, 0), M4D(1, 0), M4D(2, 0), M4D(3, 0), // Column 0
			M4D(0, 1), M4D(1, 1), M4D(2, 1), M4D(3, 1), // Column 1
			M4D(0, 2), M4D(1, 2), M4D(2, 2), M4D(3, 2), // Column 2
			M4D(0, 3), M4D(1, 3), M4D(2, 3), M4D(3, 3) // Column 3
		);
	}

#define M4V4D(mRow, x, y, z, w) \
    x * m.v[0 * 4 + mRow] + \
    y * m.v[1 * 4 + mRow] + \
    z * m.v[2 * 4 + mRow] + \
    w * m.v[3 * 4 + mRow]

	Vec4 operator*(const Mat4& m, const Vec4& v)
	{
		return Vec4(
			M4V4D(0, v.x, v.y, v.z, v.w),
			M4V4D(1, v.x, v.y, v.z, v.w),
			M4V4D(2, v.x, v.y, v.z, v.w),
			M4V4D(3, v.x, v.y, v.z, v.w)
		);
	}



	Mat4 Mat4::LookAt(const Vec3& position, const Vec3& target, const Vec3& up)
	{
		// Forward is negative Z
		Vec3 f = (target - position).Normalized() * -1.0f;
		Vec3 r = Vec3::Cross(up, f);
		if (r == Vec3(0, 0, 0))
		{
			return Mat4(); // Error
		}
		r.Normalize();
		Vec3 u = (Vec3::Cross(f, r)).Normalized();

		auto t = Vec3(
			-Vec3::Dot(r, position),
			-Vec3::Dot(u, position),
			-Vec3::Dot(f, position)
		);

		return Mat4(
			// Transpose upper 3x3 matrix to invert it
			r.x, u.x, f.x, 0,
			r.y, u.y, f.y, 0,
			r.z, u.z, f.z, 0,
			t.x, t.y, t.z, 1
		);
	}

	Mat4 Mat4::Frustum(float left, float right, float bottom, float top, float near, float far)
	{
		if (left == right || top == bottom || near == far)
		{
			HB_LOG_ERROR("Trying to create invalid frustum")
			return Mat4();
		}
		return Mat4(
			(2.0f * near) / (right - left), 0, 0, 0,
			0, (2.0f * near) / (top - bottom), 0, 0,
			(right + left) / (right - left), (top + bottom) / (top - bottom), (-(far + near)) / (far - near), -1,
			0, 0, (-2 * far * near) / (far - near), 0
		);
	}

	Mat4 Mat4::Perspective(float fov, float aspect, float znear, float zfar)
	{
		float ymax = znear * tanf(fov * MathCore::PI / 360.0f);
		float xmax = ymax * aspect;

		return Frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
	}
}


#undef M4D
#undef M4V4D
#undef MAT4_EPSILON 