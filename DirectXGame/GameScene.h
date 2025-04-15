#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "Player.h"

class GameScene {
public:
	/// 初期化 / デストラクタ
	void Initialize();
	~GameScene();

	/// 更新
	void Update();

	/// 描画
	void Render();

private:
	/// テキスチャーハンドル
	uint32_t textureHandle_ = 0u;

private:

	/// 3Dモテル
	Model* model_ = nullptr;
	/// ワールドトランスフォーム
	WorldTransform worldTransform_;
	/// カメラ
	Camera camera_;
	/// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	///// ImGui Test用
	//float inputFloat3[3] = {};

private:

	/// 自キャラ
	Player* player_ = nullptr;
};
