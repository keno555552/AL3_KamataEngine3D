#include "TitleWord.h"

void TitleWord::Initialize(const Camera* camera, const Vector3& position) {

	///// スブライド設定
	sprite_ = Sprite::Create(textureHandle_, {position.x, position.y});

	///// モデルの設定
	//model1_ = Model::CreateFromOBJ("title1", true);
	//model2_ = Model::CreateFromOBJ("title2", true);

	/// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	/// カメラの設定
	camera_ = camera;
}

void TitleWord::Update() {
	sprite_->SetPosition({worldTransform_.translation_.x, worldTransform_.translation_.y});
	//{
	//	// アフィン変換
	//	Matrix4x4 mS = MakeScaleMatrixM(worldTransform_.scale_);
	//	Matrix4x4 mR = MakeRotateMatrixM(MakeRotateXMatrixM(worldTransform_.rotation_.x), MakeRotateYMatrixM(worldTransform_.rotation_.y), MakeRotateZMatrixM(worldTransform_.rotation_.z));
	//
	//	Matrix4x4 mT = MakeTranslateMatrixM(worldTransform_.translation_);
	//
	//	worldTransform_.matWorld_ = MultM(mS, MultM(mR, mT));
	//}
	//
	//// ワールドトランスフォームの更新
	//worldTransform_.TransferMatrix();
	//
	/////// ImGuiのデバッグウィンドウ
	//ImGui::Begin("Debug");
	//// ImGui::Checkbox("DebugCamera", &useDebugCamera);
	//ImGui::SliderFloat3("worldTransform_,translation_", &worldTransform_.translation_.x, 0, 1280);
	//ImGui::SliderFloat3("worldTransform_,rotation_", &worldTransform_.rotation_.x, 0, 10);
	//ImGui::End();
}

void TitleWord::Render() {
	/// モデルの描画
	sprite_->Draw();
}