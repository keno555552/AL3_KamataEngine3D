#include "GameScene.h"
// #include "ImGuiManager.h"
// #include "PrimitiveDrawer.h"


void GameScene::Initialize() {
	textureHandle_ = TextureManager::Load("obj.png");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	model_ = Model::Create();
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

	/// サウンドデータの読み込み
	soundDataHandle_ = Audio::GetInstance()->LoadWave("fanfare.wav");

	PrimitiveDrawer::GetInstance()->SetCamera(&debugCamera_->GetCamera());
}

GameScene::~GameScene() {
	delete sprite_, sprite_ = nullptr;
	delete model_, model_ = nullptr;
	delete debugCamera_, debugCamera_ = nullptr;
}

void GameScene::Update() {

	/// スプライトの位置を更新
	Vector2 position = sprite_->GetPosition();
	/// 座標を{ 2,1 }移動
	position.x += 2.0f;
	position.y += 1.0f;
	/// 移動した座標をスプラインに反映
	sprite_->SetPosition(position);

	/// サウンドデータの再生判定
	if (!Audio::GetInstance()->IsPlaying(soundDataHandleStoper_)) {
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			soundDataHandleStoper_ = Audio::GetInstance()->PlayWave(soundDataHandle_);
		}
	}

	debugCamera_->Update();

	#ifdef _DEBUG
	ImGui::Begin("Debug");
	ImGui::Text("flag = %d", Audio::GetInstance()->IsPlaying(soundDataHandleStoper_));
	ImGui::End();

	ImGui::ShowDemoWindow();
	
	ImGui::Begin("Debug2");
	ImGui::Text("Kamata Tarou %d.%d.%d", 2050, 12, 31);
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	ImGui::End();

	#endif
}

void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

#pragma region 3Dモデル描画
	/// 前処理
	Model::PreDraw(dxCommon->GetCommandList());

	model_->Draw(worldTransform_, debugCamera_->GetCamera(), textureHandle_);
	PrimitiveDrawer::GetInstance()->DrawLine3d({}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});
	for (int i = 0; i <= 10;i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d({float(-5.0f + i), 0, -5}, {float(-5.0f + i), 0, +5}, {1.0f, 0.0f, 0.0f, 1.0f});
		PrimitiveDrawer::GetInstance()->DrawLine3d({-5, 0, float(-5.0f + i)}, {+5, 0, float(-5.0f + i)}, {0.0f, 0.0f, 1.0f, 1.0f});
	}

	/// 後処理
	Model::PostDraw();
#pragma endregion

#pragma region 2D描画の前処理
	/// 前処理  VVV
	Sprite::PreDraw(dxCommon->GetCommandList());

	sprite_->Draw();

	/// 後処理  AAA
	Sprite::PostDraw();
#pragma endregion
}
