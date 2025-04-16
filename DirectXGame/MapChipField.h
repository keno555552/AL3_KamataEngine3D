#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include <vector>

enum class MapChipType {
	kBlank, // 空白
	kBlock, // ブロック
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField {
public:

	/// リセット
	void ResetMapChipData();
	
	/// 読み込み
	void LoadMapChipCsv(const std::string& filePath);

	/// マップチップ種類を取得
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	/// マップチップ座標を取得
	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	uint32_t GetNumBlockVirtical()	{ return kNumBlockVirtical; }
	uint32_t GetNumBlockHorizontal()	{ return kNumBlockHorizontal; }

private:
	// 1ブロックのサイズ
	static inline const float kBlockWidth = 2.0f;
	static inline const float kBlockHeight = 2.0f;
	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;
};

//void GenerateBlocks(std::vector<std::vector<WorldTransform*>>& worldTransformBlocks);