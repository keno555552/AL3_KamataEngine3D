#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;



Vector3 Lerp(Vector3 a, Vector3 b, float t);

Matrix4x4 MultM(const Matrix4x4& m1, const Matrix4x4& m2);

/// <summary>
/// 拡縮のVector3からMatrix4x4への変換
/// </summary>
/// <param name="scole">Vector3</param>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakeScaleMatrixM(const Vector3 scole);

Matrix4x4 MakeRotateXMatrixM(const float theta);

Matrix4x4 MakeRotateYMatrixM(const float theta);

Matrix4x4 MakeRotateZMatrixM(const float theta);

/// <summary>
/// 回転のVector3からMatrix4x4への変換
/// </summary>
/// <param name="rotate">Vector3</param>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakeRotateMatrixM(const Matrix4x4 thetaX, const Matrix4x4 thetaY, const Matrix4x4 thetaZ);

/// <summary>
/// 移動のVector3からMatrix4x4への変換
/// </summary>
/// <param name="translate">Vector3</param>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakeTranslateMatrixM(const Vector3 translate);

/// <summary>
/// Matrix4x4のアフィン変換(Vector3から)
/// </summary>
/// <param name="scole">Vector3</param>
/// <param name="rotate">Vector3</param>
/// <param name="translate">Vector3</param>
/// <returns>結果Matrix4x4</returns>
Matrix4x4 MakeAffineMatrixM(Vector3 scale, Vector3 rotate, Vector3 translate);
