#pragma once
#include <vector>

namespace dataTypes
{
	struct Brick {
		int shapeId;
		std::vector<int> colorCodes;

		bool operator==(const Brick& other) const {
			return shapeId == other.shapeId && colorCodes == other.colorCodes;
		}
	};

	struct Item {
		int id;
		std::vector<Brick> bricks;
	};

	enum class Status {
		Discontinued = 0,
		Outgoing = 1,
		Normal = 2,
		Novelty = 3		
	};

	inline bool operator<(const Status& lhs, const Status& rhs) {
		return static_cast<int>(lhs) < static_cast<int>(rhs);
	}

	struct MasterData {
		int itemId;
		int price;
		Status status;

		bool operator<(const MasterData& other) const {
			if (status != other.status) {
				return status > other.status;
			}
			return price < other.price;
		}
	};
}
