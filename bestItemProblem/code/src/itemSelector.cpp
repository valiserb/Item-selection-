#include "itemSelector.h"
#include <algorithm>
#include <iterator>
#include <set>

ItemSelector::ItemSelector(const std::vector<dataTypes::MasterData>& masterDataList, const std::vector<dataTypes::Item>& itemList) {
	BuildDataStructures(masterDataList, itemList);
}

int ItemSelector::GetBestItem(const std::vector<dataTypes::Brick>& bricks) const
{
	std::vector<int> itemsContainingBricks = GetAllItemsContainingBricks(bricks);
	if (itemsContainingBricks.empty()) {
		return -1;
	}

	std::set<dataTypes::MasterData> validMasterDataSet;

	for (int itemId : itemsContainingBricks) {
		auto it = m_masterDataMap.find(itemId);	
		if (it != m_masterDataMap.end()) {
			validMasterDataSet.insert(it->second);
		}
	}
	if (validMasterDataSet.empty()) {
		return -1;
	}

	return validMasterDataSet.begin()->itemId;
}

void ItemSelector::BuildDataStructures(const std::vector<dataTypes::MasterData>& masterDataList, const std::vector<dataTypes::Item>& itemList) {
	for (const auto& md : masterDataList) {
		if (md.status != dataTypes::Status::Discontinued) {
			m_masterDataMap[md.itemId] = md;
		}
	}

	for (const auto& item : itemList) {
		for (const auto& brick : item.bricks) {
			m_brickToItemIdsMap[brick].push_back(item.id);
		}
	}
}

std::vector<int> ItemSelector::GetAllItemsContainingBricks(const std::vector<dataTypes::Brick>& bricks) const {
	if (bricks.empty()) {
		return std::vector<int>();
	}

	auto it = m_brickToItemIdsMap.find(bricks[0]);
	if (it == m_brickToItemIdsMap.end()) {	   
	    return std::vector<int>();
	}

	std::vector<int> relevantItems = it->second;

	for (size_t idx = 1; idx < bricks.size(); idx++) {
		it = m_brickToItemIdsMap.find(bricks[idx]);
		if (it == m_brickToItemIdsMap.end()) {
			return std::vector<int>();
		}
		std::vector<int> intersection;
		std::set_intersection(relevantItems.begin(), relevantItems.end(),
			it->second.begin(), it->second.end(),
			std::inserter(intersection, intersection.begin()));
		relevantItems = std::move(intersection);
		if (relevantItems.empty()) {
			return std::vector<int>();
		}
	}

	return relevantItems;
}
