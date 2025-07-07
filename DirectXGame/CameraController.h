#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "Player.h"

/// 範囲用構造体
struct Rect {
	float left		= 0.0f; // 左端
	float right		= 1.0f; // 右端
	float bottom	= 0.0f;	// 下端
	float top		= 1.0f;	// 上端
};		

class CameraController {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void SetTarget(Player* player) { target_ = player; }

	void SetMovableArea(Rect area) { movableArea_ = area; }

	Camera& GetCamera() { return camera_; };

	void Reset();

private:
	Vector3 targetOffset_ = {0, 0, -30.0f};

	/// カメラの移動範囲
	Rect movableArea_ = {0, 100, 0, 100};

	/// 追従対象の各方面へのカメラ移動範囲
	static inline const Rect kCameraMoveRange = {-10.0f, 10.0f, -10.0f, 10.0f};

	/// 座標補間割合
	static inline const float kInterpolationRate = 0.1f;
	/// 速度掛け律
	static inline const float kVelocityBias = 30.0f;

private:
	/// カメラ
	Camera camera_;

	Vector3 targetPosition_;

private:
	/// 借り
	Player* target_ = nullptr;
};
