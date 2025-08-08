#include "Enemy.h"
#include <algorithm>
#include <numbers>


void Enemy::Initialize(const Camera* camera, const Vector3& position) {
	/// モデルの設定
	model_ = Model::CreateFromOBJ("enemy", true);

	/// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	/// カメラの設定
	camera_ = camera;

	/// ワールドトランスフォームの初期化
	// 初期回転
	worldTransform_.rotation_.y = -std::numbers::pi_v<float>;

	/// 速度を設定する
	velocity_ = {-kWalkSpeed, 0, 0};

	///// アニメーション
	walkTimer_ = 0.0f;
}

void Enemy::Update() {

	/// 移動
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;

	/// タイマーを加算
	walkTimer_ += 1.0f / 60.0f;

	/// 回転アニメーション
	float param = std::sin(2.0f * 3.14f * walkTimer_ / (kWSalkMotionTime));
	float degree = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f;
	worldTransform_.rotation_.z = degree * (3.14f / 180.0f);
		

	{
		// アフィン変換
		Matrix4x4 mS = MakeScaleMatrixM(worldTransform_.scale_);
		Matrix4x4 mR = MakeRotateMatrixM(MakeRotateXMatrixM(worldTransform_.rotation_.x), MakeRotateYMatrixM(worldTransform_.rotation_.y), MakeRotateZMatrixM(worldTransform_.rotation_.z));

		Matrix4x4 mT = MakeTranslateMatrixM(worldTransform_.translation_);

		worldTransform_.matWorld_ = MultM(mS, MultM(mR, mT));
	}

	// ワールドトランスフォームの更新
	worldTransform_.TransferMatrix();

	///// ImGuiのデバッグウィンドウ
	//ImGui::Begin("Debug2");
	//// ImGui::Checkbox("DebugCamera", &useDebugCamera);
	//ImGui::SliderFloat("param", &param, 0,100);
	//ImGui::End();
}


void Enemy::Render() {
	/// モデルの描画
	model_->Draw(worldTransform_, *camera_);
}

void Enemy::OnCollision(const Player* player) { (void)player; }

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
};

AABB Enemy::GetAABB() {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kEnemyWidth / 2.0f, worldPos.y - kEnemyHeight / 2.0f, worldPos.z - kEnemyWidth / 2.0f};
	aabb.max = {worldPos.x + kEnemyWidth / 2.0f, worldPos.y + kEnemyHeight / 2.0f, worldPos.z + kEnemyWidth / 2.0f};

	return aabb;
}