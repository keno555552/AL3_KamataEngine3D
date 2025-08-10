#include "Particles.h"
#include <algorithm>
#include <numbers>

void DeathParticles::Initialize(const Camera* camera, const Vector3& position) {

	/// モデルの設定
	model_ = Model::CreateFromOBJ("particlesWhiteBall", true);

	/// カメラの設定
	camera_ = camera;

	/// アニメーションの設定
	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};

	/// ワルドトランスフォーム初期化
	int num = kNumParticles;
	if (num > 0) {
		for (WorldTransform& worldTransform : worldTransforms_) {
			worldTransform.Initialize();
			worldTransform.translation_ = position;
		}
	}
}

void DeathParticles::Update() {
	if (isFinished_) { return; }

	/// 移動
	for (int i = 0; i < kNumParticles; i++) {
		// 基本となる速度ベクトル
		Vector3 velocity = {kSpeed, 0, 0};
		// 同軸角を計算する
		float angle = kAngleUnit * i;
		// Z軸まわり回転行列
		Matrix4x4 matrixRotation = MakeRotateZMatrixM(angle);
		// 速度ベクトルをMatrixに変換
		Matrix4x4 matrixTranslation = MakeTranslateMatrixM(velocity);
		// 角道合わせの速度ベクトル計算
		Matrix4x4 mixMatrix = MultM(matrixTranslation, matrixRotation);
		// 結果ベクトルをvector3に戻す
		velocity = TranformM4toV3(mixMatrix);

		// 結果ベクトルをワルドトランスフォームに足す
		worldTransforms_[i].translation_.x += velocity.x;
		worldTransforms_[i].translation_.y += velocity.y;
		worldTransforms_[i].translation_.z += velocity.z;
	}

	/// ワールドトランスフォームの更新
	if (!worldTransforms_.empty()) {
		for (WorldTransform& worldTransform : worldTransforms_) {
			// アフィン変換
			Matrix4x4 mS = MakeScaleMatrixM(worldTransform.scale_);
			Matrix4x4 mR = MakeRotateMatrixM(MakeRotateXMatrixM(worldTransform.rotation_.x), MakeRotateYMatrixM(worldTransform.rotation_.y), MakeRotateZMatrixM(worldTransform.rotation_.z));
			Matrix4x4 mT = MakeTranslateMatrixM(worldTransform.translation_);

			worldTransform.matWorld_ = MultM(mS, MultM(mR, mT));
			worldTransform.TransferMatrix();
		}
	}

	/// アニメーション
	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	// 存続時間の上限に足したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了扱いにする
		isFinished_ = true;
	}

	color_.w = std::clamp((1.0f - counter_ / kDuration), 0.0f, 1.0f);

	objectColor_.SetColor(color_);

	///// ImGuiのデバッグウィンドウ
	//ImGui::Begin("Debug");
	//// ImGui::Checkbox("DebugCamera", &useDebugCamera);
	//ImGui::SliderFloat("counter_", &counter_, 1, 50);
	//ImGui::Checkbox("isFinished_", &isFinished_);
	//ImGui::End();
}

void DeathParticles::Draw() {
	if (isFinished_) { return; }
	if (!worldTransforms_.empty()) {
		for (WorldTransform& worldTransform : worldTransforms_) {
			model_->Draw(worldTransform, *camera_,&objectColor_);
		}
	}
}