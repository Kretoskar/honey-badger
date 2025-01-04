#pragma once

#include "HoneyBadgerCore/Window/Public/Window.h"
#include "HoneyBadgerCore/Core/Public/EventSystem.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Math/Public/Mat4.h"

namespace HoneyBadger
{
	class Shader;

	class Camera
	{
	protected:
		Vec3 _position;
		Vec3 _orientation = Vec3(-0.5f, -0.5f, -0.5f);
		Vec3 _up = Vec3(0.0f, 1.0f, 0.0f);

		Mat4 _view;
		Mat4 _projection;

		int _width = 1920;
		int _height = 1080;

		float _speed = 0.005f;
		float _sensitivity = 100.0f;

		float _FOVdeg = 75;
		float _nearPlane = 0.01f;
		float _farPlane = 1000;

		Window* _window;
		bool _canMove = false;
		bool _canLook = false;

		bool _movingForward = false;
		bool _movingBackward = false;
		bool _movingLeft = false;
		bool _movingRight = false;

		Vec3 GetVelocity() const;

	public:
		Camera(Window* inWindow, Vec3 position)
			: _window(inWindow), _position(position) {}
		virtual void Init();
		virtual void Update();

		Vec3 GetRightVector() const;

		virtual void OnRightMouseButtonClick(void* event);
		virtual void OnRightMouseButtonRelease(void* event);
		
		virtual void OnForwardPressed(void* payload);
		virtual void OnForwardReleased(void* payload);
		
		virtual void OnBackwardPressed(void* payload);
		virtual void OnBackwardReleased(void* payload);
		
		virtual void OnRightPressed(void* payload);
		virtual void OnRightReleased(void* payload);
		
		virtual void OnLeftPressed(void* payload);
		virtual void OnLeftReleased(void* payload);
		
		virtual void OnMouseMoved(void* payload);

		Mat4 GetVPMatrix() const { return _projection * _view; }
		Mat4 GetProjectionMatrix() const { return _projection; }
		Mat4 GetViewMatrix() const { return _view; }

		Vec3 GetPosition() const { return _position; }
	};
}