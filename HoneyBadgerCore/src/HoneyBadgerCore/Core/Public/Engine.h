#pragma once

#include "hbpch.h"
#include <memory>
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

		static Engine* Instance;

		AssetsRegistry* GetAssetsRegistry() const
		{
			return AssetsReg.get();
		}

	private:
		std::unique_ptr<AssetsRegistry> AssetsReg;
	};
}