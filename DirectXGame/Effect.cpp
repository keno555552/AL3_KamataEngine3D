#include "Effect.h"
#include <algorithm>

void Fade::Initialze(int SizeX, int SizeY) {

	sprite_ = Sprite::Create(textureHandle_, {0, 0});
	sprite_->SetSize(Vector2((float)SizeX, (float)SizeY));
	sprite_->SetColor(Vector4(0, 0, 0, 1));
}

void Fade::Update() {
	switch (status_) {
	case Status::None:
		break;
	case Status::FadeIn:
		// 1フレーム分の秒数をカウントアップ
		counter_ += 1.0f / 60.0f;
		// フェード継続時間に足したら打ち止め
		if (counter_ >= duration_) {
			counter_ = duration_;
		}

		// 0.0fから1.0fの間で、経過時間がフェード継続時間に近づくほどアルファ値を大きくする
		sprite_->SetColor(Vector4(0, 0, 0, std::clamp((1.0f - counter_) / duration_, 0.0f, 1.0f)));
		break;

	case Status::FadeOut:
		// 1フレーム分の秒数をカウントアップ
		counter_ += 1.0f / 60.0f;
		// フェード継続時間に足したら打ち止め
		if (counter_ >= duration_) {
			counter_ = duration_;
		}

		// 0.0fから1.0fの間で、経過時間がフェード継続時間に近づくほどアルファ値を大きくする
		sprite_->SetColor(Vector4(0, 0, 0, std::clamp(counter_ / duration_, 0.0f, 1.0f)));
		break;
	}
}

void Fade::Draw(DirectXCommon* dxCommon) {
	if (status_ == Status::None) {
		return;
	}

	Sprite::PreDraw(dxCommon->GetCommandList());
	sprite_->Draw();
	Sprite::PostDraw();
}

void Fade::Start(Status status, float duration) {
	status_ = status;
	duration_ = duration;
	counter_ = 0.0f;
}

void Fade::Stop() { status_ = Status::None; }

bool Fade::IsFinished() {
	switch (status_) {
	case Status::FadeIn:
		break;
	case Status::FadeOut:
		if (counter_ >= duration_)
			return true;
		break;
	}
	return false;
}

KamataEngine::Model* HitEffect::model_ = nullptr;
KamataEngine::Camera* HitEffect::camera_ = nullptr;

void HitEffect::Initialze(Vector3 pos) {
	/// ワールドトランスフォームの初期化
	circleWorldTransform_.Initialize();
	circleWorldTransform_.translation_ = {pos.x, pos.y, -2.0f};

	for (WorldTransform& worldTransform : ellipseWorldTransforms_) {
		randomEngine.seed(seedGenerator());
		std::uniform_real_distribution<float> rotationDistribution(-3.14f, 3.14f);
		float rotationZ = rotationDistribution(randomEngine);
		worldTransform.Initialize();
		worldTransform.scale_ = {2.0f, 0.2f, 1.0f};
		worldTransform.rotation_ = {0.0f, 0.0f, rotationZ};
		worldTransform.translation_ = {pos.x, pos.y, -1.9f};
	}

	color_.Initialize();
	color_.SetColor({1.0f, 1.0f, 1.0f, 1.0f});
}

void HitEffect::Update() {

	hitEffectParameter_++;
	switch (hitEffectPhase_) {
	default:
	case HitEffectPhase::kSizeUp: {
		float t = static_cast<float>((float)hitEffectParameter_) / 30.0f;
		circleWorldTransform_.scale_.x = Lerp(0.5f, 1.0f, t);
		circleWorldTransform_.scale_.y = Lerp(0.5f, 1.0f, t);
		for (WorldTransform& worldTransform : ellipseWorldTransforms_) {
			worldTransform.scale_.x = Lerp(1.0f, 2.0f, t);
			worldTransform.scale_.y = Lerp(0.1f, 0.2f, t);
		}
		if (hitEffectParameter_ >= 30.0f) {
			hitEffectPhase_ = HitEffectPhase::kFadeOut;
			hitEffectParameter_ = 0;
		}
	} break;
	case HitEffectPhase::kFadeOut: {
		float t = static_cast<float>((float)hitEffectParameter_) / 30.0f;
		float alpha = Lerp(1.0f, 0.0f, t);
		color_.SetColor({1.0f, 1.0f, 1.0f, alpha});
		if (hitEffectParameter_ >= 30.0f) {
			hitEffectPhase_ = HitEffectPhase::kUnknown;
			isFinished_ = true;
		}
	} break;
	}

	{
		// アフィン変換
		Matrix4x4 mS = MakeScaleMatrixM(circleWorldTransform_.scale_);
		Matrix4x4 mR =
		    MakeRotateMatrixM(MakeRotateXMatrixM(circleWorldTransform_.rotation_.x), MakeRotateYMatrixM(circleWorldTransform_.rotation_.y), MakeRotateZMatrixM(circleWorldTransform_.rotation_.z));

		Matrix4x4 mT = MakeTranslateMatrixM(circleWorldTransform_.translation_);

		circleWorldTransform_.matWorld_ = MultM(mS, MultM(mR, mT));
		// ワールドトランスフォームの更新
		circleWorldTransform_.TransferMatrix();
	}
	for (WorldTransform& worldTransform : ellipseWorldTransforms_) {
		// アフィン変換
		Matrix4x4 mS = MakeScaleMatrixM(worldTransform.scale_);
		Matrix4x4 mR = MakeRotateMatrixM(MakeRotateXMatrixM(worldTransform.rotation_.x), MakeRotateYMatrixM(worldTransform.rotation_.y), MakeRotateZMatrixM(worldTransform.rotation_.z));
		Matrix4x4 mT = MakeTranslateMatrixM(worldTransform.translation_);

		worldTransform.matWorld_ = MultM(mS, MultM(mR, mT));
		// ワールドトランスフォームの更新
		worldTransform.TransferMatrix();
	}
}

void HitEffect::Draw() {
	for (WorldTransform& worldTransform : ellipseWorldTransforms_) {
		model_->Draw(worldTransform, *camera_, &color_);
	}
	model_->Draw(circleWorldTransform_, *camera_, &color_);
}

HitEffect* HitEffect::Create(Vector3 pos) {
	/// インスタンス生成
	HitEffect* instance = new HitEffect;
	/// newの失敗を検出
	assert(instance);
	/// インスタンスの初期化
	instance->Initialze(pos);
	/// 初期化したインスタンスを返す
	return instance;
}
