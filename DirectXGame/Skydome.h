#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;

class Skydome {
public:
	~Skydome();

	/// 初期化
	void Initialize(const Camera* camera);
	/// 更新
	void Update();
	/// 描画
	void Render();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* modelSkydome_ = nullptr;
	// カメラ
	const Camera* camera_ = nullptr;
};
