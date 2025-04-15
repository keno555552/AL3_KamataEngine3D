#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle, const Camera* camera) {
	/// モデルの設定
	model_ = model;
	/// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	/// カメラの設定
	camera_ = camera;
	/// テクスチャーハンドルの設定
	textureHandle_ = textureHandle;
}

void Player::Update() { 
	worldTransform_.TransferMatrix();
}

void Player::Render() {
	assert(camera_ != nullptr);
	assert(model_ != nullptr);
	assert(textureHandle_ != 0u);
	/// モデルの描画
	model_->Draw(worldTransform_, *camera_, textureHandle_);
}
