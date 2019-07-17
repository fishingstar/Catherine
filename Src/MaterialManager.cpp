#include "MaterialManager.h"

namespace Catherine
{
	MaterialManager * MaterialManager::Instance()
	{
		static MaterialManager s_instance;
		return &s_instance;
	}


}