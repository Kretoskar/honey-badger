#pragma once

#include "hbpch.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"

namespace HoneyBadger
{

	class Engine
	{
	public:
		// Call this before window is created
		bool Init();

		// Call this after window is created
		bool InitAfterWindow();

		static AssetsRegistry* AssetsReg;
	};
}