#pragma once

#include <optional>
#include <unordered_map>
#include <vector>
#include "dataTypes.h"
#include "utils.h"

class ItemSelector {
public:
	ItemSelector(const std::vector<dataTypes::MasterData>& masterDataList, const std::vector<dataTypes::Item>& itemList);
	int GetBestItem(const std::vector<dataTypes::Brick>& bricks) const;

private:
	void BuildDataStructures(const std::vector<dataTypes::MasterData>& masterDataList, const std::vector<dataTypes::Item>& itemList);
	std::vector<int> GetAllItemsContainingBricks(const std::vector<dataTypes::Brick>& bricks) const;

	std::unordered_map<int, dataTypes::MasterData> m_masterDataMap;
	std::unordered_map<dataTypes::Brick, std::vector<int>, BrickHashFunction> m_brickToItemIdsMap;
};