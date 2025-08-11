#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "MapChipField.h"
#include "crashDecision.h"
#include "myMathForAL.h"

class TitleWord {
public:
	/// ~TitleWord();
	/// 初期化
	void Initialize(const Camera* camera, const Vector3& position);
	/// 更新
	void Update();
	/// 描画
	void Render();

private:

	int textureHandle_ = TextureManager::Load("title/title.png");

	///スブライド
	Sprite* sprite_ = nullptr;

	///// 単独モデル
	//Model* model1_ = nullptr;
	//Model* model2_ = nullptr;
	/// ワールドトランスフォーム
	WorldTransform worldTransform_;
	/// カメラ
	const Camera* camera_ = nullptr;

};
