#include "catch2/catch.hpp"
#include "itemSelector.h"
#include "dataTypes.h"

TEST_CASE("Item selector complete test")
{
	std::vector<dataTypes::MasterData> masterDataList{
		dataTypes::MasterData{1001, 21, dataTypes::Status::Normal},
		dataTypes::MasterData{1002, 19, dataTypes::Status::Novelty},
		dataTypes::MasterData{1003, 25, dataTypes::Status::Outgoing},
		dataTypes::MasterData{1004, 14, dataTypes::Status::Discontinued},
		dataTypes::MasterData{1005, 21, dataTypes::Status::Normal},
		dataTypes::MasterData{1006, 15, dataTypes::Status::Novelty},
		dataTypes::MasterData{1007, 18, dataTypes::Status::Discontinued},
		dataTypes::MasterData{1008, 25, dataTypes::Status::Outgoing},
		dataTypes::MasterData{1009, 21, dataTypes::Status::Normal},
		dataTypes::MasterData{1010, 21, dataTypes::Status::Novelty},
		dataTypes::MasterData{1011, 21, dataTypes::Status::Discontinued},
		dataTypes::MasterData{1012, 21, dataTypes::Status::Outgoing},
		dataTypes::MasterData{1013, 21, dataTypes::Status::Normal},
		dataTypes::MasterData{1014, 22, dataTypes::Status::Normal},
		dataTypes::MasterData{1015, 23, dataTypes::Status::Normal},
		dataTypes::MasterData{1016, 24, dataTypes::Status::Normal},
		dataTypes::MasterData{1017, 21, dataTypes::Status::Discontinued} };

	std::vector<dataTypes::Item> itemList{
		dataTypes::Item{1001, {
				dataTypes::Brick{101, {21, 34, 56}},
				dataTypes::Brick{102, {1, 3}},
				dataTypes::Brick{103, {11, 5, 42, 67}},
				dataTypes::Brick{104, {23}}}},
		dataTypes::Item{1002, {
				dataTypes::Brick{101, {21, 34, 56}},
				dataTypes::Brick{102, {1, 3}},
				dataTypes::Brick{103, {11, 5, 42, 67}},
				dataTypes::Brick{104, {23}}}},
		dataTypes::Item{1003, {
				dataTypes::Brick{101, {21, 34, 56}},
				dataTypes::Brick{102, {1, 3}},
				dataTypes::Brick{103, {11, 5, 42, 67}},
				dataTypes::Brick{104, {23}}}},
		dataTypes::Item{1004, {
				dataTypes::Brick{105, {1, 81}},
				dataTypes::Brick{106, {12, 52, 42, 67}}}},
		dataTypes::Item{1005, {
				dataTypes::Brick{105, {1, 81}},
				dataTypes::Brick{106, {12, 52, 42, 67}}}},
		dataTypes::Item{1006, {
				dataTypes::Brick{105, {1, 81}},
				dataTypes::Brick{106, {12, 52, 42, 67}}}},
		dataTypes::Item{1007, {
				dataTypes::Brick{105, {1, 81}},
				dataTypes::Brick{106, {12, 52, 42, 67}}}},
		dataTypes::Item{1008, {
				dataTypes::Brick{105, {1, 81}},
				dataTypes::Brick{106, {12, 52, 42, 67}}}},
		dataTypes::Item{1009, {
				dataTypes::Brick{107, {1, 33}},
				dataTypes::Brick{108, {67}},
				dataTypes::Brick{109, {11, 78, 42, 67}}}},
		dataTypes::Item{1010, {
				dataTypes::Brick{107, {1, 33}},
				dataTypes::Brick{108, {67}},
				dataTypes::Brick{109, {11, 78, 42, 67}}}},
		dataTypes::Item{1011, {
				dataTypes::Brick{107, {1, 33}},
				dataTypes::Brick{108, {67}},
				dataTypes::Brick{109, {11, 78, 42, 67}}}},
		dataTypes::Item{1012, {
				dataTypes::Brick{107, {1, 33}},
				dataTypes::Brick{108, {67}},
				dataTypes::Brick{109, {11, 78, 42, 67}}}},
		dataTypes::Item{1013, {
				dataTypes::Brick{101, {34, 56, 21}},
				dataTypes::Brick{102, {1, 3}},
				dataTypes::Brick{104, {23}},
				dataTypes::Brick{107, {1, 33}},
				dataTypes::Brick{108, {67}}}},
		dataTypes::Item{1014, {
				dataTypes::Brick{101, {34, 56, 21}},
				dataTypes::Brick{102, {1, 3}},
				dataTypes::Brick{104, {23}},
				dataTypes::Brick{107, {1, 33}},
				dataTypes::Brick{108, {67}}}},
		dataTypes::Item{1015, {
				dataTypes::Brick{101, {34, 56, 21}},
				dataTypes::Brick{102, {1, 3}},
				dataTypes::Brick{104, {23}},
				dataTypes::Brick{107, {1, 33}},
				dataTypes::Brick{108, {67}}}},
		dataTypes::Item{1016, {
				dataTypes::Brick{101, {34, 56, 21}},
				dataTypes::Brick{102, {1, 3}},
				dataTypes::Brick{104, {23}},
				dataTypes::Brick{107, {1, 33}},
				dataTypes::Brick{108, {67}}}},
		dataTypes::Item{1017, {
				dataTypes::Brick{101, {21, 34, 56}},
				dataTypes::Brick{103, {11, 5, 42, 67}},
				dataTypes::Brick{108, {67}}}},
	};

	ItemSelector itemSelector{ masterDataList, itemList };

	SECTION("Existing brick returns valid item") {
		REQUIRE(itemSelector.GetBestItem({ dataTypes::Brick{102, {1, 3}} }) == 1002);
	}

	SECTION("Multiple bricks returns valid item") {
		REQUIRE(itemSelector.GetBestItem({ dataTypes::Brick{102, {1, 3}}, dataTypes::Brick{104, {23}} }) == 1002);
	}

	SECTION("No bricks returns nothing") {
		REQUIRE(itemSelector.GetBestItem({}) == -1);
	}

	SECTION("Unknown brick returns nothing") {
		REQUIRE(itemSelector.GetBestItem({ dataTypes::Brick{999, {22}} }) == -1);
	}

	SECTION("Multiple bricks with no common item return nothing") {
		REQUIRE(itemSelector.GetBestItem({ dataTypes::Brick{102, {1, 3}}, dataTypes::Brick{105, {1, 81}} }) == -1);
	}

	SECTION("Discontinued items are ignored") {
		// Item 1017 is discontinued and contains bricks 101, 103, 108
		REQUIRE(itemSelector.GetBestItem({
				dataTypes::Brick{101, {21, 34, 56}},
				dataTypes::Brick{103, {11, 5, 42, 67}},
				dataTypes::Brick{108, {67}}}) == -1);
	}

	SECTION("Best item is chosen based on status when price is the same") {
		// Items 1009, 1010, 1011 and 1012 have the same price but different statuses
		REQUIRE(itemSelector.GetBestItem({
				dataTypes::Brick{107, {1, 33}},
				dataTypes::Brick{108, {67}},
				dataTypes::Brick{109, {11, 78, 42, 67}}}) == 1010);
	}

	SECTION("Best item is chosen based on price when status is the same") {
		// Items 1013, 1014, 1015, 1016 have the same status but different prices
		REQUIRE(itemSelector.GetBestItem({
				dataTypes::Brick{102, {1, 3}},
				dataTypes::Brick{104, {23}},
				dataTypes::Brick{107, {1, 33}},
				dataTypes::Brick{108, {67}}}) == 1013);
	}

	SECTION("Color order is taken into consideration") {
		REQUIRE(itemSelector.GetBestItem({ dataTypes::Brick{101, {21, 34, 56} }, dataTypes::Brick{102, {1, 3} } }) == 1002);
		REQUIRE(itemSelector.GetBestItem({ dataTypes::Brick{101, {34, 56, 21} }, dataTypes::Brick{102, {1, 3} } }) == 1013);
	}
}

