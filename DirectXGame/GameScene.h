#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include <vector>
#include "Player.h"
#include "Skydome.h"
#include "MapChipField.h"

Matrix4x4 Mult(const Matrix4x4& m1, const Matrix4x4& m2);

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

	void GenerateBlocks();

private:
	/// テキスチャーハンドル
	uint32_t playerTextureHandle_ = 0u;
	uint32_t boxTextureHandle_ = 0u;

	/// 3Dモテル
	Model* model_ = nullptr;
	/// BOXモデル
	Model* modelBlock_ = nullptr;
	/// ワールドトランスフォーム
	WorldTransform worldTransform_;
	/// カメラ
	Camera camera_;
	/// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;


private:

	/// スカイドーム
	Skydome* skydome_ = nullptr;

	/// 自キャラ
	Player* player_ = nullptr;

	/// マップチップ
	MapChipField* mapChipField_;
	
	///　ボックス
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
};
