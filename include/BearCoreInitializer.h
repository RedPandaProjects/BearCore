#pragma once
namespace BearCore
{
	BEARTOOL_API void Initialize(const bchar*app_name, const bchar*log_path, const bchar*email/*for debug help*/);
	BEARTOOL_API void Destroy();
}