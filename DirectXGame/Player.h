#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;


class Player {
public:

	/// <summary>
	/// 初始化
	/// </summary>
	void Initialize(Model* modelIn, uint32_t textureHandle,const Camera* camera);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u; ///<<<<<uint32_t AL3_02_01
	// カメラ
	const Camera* camera_ = nullptr;
};
