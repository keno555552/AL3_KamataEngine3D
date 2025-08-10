#include "TitleScene.h"

void TitleScene::Initialize() {

	camera_.Initialize();

	/// スカイドームの生成
	skydome_->Initialize(&camera_);

	Vector3 playerPosition = {0,-2.3f,-38.0f};
	player_->Initialize(&camera_, playerPosition);

	//Vector3 wordPosition = {0.2f, 0.5f, -46.5f};
	Vector3 wordPosition = {180.0f, 53.0f, -46.5f};
	titleWord_->Initialize(&camera_, wordPosition);
}

void TitleScene::Update() { 
	skydome_->Update(); 
	player_->UpdateForTitle();
	titleWord_->Update();

	/// ステイシーチェンジ動作
	if (Input::GetInstance()->PushKey(DIK_SPACE)) { finished_ = true; }
}

void TitleScene::Draw() {
	/// 前処理
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	titleWord_->Render();

	Sprite::PostDraw();

	Model::PreDraw(dxCommon->GetCommandList());

	skydome_->Render();
	player_->Render();

	Model::PostDraw();

}