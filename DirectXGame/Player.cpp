#include "Player.h"


void Player::Initialize(Model* modelIn, uint32_t textureHandle, const Camera* camera) { 
	assert(modelIn);
	assert(camera);
	model_ = modelIn;//借り
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	camera_ = camera;//借り
}

void Player::Update() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

}

void Player::Draw() {
	// モデルの描画
	model_->Draw(worldTransform_, *camera_, textureHandle_);
}
