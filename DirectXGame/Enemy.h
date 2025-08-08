#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "MapChipField.h"
#include "myMathForAL.h"

/// 歩きの速さ
static inline const float kWalkSpeed = 0.05f;

///// アニメーション
/// 最初の角度[度]
static inline const float kWalkMotionAngleStart = -15.0f;
/// 最後の角度[度]
static inline const float kWalkMotionAngleEnd = 30.0f;
/// アニメーションの周期とその時間[秒]
static inline const float kWSalkMotionTime = 2.0f;


/// <summary>
/// 敵
/// </summary>
class Enemy {
public:
	void Initialize(const Camera* camera, const Vector3& position);
	/// 更新
	void Update();
	/// 描画
	void Render();

private:
	/// 単独モデル
	Model* model_ = nullptr;
	/// ワールドトランスフォーム
	WorldTransform worldTransform_;
	/// 速度
	Vector3 velocity_ = {};
	/// カメラ
	const Camera* camera_ = nullptr;
	/// 経過時間
	float walkTimer_ = 0.0f;
};
