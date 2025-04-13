#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;

class GameScene {
public:
	/// 初期化 / デストラクタ
	void Initialize();
	~GameScene();

	/// 更新
	void Update();

	/// 描画
	void Draw();

private:
	/// テキスチャーハンドル
	int textureHandle_ = 0;

private:
	/// スプライト
	Sprite* sprite_ = nullptr;

	/// 3Dモテル
	Model* model_ = nullptr;
	/// ワールドトランスフォーム
	WorldTransform worldTransform_;
	/// カメラ
	Camera camera_;
	/// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	/// サウンドデータハンドル
	int soundDataHandle_ = 0;
	int soundDataHandleStoper_ = 0;

	/// ImGui Test用
	float inputFloat3[3] = {};
};
