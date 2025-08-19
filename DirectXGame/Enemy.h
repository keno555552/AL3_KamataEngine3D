#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "CameraController.h"
#include "MapChipField.h"
#include "myMathForAL.h"

/// 歩きの速さ
static inline const float kWalkSpeed = 0.05f;
/// キャラクターの当たり判定サイズ
static inline const float kEnemyWidth = 1.9f;
static inline const float kEnemyHeight = 1.9f;

///// アニメーション
/// 最初の角度[度]
static inline const float kWalkMotionAngleStart = -15.0f;
/// 最後の角度[度]
static inline const float kWalkMotionAngleEnd = 30.0f;
/// アニメーションの周期とその時間[秒]
static inline const float kWSalkMotionTime = 2.0f;

///// デスアニメーション
static inline const float kDeadAnimationTime = 1.0f;
static inline const float kDeadAnimationAnglie = 360.0f * 2.0f + 90.0f;


/// <summary>
/// 敵
/// </summary>
class Player;
class Enemy {
public:
	void Initialize(const Camera* camera, const Vector3& position);
	/// 更新
	void Update();
	/// 描画
	void Render();

	void OnCollision(const Player* player);

	Vector3 GetWorldPosition();
	AABB GetAABB();
	bool GetStateDead() const { return isDead_; }
	bool GetStateAttackEffectFinished() const { return deadEffectFinished_; }

private:
	///// 振る舞い
	enum class Behavior {
		kUnknown = -1, // リクエストのない
		kRoot,         // 通常状態
		kDead,       // 攻撃中
	};
	Behavior behavior_ = Behavior::kRoot;
	Behavior behaviorRequest_ = Behavior::kUnknown;

	/// 攻撃
	// 攻撃ギミックの経過時間カウンター
	int deadEffectParameter_ = 0;
	enum class DeadPhase {
		none,		// アタックではない
		rotate,     // 溜め
		finsih,		// 余韻
	};
	DeadPhase deadPhase_ = DeadPhase::none;

private:
	/// 単独モデル
	Model* model_ = nullptr;
	/// ワールドトランスフォーム
	WorldTransform worldTransform_;
	/// カメラ
	const Camera* camera_ = nullptr;
	/// 速度
	Vector3 velocity_ = {};
	/// 経過時間
	float walkTimer_ = 0.0f;

private:
	bool isDead_ = false;
	bool deadEffectFinished_ = false;
};
