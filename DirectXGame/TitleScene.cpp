#include "TitleScene.h"

TitleScene::~TitleScene() {
	delete fade_, fade_ = nullptr;
	delete skydome_,skydome_ = nullptr;
	delete player_, player_ = nullptr;
	delete titleWord_, titleWord_ = nullptr;
}

void TitleScene::Initialize() {

	camera_.Initialize();

	/// スカイドームの生成
	skydome_->Initialize(&camera_);

	fade_->Initialze(1280, 720);
	fade_->Start(Fade::Status::FadeIn, 1.0f);

	Vector3 playerPosition = {0, -2.3f, -38.0f};
	player_->Initialize(&camera_, playerPosition);

	// Vector3 wordPosition = {0.2f, 0.5f, -46.5f};
	Vector3 wordPosition = {180.0f, 53.0f, -46.5f};
	titleWord_->Initialize(&camera_, wordPosition);
}

void TitleScene::Update() {
	skydome_->Update();
	player_->UpdateForTitle();
	titleWord_->Update();
	fade_->Update();

	/// ステイシーチェンジ動作
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		fade_->Start(Fade::Status::FadeOut, 1.0f);
	}

	if (fade_->IsFinished()) {
		finished_ = true;
	}
}

void TitleScene::Draw() {
	/// 前処理
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	skydome_->Render();
	player_->Render();

	Model::PostDraw();

	Sprite::PreDraw(dxCommon->GetCommandList());

	titleWord_->Render();

	Sprite::PostDraw();

	fade_->Draw(dxCommon);
}