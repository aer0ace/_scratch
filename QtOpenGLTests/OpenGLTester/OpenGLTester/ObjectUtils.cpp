#include "ObjectUtils.h"

namespace Utils
{
	//ObjectUtils::ObjectUtils()
	//{
	//
	//}
	//
	//ObjectUtils::~ObjectUtils()
	//{
	//
	//}

	float clamp(float n, float lower, float upper)
	{
		return std::max(lower, std::min(n, upper));
	}


}
