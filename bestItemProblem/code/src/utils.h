#include "dataTypes.h"

class BrickHashFunction {
public:
	size_t operator()(dataTypes::Brick const& brick) const {
		size_t hash = std::hash<int>()(brick.shapeId);
		for (int idx = 0; idx<brick.colorCodes.size(); idx++) {
			hash += std::hash<int>()(brick.colorCodes[idx]*idx);
		}
		return hash;
	}
};