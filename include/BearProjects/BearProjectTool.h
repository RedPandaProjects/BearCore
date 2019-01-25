#pragma once
#ifndef MAIN_PROJECT_NAME
#define MAIN_PROJECT_NAME ""
#endif
namespace BearCore
{
	class BEARTOOL_API BearProjectTool
	{
		BEAR_CLASS_STATIC(BearProjectTool);
	public:
		template<typename C> 
		static C GetFunctionInProject(const bchar*name,const bchar*function)
		{
			return reinterpret_cast<C>(GetFunctionInProjectImpl(name, function));
		}
		static bool CheckProject(const bchar*name);
		static void Destory();
		static void UnLoad(const bchar*name);
	private:
		static void * GetFunctionInProjectImpl(const bchar*name, const bchar*function);
	};
}