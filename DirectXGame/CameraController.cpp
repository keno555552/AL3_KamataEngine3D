#include "CameraController.h"
#include <algorithm> // Add this include for std::min and std::max

void CameraController::Initialize() { camera_.Initialize(); }

void CameraController::Update() {
	/// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	/// 追従対象とオフセットと追従対象の速度からカメラの座標を計算
	targetPosition_.x = targetWorldTransform.translation_.x + targetOffset_.x + target_->GetVelocity().x * kVelocityBias;
	targetPosition_.y = targetWorldTransform.translation_.y + targetOffset_.y + target_->GetVelocity().y * kVelocityBias;
	targetPosition_.z = targetWorldTransform.translation_.z + targetOffset_.z + target_->GetVelocity().z * kVelocityBias;

	///　座標補間によりゆったり追従
	camera_.translation_ = Lerp(camera_.translation_, targetPosition_, (float)kInterpolationRate);

	/// 追従対象が画面外に出ないように補正
	camera_.translation_.x = 
		(((camera_.translation_.x) > (target_->GetWorldTransform().translation_.x + kCameraMoveRange.left)) ? 
		(camera_.translation_.x)   : (target_->GetWorldTransform().translation_.x + kCameraMoveRange.left));
	camera_.translation_.x = 
		(((camera_.translation_.x) < (target_->GetWorldTransform().translation_.x + kCameraMoveRange.right)) ?
		(camera_.translation_.x)   : (target_->GetWorldTransform().translation_.x + kCameraMoveRange.right));
	camera_.translation_.y =
		(((camera_.translation_.y) > (target_->GetWorldTransform().translation_.y + kCameraMoveRange.bottom)) ? 
		(camera_.translation_.y)   : (target_->GetWorldTransform().translation_.y + kCameraMoveRange.bottom));
	camera_.translation_.y = 
		(((camera_.translation_.y) < (target_->GetWorldTransform().translation_.y + kCameraMoveRange.top)) ? 
		(camera_.translation_.y)   : (target_->GetWorldTransform().translation_.y + kCameraMoveRange.top));

	/// 移動範囲制限
	camera_.translation_.x = std::clamp(camera_.translation_.x, movableArea_.left, movableArea_.right);
	camera_.translation_.y = std::clamp(camera_.translation_.y, movableArea_.bottom, movableArea_.top);

	/// 行列を更新する
	camera_.UpdateMatrix();
}

void CameraController::Reset() {
	/// 随従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	/// 随従対象のオフセットからカメラの座標を計算
	camera_.translation_.x = targetWorldTransform.translation_.x + targetOffset_.x;
	camera_.translation_.y = targetWorldTransform.translation_.y + targetOffset_.y;
	camera_.translation_.z = targetWorldTransform.translation_.z + targetOffset_.z;
};