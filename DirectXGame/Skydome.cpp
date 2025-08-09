#include "Skydome.h"

Skydome::~Skydome() { 
	delete modelSkydome_;
}

void Skydome::Initialize(const Camera* camera) {
	/// モデルの設定
	//modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	//modelSkydome_ = Model::CreateFromOBJ("skydome2", true);
	modelSkydome_ = Model::CreateFromOBJ("skydome3", true);
	/// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	/// カメラの設定
	camera_ = camera;
}

void Skydome::Update() { 
	worldTransform_.TransferMatrix(); 
}

void Skydome::Render() {
	/// モデルの描画
	modelSkydome_->Draw(worldTransform_, *camera_);
}