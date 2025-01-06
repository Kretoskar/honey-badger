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

	Mat4 Mat4::Scaled(const Mat4& mat, const Vec3& scale)
	{
		Mat4 m(mat);
		m.c0r0 *= scale.x;
		m.c1r1 *= scale.y;
		m.c2r2 *= scale.z;

		return m;
	}

	void Mat4::SetScale(const Vec3& scale)
	{
		c0r0 = scale.x;
		c1r1 = scale.y;
		c2r2 = scale.z;
	}

	Vec3 Mat4::TransformVector(const Mat4& m, const Vec3& v)
	{
		return Vec3(
			M4V4D(0, v.x, v.y, v.z, 0.0f),
			M4V4D(1, v.x, v.y, v.z, 0.0f),
			M4V4D(2, v.x, v.y, v.z, 0.0f)
		);
	}

	Mat4 Mat4::Transposed()
	{
		return Mat4(
			xx, yx, zx, tx,
			xy, yy, zy, ty,
			xz, yz, zz, tz,
			xw, yw, zw, tw
		);
	}

	Mat4 Mat4::Perspective(float fov, float aspect, float znear, float zfar)
	{
		float ymax = znear * tanf(fov * MathCore::PI / 360.0f);
		float xmax = ymax * aspect;

		return Frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
	}

	#define M4_3X3MINOR(c0, c1, c2, r0, r1, r2) \
    (v[c0 * 4 + r0] * (v[c1 * 4 + r1] * v[c2 * 4 + r2] - v[c1 * 4 + r2] * v[c2 * 4 + r1]) - \
     v[c1 * 4 + r0] * (v[c0 * 4 + r1] * v[c2 * 4 + r2] - v[c0 * 4 + r2] * v[c2 * 4 + r1]) + \
     v[c2 * 4 + r0] * (v[c0 * 4 + r1] * v[c1 * 4 + r2] - v[c0 * 4 + r2] * v[c1 * 4 + r1]))

	float Mat4::Determinant()
	{
		return v[0] * M4_3X3MINOR(1, 2, 3, 1, 2, 3)
			- v[4] * M4_3X3MINOR(0, 2, 3, 1, 2, 3)
			+ v[8] * M4_3X3MINOR(0, 1, 3, 1, 2, 3)
			- v[12] * M4_3X3MINOR(0, 1, 2, 1, 2, 3);
	}

	Mat4 Mat4::Adjugate()
	{
		// Cofactor(M[i, j]) = Minor(M[i, j]] * pow(-1, i + j)
		Mat4 cofactor;

		cofactor.v[0] = M4_3X3MINOR(1, 2, 3, 1, 2, 3);
		cofactor.v[1] = -M4_3X3MINOR(1, 2, 3, 0, 2, 3);
		cofactor.v[2] = M4_3X3MINOR(1, 2, 3, 0, 1, 3);
		cofactor.v[3] = -M4_3X3MINOR(1, 2, 3, 0, 1, 2);

		cofactor.v[4] = -M4_3X3MINOR(0, 2, 3, 1, 2, 3);
		cofactor.v[5] = M4_3X3MINOR(0, 2, 3, 0, 2, 3);
		cofactor.v[6] = -M4_3X3MINOR(0, 2, 3, 0, 1, 3);
		cofactor.v[7] = M4_3X3MINOR(0, 2, 3, 0, 1, 2);

		cofactor.v[8] = M4_3X3MINOR(0, 1, 3, 1, 2, 3);
		cofactor.v[9] = -M4_3X3MINOR(0, 1, 3, 0, 2, 3);
		cofactor.v[10] = M4_3X3MINOR(0, 1, 3, 0, 1, 3);
		cofactor.v[11] = -M4_3X3MINOR(0, 1, 3, 0, 1, 2);

		cofactor.v[12] = -M4_3X3MINOR(0, 1, 2, 1, 2, 3);
		cofactor.v[13] = M4_3X3MINOR(0, 1, 2, 0, 2, 3);
		cofactor.v[14] = -M4_3X3MINOR(0, 1, 2, 0, 1, 3);
		cofactor.v[15] = M4_3X3MINOR(0, 1, 2, 0, 1, 2);

		return cofactor.Transposed();
	}

	Mat4 Mat4::Inverse()
	{
		float det = Determinant();

		if (det == 0.0f)
		{
			// Epsilon check would need to be REALLY small
			std::cout << "WARNING: Trying to invert a matrix with a zero determinant\n";
			return Mat4();
		}
		Mat4 adj = Adjugate();

		return adj * (1.0f / det);
	}
}


#undef M4D
#undef M4V4D
#undef MAT4_EPSILON 