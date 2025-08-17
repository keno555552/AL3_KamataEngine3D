#include "GameScene.h"
#include "KamataEngine.h"
#include <Windows.h>
using namespace KamataEngine;
#include "TitleScene.h"
#include "sceneChanger.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
#pragma region System初期化
	/// KamataEngineの初期化
	Initialize(L"LE2B_06_カン_ケンリャン_AL3");
	/// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	/// DirectXの初期化
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//Scene scene = Scene::kTitle;
	Scene scene = Scene::kGame;

	/// TitleSceneの生成まだわ初期化
	TitleScene* titleScene = nullptr;
	//TitleScene* titleScene = new TitleScene;
	//titleScene->Initialize();

	/// GameSceneの生成,そして待機
	//GameScene* gameScene = nullptr;
	GameScene* gameScene = new GameScene;
	gameScene->Initialize();

#pragma endregion

#pragma region Mainループ
	while (true) {

#pragma region ゲーム処理

		/// ImGui受付開始
		imguiManager->Begin();

		if (Update()) {
			break;
		}

		ChangeScene(scene, &titleScene, &gameScene);
		UpdateScene(scene, &titleScene, &gameScene);

		/// ImGui受付終了
		imguiManager->End();
#pragma endregion

#pragma region 描画処理

		dxCommon->PreDraw();

		DrawScene(scene, &titleScene, &gameScene);

		/// ImGui描画
		imguiManager->Draw();

		/// 軸表示の描画
		AxisIndicator::GetInstance()->Draw();

		dxCommon->PostDraw();
#pragma endregion

		if (Input::GetInstance()->TriggerKey(DIK_ESCAPE)) {
			break;
		}
	}
#pragma endregion

#pragma region 後処理

	if (titleScene) {
		delete titleScene, titleScene = nullptr;
	}
	if (gameScene) {
		delete gameScene, gameScene = nullptr;
	}

#pragma endregion

	Finalize();
	return 0;
}
