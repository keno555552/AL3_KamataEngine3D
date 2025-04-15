#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;

class Player {
public:
	/// 初期化
	void Initialize(Model* model, uint32_t textureHandle, const Camera* camera);
	/// 更新
	void Update();
	/// 描画
	void Render();

private:
	/// モデル
	Model* model_ = nullptr;
	/// ワールドトランスフォーム
	WorldTransform worldTransform_;
	/// カメラ
	const Camera* camera_ = nullptr;
	/// テクスチャーハンドル
	uint32_t textureHandle_ = 0u;
};
