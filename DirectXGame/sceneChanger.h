#pragma once
#include "GameScene.h"
#include "KamataEngine.h"
#include <Windows.h>
using namespace KamataEngine;
#include "TitleScene.h"

/// GameScene(型)
enum class Scene {

	kUnkown = 0,

	kTitle,
	kGame,
};

void ChangeScene(Scene& scene, TitleScene** titleScene, GameScene** gameScene);

void UpdateScene(Scene& scene, TitleScene** titleScene, GameScene** gameScene);

void DrawScene(Scene& scene, TitleScene** titleScene, GameScene** gameScene);