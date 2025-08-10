#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "CameraController.h"
#include "MapChipField.h"
#include "myMathForAL.h"
#include <array>

#pragma region DeathParticles


class DeathParticles {
public:
	/// パーディクル数
	static inline const int kNumParticles = 8;
	/// 存続期間(消滅までの時間)<秒>
	static inline const float kDuration = 1.5f;
	/// 移動の速度
	static inline const float kSpeed = 0.1f;
	/// 分割した1個分の角度
	static inline const float kAngleUnit = 2.0f * 3.14f / kNumParticles;
public:
	void Initialize(const Camera* camera, const Vector3& position);
	void Update();
	void Draw();

	bool IsFinished() { return isFinished_; }

private:
	/// 単独モデル
	Model* model_ = nullptr;
	/// ワールドトランスフォーム
	WorldTransform worldTransform_;
	/// カメラ
	const Camera* camera_ = nullptr;

	std::array<WorldTransform, kNumParticles> worldTransforms_;

	///// アニメーション
	/// 終了フラグ
	bool isFinished_ = false;
	/// 経過時間カウント
	float counter_ = 0.0f; 
	/// 色変更オブジェクト
	ObjectColor objectColor_;
	/// 色の数値
	Vector4 color_;
};
#pragma endregion
