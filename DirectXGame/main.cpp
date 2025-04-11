#include "GameScene.h"
#include "KamataEngine.h"
#include <Windows.h>
using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
#pragma region System初期化
	/// KamataEngineの初期化
	Initialize(L"LE2B_06_カン_ケンリャン_AL3");
	/// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	/// DirectXの初期化
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	/// GameSceneの生成まだわ初期化
	GameScene* gameScene = new GameScene();
	gameScene->Initialize();

#pragma endregion

	while (true) {

#pragma region ゲーム処理
		/// ImGui受付開始
		imguiManager->Begin();

		if (Update()) {
			break;
		}
		/// ゲームシーンの更新
		gameScene->Update();

		/// ImGui受付終了
		imguiManager->End();
#pragma endregion

#pragma region 描画処理
		dxCommon->PreDraw();

		/// ゲームシーンの描画
		gameScene->Draw();

		/// ImGui描画
		imguiManager->Draw();

		dxCommon->PostDraw();
#pragma endregion

		if (Input::GetInstance()->TriggerKey(DIK_ESCAPE)) {
			break;
		}
	}

#pragma region 後処理

	/// GameSceneの後処理
	delete gameScene;
	gameScene = nullptr;

#pragma endregion

	Finalize();
	return 0;
}
