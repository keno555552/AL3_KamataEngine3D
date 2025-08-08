#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"
#include "MapChipField.h"
#include "myMathForAL.h"
#include "CameraController.h"

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
	/// 追従カメラ
	CameraController* cameraController_ = nullptr;


private:

	/// スカイドーム
	Skydome* skydome_ = new Skydome;

	/// 自キャラ
	Player* player_ = new Player;

	/// 自キャラ
	Enemy* enemy_ = new Enemy;

	/// マップチップ
	MapChipField* mapChipField_ = nullptr;
	
	///　ボックス
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
};
