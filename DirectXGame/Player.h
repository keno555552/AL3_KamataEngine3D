#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "myMathForAL.h"

/////設定
/// 移動速度
static inline const float kAcceleration = 0.01f;
/// 移動減衰
static inline const float kAttenuation = 0.08f;
/// 移動限界速度
static inline const float kLimitRunSpeed = 0.5f;
/// 回転速度
static inline const float kTimeTurn = 10.0f;
/// 重力加速度
static inline const float kGravityAcceleration = 0.01f;
/// 最大落下速度
static inline const float kLimitFallSpeed = 0.5f;
/// ジャンプ初速
static inline const float kJumpAcceleration = 0.5f;


enum class LRDirection {
	kRight,
	kLeft,
	None
};


class Player {
public:
	~Player();
	/// 初期化
	void Initialize(Model* model, uint32_t textureHandle, const Camera* camera, const Vector3& position);
	/// 更新
	void Update();
	/// 描画
	void Render();

private:
	///// モデル
	Model* model_ = nullptr;

	/// 単独モデル
	Model* modelPlayer_ = nullptr;
	
	/// ワールドトランスフォーム
	WorldTransform worldTransform_;
	/// カメラ
	const Camera* camera_ = nullptr;
	/// テクスチャーハンドル
	uint32_t textureHandle_ = 0u;

private:
	//////// プレイヤーデータ
	/// 移動速度
	Vector3 velocity_ = {};
	/// 方向/開始時の方向
	LRDirection lrDirection_ = LRDirection::kRight;
	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	// 接地状態フラグ
	bool onGround_ = true;
};
