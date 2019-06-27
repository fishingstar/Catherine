#pragma once

namespace Catherine
{
	class IModel
	{
	public:
		virtual void LoadFromFile(const char * path) = 0;
		virtual void Render() = 0;
	};
}