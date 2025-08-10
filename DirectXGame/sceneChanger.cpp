#include "sceneChanger.h"

void ChangeScene(Scene& scene,TitleScene** titleScene,GameScene** gameScene){
	switch (scene) {
	case Scene::kTitle:
		if (*titleScene)if ((*titleScene)->IsFinished()) {
			scene = Scene::kGame;
			delete (*titleScene), (*titleScene) = nullptr;
			(*gameScene) = new GameScene, (*gameScene)->Initialize();
		}
		break;
	case Scene::kGame:
		if (*gameScene)if ((*gameScene)->IsFinished()) {
			scene = Scene::kTitle;
			delete (*gameScene), (*gameScene) = nullptr;
			(*titleScene) = new TitleScene, (*titleScene)->Initialize();
		}
		break;
	}
}

void UpdateScene(Scene& scene, TitleScene** titleScene, GameScene** gameScene){
	switch (scene) {
	case Scene::kTitle:
		if (*titleScene)(*titleScene)->Update();
		break;
	case Scene::kGame:
		if (*gameScene)(*gameScene)->Update();
		break;
	}
}

void DrawScene(Scene& scene, TitleScene** titleScene, GameScene** gameScene){
	switch (scene) {
	case Scene::kTitle:
		if (*titleScene)(*titleScene)->Draw();
		break;
	case Scene::kGame:
		if (*gameScene)(*gameScene)->Render();
		break;
	}
}
