#include "myMathForAL.h"

Vector3 Lerp(Vector3 a, Vector3 b, float t) {
	Vector3 result = {};
	result.x = a.x + (b.x - a.x) * t;
	result.y = a.y + (b.y - a.y) * t;
	result.z = a.z + (b.z - a.z) * t;

	return result;
}

Matrix4x4 MultM(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 resuit = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				resuit.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return resuit;
}

Matrix4x4 MakeScaleMatrixM(const Vector3 scole) { return Matrix4x4{scole.x, 0.0f, 0.0f, 0.0f, 0.0f, scole.y, 0.0f, 0.0f, 0.0f, 0.0f, scole.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}; }

Matrix4x4 MakeRotateXMatrixM(const float theta) {
	Matrix4x4 rX = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cosf(theta), sinf(theta), 0.0f, 0.0f, -sinf(theta), cosf(theta), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return rX;
}

Matrix4x4 MakeRotateYMatrixM(const float theta) {
	Matrix4x4 rY = {cosf(theta), 0.0f, -sinf(theta), 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, sinf(theta), 0.0f, cosf(theta), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return rY;
}

Matrix4x4 MakeRotateZMatrixM(const float theta) {
	Matrix4x4 rZ = {cosf(theta), sinf(theta), 0.0f, 0.0f, -sinf(theta), cosf(theta), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return rZ;
}

Matrix4x4 MakeRotateMatrixM(const Matrix4x4 thetaX, const Matrix4x4 thetaY, const Matrix4x4 thetaZ) { return MultM(thetaX, MultM(thetaY, thetaZ)); }

Matrix4x4 MakeTranslateMatrixM(const Vector3 translate) { return Matrix4x4{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, translate.x, translate.y, translate.z, 1.0f}; }

Matrix4x4 MakeAffineMatrixM(Vector3 scale, Vector3 rotate, Vector3 translate) {
	Matrix4x4 r1 = MakeScaleMatrixM(scale);

	Matrix4x4 r2 = MakeRotateMatrixM(MakeRotateXMatrixM(rotate.x), MakeRotateYMatrixM(rotate.y), MakeRotateZMatrixM(rotate.z));

	Matrix4x4 r3 = MakeTranslateMatrixM(translate);

	// return Matrix4x4{ r3 * (r2 * r1) };
	// return Matrix4x4{ r1 * r2 * r3 };
	return Matrix4x4{MultM(r1 ,MultM(r2 , r3))};
}
