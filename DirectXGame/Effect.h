#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "myMathForAL.h"
#include <random>

class Fade {
public:
	enum class Status {
		None,
		FadeIn,
		FadeOut,
	};

public:
	void Initialze(int SizeX, int SizeY);
	void Update();
	void Draw(DirectXCommon* dxCommon);

	void Start(Status status, float duration);
	void Stop();
	bool IsFinished();

	Status GetStatus() { return status_; }

private:
	int textureHandle_ = TextureManager::Load("white1x1.png");

	Sprite* sprite_ = nullptr;

	Status status_ = Status::None;
	// フェードの持続時間
	float duration_ = 0.0f;
	// 経過時間カウンター
	float counter_ = 0.0f;

	bool finished_ = false;
};

class HitEffect {
public:
	void Initialze(Vector3 pos);
	void Update();
	void Draw();

public:
	static void SetModel(Model* model) { model_ = model; }
	static void SetCamera(Camera* camera) { camera_ = camera; }
	static HitEffect* Create(Vector3 pos);
	bool IsFinished() { return isFinished_; }

private:
	///// 振る舞い
	int hitEffectParameter_ = 0;
	enum class HitEffectPhase {
		kUnknown = -1, // リクエストのない
		kSizeUp,         // 通常状態
		kFadeOut,       // 攻撃中
	};
	HitEffectPhase hitEffectPhase_ = HitEffectPhase::kSizeUp;

private:
	static Model* model_;
	static Camera* camera_;
	WorldTransform circleWorldTransform_;
	std::array<WorldTransform, 2> ellipseWorldTransforms_;
	ObjectColor color_;
	bool isFinished_ = false;

	std::random_device seedGenerator;
	std::mt19937_64 randomEngine;
};
