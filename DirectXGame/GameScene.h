#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "CameraController.h"
#include "Effect.h"
#include "Enemy.h"
#include "MapChipField.h"
#include "Particles.h"
#include "Player.h"
#include "Skydome.h"
#include "myMathForAL.h"
#include <vector>

/// ゲームのフェイズ(型)
enum class Phase {
	kFadeIn,
	kPlay,
	kDeath,
	kFadeOut,
};

class GameScene {
public:
	/// 初期化 / デストラクタ
	void Initialize();
	~GameScene();

	/// 更新
	void Update();

	/// 描画
	void Render();

public:
	void CreateHitEffect(Vector3 pos);
	/// 終了フラグのgetter
	bool IsFinished() const { return finished_; }

private:
	void GenerateBlocks();
	void CheckAllCollisions();
	void ChangePhase();

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
	/// ゲームプレイフェイズから開始
	Phase phase_ = Phase::kPlay;

	/// 終了フラグ
	bool finished_ = false;

private:
	Fade* fade_ = new Fade();

	/// スカイドーム
	Skydome* skydome_ = new Skydome;

	/// 自キャラ
	Player* player_ = new Player;
	/// 死亡エフェクト
	DeathParticles* deathParticles_ = nullptr;

	/// 自キャラ
	std::list<Enemy*> enemyGroup_;
	/// やられエフェクト
	std::list<HitEffect*> hitEffect_;

	/// マップチップ
	MapChipField* mapChipField_ = nullptr;

	/// ボックス
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
};
