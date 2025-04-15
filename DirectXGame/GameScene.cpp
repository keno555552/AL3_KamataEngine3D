#include "GameScene.h"

void GameScene::Initialize() {
#pragma region System
	textureHandle_ = TextureManager::Load("obj.png");
	model_= Model::Create();
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

	/// Player関連
	// 自キャラの生成、初期化
	player_ = new Player();
	player_->Initialize(model_, textureHandle_, &debugCamera_->GetCamera());

#pragma endregion

}

GameScene::~GameScene() {
	delete model_, model_ = nullptr;
	delete debugCamera_, debugCamera_ = nullptr;

#pragma region GameObject
	delete player_,player_ = nullptr;
#pragma endregion
}

void GameScene::Update() {
#pragma region カメラ関連

	debugCamera_->Update();

#pragma endregion

#pragma region ゲームロジック
#pragma endregion

#pragma region GameObject

	/// Player関連
	// 自キャラの更新
	player_->Update();

#pragma endregion

#ifdef _DEBUG
	// ImGui::Begin("Debug");
	// ImGui::Text("flag = %d", Audio::GetInstance()->IsPlaying(soundDataHandleStoper_));
	// ImGui::End();
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

	/// 自キャラの描画
	player_->Render();
	//model_->Draw(worldTransform_, debugCamera_->GetCamera(), textureHandle_);

	/// 後処理
	Model::PostDraw();
#pragma endregion

	PrimitiveDrawer::GetInstance()->DrawLine3d({}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});
	for (int i = 0; i <= 10; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d({float(-5.0f + i), 0, -5}, {float(-5.0f + i), 0, +5}, {1.0f, 0.0f, 0.0f, 1.0f});
		PrimitiveDrawer::GetInstance()->DrawLine3d({-5, 0, float(-5.0f + i)}, {+5, 0, float(-5.0f + i)}, {0.0f, 0.0f, 1.0f, 1.0f});
	}

#pragma region 2D描画
	//// 2D描画の前処理
	//Sprite::PreDraw(dxCommon->GetCommandList());
	//// 2D描画の後処理
	//Sprite::PostDraw();
#pragma endregion
}
