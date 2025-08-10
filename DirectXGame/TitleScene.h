#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "CameraController.h"
#include "Player.h"
#include "Skydome.h"
#include "TitleWord.h"

class TitleScene {
public:
	void Initialize();
	void Update();
	void Draw();

	/// 終了フラグのgetter
	bool IsFinished() const { return finished_; }

private:
	/// 終了フラグ
	bool finished_ = false;

private:
	/// スカイドーム
	Skydome* skydome_ = new Skydome;

	/// カメラ
	Camera camera_;

	/// Player
	Player* player_ = new Player;

	///
	TitleWord* titleWord_ = new TitleWord;
};
