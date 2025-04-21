#include "GameScene.h"

void GameScene::GenerateBlocks() {
	/// ボックス生成
	// 要素数
	uint32_t kNumBlockVertical = mapChipField_->GetNumBlockVirtical();
	uint32_t kNumBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	// 要素数を変更する
	// 列数を設定(縦方向のブロック数)
	worldTransformBlocks_.resize(kNumBlockVertical);
	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
		// 列数を設定(横方向のブロック数)
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}
	// いざボックス生成
	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

void GameScene::Initialize() {
#pragma region System
	playerTextureHandle_ = TextureManager::Load("obj.png");
	boxTextureHandle_ = TextureManager::Load("cube/cube.jpg");
	model_ = Model::Create();
	modelBlock_ = Model::Create();
	/// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	/// カメラの初期化
	camera_.Initialize();
	/// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());

	PrimitiveDrawer::GetInstance()->SetCamera(&debugCamera_->GetCamera());

#pragma endregion

#pragma region GameObject

	/// スカイドームの生成
	skydome_ = new Skydome();
	skydome_->Initialize(&debugCamera_->GetCamera());

	/// Player関連
	// 自キャラの生成、初期化
	player_ = new Player();
	// 初期配置をマップチップ単位で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1, 18);
	player_->Initialize(model_, playerTextureHandle_, &debugCamera_->GetCamera(), playerPosition);

	/// マップチップの生成
	mapChipField_ = new MapChipField();
	mapChipField_->LoadMapChipCsv("Resources/stage/blocks.csv");

	/// マップチップの初期化
	GenerateBlocks();

#pragma endregion
}

GameScene::~GameScene() {
	delete model_, model_ = nullptr;
	delete debugCamera_, debugCamera_ = nullptr;

#pragma region GameObject
	delete player_, player_ = nullptr;

	delete mapChipField_, mapChipField_ = nullptr;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();

#pragma endregion
}

void GameScene::Update() {
#pragma region カメラ関連

	debugCamera_->Update();

#pragma endregion

#pragma region ゲームロジック
#pragma endregion

#pragma region GameObject

	/// スカイドームの更新
	skydome_->Update();

	/// Player関連
	// 自キャラの更新
	player_->Update();

	/// ボックスの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}

			Matrix4x4 mS = MakeScaleMatrixM(worldTransformBlock->scale_);

			Matrix4x4 mR = MakeRotateMatrixM(MakeRotateXMatrixM(worldTransformBlock->rotation_.x),
											 MakeRotateYMatrixM(worldTransformBlock->rotation_.y),
											 MakeRotateZMatrixM(worldTransformBlock->rotation_.z));

			Matrix4x4 mT = MakeTranslateMatrixM(worldTransformBlock->translation_);

			// アフィン変換
			worldTransformBlock->matWorld_ = MultM(mS, MultM(mR, mT));

			// 定数バッファに転送
			worldTransformBlock->TransferMatrix();
		}
	}

#pragma endregion

#ifdef _DEBUG
	
	//
	// ImGui::ShowDemoWindow();
	//
	// ImGui::Begin("Debug2");
	// ImGui::Text("Kamata Tarou %d.%d.%d", 2050, 12, 31);
	// ImGui::InputFloat3("InputFloat3", inputFloat3);
	// ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	// ImGui::End();

#endif
}

void GameScene::Render() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

#pragma region 3Dモデル描画
	/// 前処理
	Model::PreDraw(dxCommon->GetCommandList());

	/// スカイドームの描画
	skydome_->Render();

	/// 自キャラの描画
	player_->Render();

	/// 　ボックスの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}
			// モデルの描画
			modelBlock_->Draw(*worldTransformBlock, debugCamera_->GetCamera(), boxTextureHandle_);
		}
	}

	/// 後処理
	Model::PostDraw();
#pragma endregion

	//PrimitiveDrawer::GetInstance()->DrawLine3d({}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});
	//for (int i = 0; i <= 10; i++) {
	//	PrimitiveDrawer::GetInstance()->DrawLine3d({float(-5.0f + i), 0, -5}, {float(-5.0f + i), 0, +5}, {1.0f, 0.0f, 0.0f, 1.0f});
	//	PrimitiveDrawer::GetInstance()->DrawLine3d({-5, 0, float(-5.0f + i)}, {+5, 0, float(-5.0f + i)}, {0.0f, 0.0f, 1.0f, 1.0f});
	//}

#pragma region 2D描画
	//// 2D描画の前処理
	// Sprite::PreDraw(dxCommon->GetCommandList());
	//// 2D描画の後処理
	// Sprite::PostDraw();
#pragma endregion
}
