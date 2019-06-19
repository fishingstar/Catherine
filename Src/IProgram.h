#pragma once

namespace Catherine
{
	class IProgram
	{
	public:
		// TODO : support other shader types
		virtual void AttachShader(const char * vertex, const char * fragment) = 0;
		virtual bool Compile() = 0;
		virtual bool Link() = 0;
		virtual void Use() = 0;
	};
}
