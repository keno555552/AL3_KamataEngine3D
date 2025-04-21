#define NOMINMAX ///<<<必ずすべでのファイルの先頭に書くこと
#include "Player.h"
#include <algorithm>
#include <numbers>

void Player::Initialize(Model* model, uint32_t textureHandle, const Camera* camera, const Vector3& position) {
	/// モデルの設定
	model_ = model;
	modelPlayer_ = Model::CreateFromOBJ("player4", true);
	// modelPlayer_ = Model::CreateFromOBJ("skydome2", true);

	/// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	/// カメラの設定
	camera_ = camera;
	/// テクスチャーハンドルの設定
	textureHandle_ = textureHandle;

	/// ワールドトランスフォームの初期化
	// 初期回転
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	turnFirstRotationY_ = worldTransform_.rotation_.y;
}

Player::~Player() {
	// delete modelPlayer_;
}

void Player::Update() {

	/// プレイヤーの移動
	bool landing = false;
	///// 移動
	if (onGround_) {
		// 左右移動捜索
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {

			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				if (velocity_.x < 0.0f) {
					// 速度と逆方向に入力中に急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAcceleration;

				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}
			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				if (velocity_.x > 0.0f) {
					// 速度と逆方向に入力中に急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAcceleration;
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}
			}
			// 加速/減速
			velocity_.x += acceleration.x;

			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

		} else {
			// 非入力時は移動減衰をかける
			velocity_.x *= (1.0f - kAttenuation);
			if (velocity_.x < 0.01f && velocity_.x > -0.01f) {
				velocity_.x = 0.0f;
			}
		}

		// 回転制御
		if (turnTimer_ > 0.0f) {
			turnTimer_ -= 1.0f;

			float destinationRotationYTable[] = {
			    0.0f,                     // 右
			    std::numbers::pi_v<float> // 左
			};
			// 状態に応じた角度を取得する
			float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
			// 自キャラの角度を設定する
			worldTransform_.rotation_.y = turnFirstRotationY_ * (turnTimer_ / kTimeTurn) + destinationRotationY * (1 - turnTimer_ / kTimeTurn);
		}

		// ジャンプ
		if (Input::GetInstance()->PushKey(DIK_UP)) {
			// ジャンプ初速を加える
			velocity_.y += kJumpAcceleration;
		}

		// ジャンプ開始
		if (velocity_.y > 0.0f) {
			// 空中状態に移行
			onGround_ = false;
		}


	} else {
		// 落下速度
		velocity_.y -= kGravityAcceleration;
		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
		// 空中
		if (velocity_.y < 0) {
			if ((worldTransform_.translation_.y + velocity_.y) <= 2.0f) {
				landing = true;
			}
		}
		// 着地判定
		if (landing) {
			// めり込み排斥
			worldTransform_.translation_.y = 2.0f;
			// 下方向速度をリセット
			velocity_.y = 0.0f;
			// 接地状態に移行
			onGround_ = true;
		}

	}

	// 実際移動計算
	worldTransform_.translation_ = {
	    worldTransform_.translation_.x + velocity_.x,
	    worldTransform_.translation_.y + velocity_.y,
	    worldTransform_.translation_.z + velocity_.z,
	};

	{
		// アフィン変換
		Matrix4x4 mS = MakeScaleMatrixM(worldTransform_.scale_);
		Matrix4x4 mR = MakeRotateMatrixM(MakeRotateXMatrixM(worldTransform_.rotation_.x), MakeRotateYMatrixM(worldTransform_.rotation_.y), MakeRotateZMatrixM(worldTransform_.rotation_.z));

		Matrix4x4 mT = MakeTranslateMatrixM(worldTransform_.translation_);

		worldTransform_.matWorld_ = MultM(mS, MultM(mR, mT));
	}

	// ワールドトランスフォームの更新
	worldTransform_.TransferMatrix();

	/// ImGuiのデバッグウィンドウ
	ImGui::Begin("Debug");
	ImGui::SliderFloat2("worldTransform_,translation_", &worldTransform_.translation_.x, 1, 50);
	ImGui::SliderFloat2("worldTransform_,rotation_", &worldTransform_.rotation_.x, 0, 10);
	ImGui::End();
}

void Player::Render() {
	// assert(camera_ != nullptr);
	// assert(model_ != nullptr);
	// assert(textureHandle_ != 0u);
	/// モデルの描画
	// model_->Draw(worldTransform_, *camera_, textureHandle_);
	modelPlayer_->Draw(worldTransform_, *camera_);
}
