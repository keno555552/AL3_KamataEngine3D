#include "GameScene.h"
// #include "ImGuiManager.h"

void GameScene::Initialize() {
	textureHandle_ = TextureManager::Load("obj.png");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	model_ = Model::Create();
	/// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	/// カメラの初期化
	camera_.Initialize();
	/// サウンドデータの読み込み
	soundDataHandle_ = Audio::GetInstance()->LoadWave("fanfare.wav");
}

GameScene::~GameScene() {
	delete sprite_, sprite_ = nullptr;
	delete model_, model_ = nullptr;
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

	ImGui::Begin("Debug");
	ImGui::Text("flag = %d", Audio::GetInstance()->IsPlaying(soundDataHandleStoper_));
	ImGui::End();
}

void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

#pragma region 3Dモデル描画
	/// 前処理
	Model::PreDraw(dxCommon->GetCommandList());

	model_->Draw(worldTransform_, camera_, textureHandle_);

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
