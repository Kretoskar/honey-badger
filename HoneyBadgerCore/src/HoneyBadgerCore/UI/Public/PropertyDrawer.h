#pragma once

#include "HoneyBadgerCore/Math/Public/Quat.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include <string>

namespace HoneyBadger
{
	void DrawEditorComponentName(const char* name);
	void DrawEditorProperty(const char* name, const std::string& value);
	void DrawEditorProperty(const char* name, int32_t value);

	void DrawEditorPropertyEditable(const char* name, std::string& value);
	void DrawEditorPropertyEditable(const char* name, Vec3& value);
	void DrawEditorPropertyEditable(const char* name, Quat& value);
}