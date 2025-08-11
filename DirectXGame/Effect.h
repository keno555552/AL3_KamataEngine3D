#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "myMathForAL.h"

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
