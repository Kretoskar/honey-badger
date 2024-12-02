#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "HoneyBadgerCore/UI/Public/PropertyDrawer.h"

#define Q(x) #x
#define QUOTE(x) Q(x)

#define RTTI_DECLARE() void DrawProperties();
#define RTTI_BEGIN(_TClass) void _TClass::DrawProperties() { \
        HoneyBadger::DrawEditorComponentName(#_TClass);
#define RTTI_PROPERTY(_name, _prop ) HoneyBadger::DrawEditorProperty(QUOTE(_name), this->_prop);
#define RTTI_PROPERTY_EDITABLE(_name, _prop ) HoneyBadger::DrawEditorPropertyEditable(QUOTE(_name), this->_prop);
#define RTTI_END() }