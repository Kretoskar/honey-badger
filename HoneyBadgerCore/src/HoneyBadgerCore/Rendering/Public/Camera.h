#pragma once

#include "HoneyBadgerCore/Core/Public/EventSystem.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Math/Public/Mat4.h"

namespace HoneyBadger
{
	class Window;
	class Shader;

	class Camera
	{
		Vec3 _position;
		Vec3 _orientation = Vec3(-0.5f, -0.5f, -0.5f);
		Vec3 _up = Vec3(0.0f, 1.0f, 0.0f);

		Mat4 _view;
		Mat4 _projection;

		int _width = 1920;
		int _height = 1080;

		float _speed = 0.15f;
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
		void Init();
		void Update();

		Vec3 GetRightVector() const;

		void OnRightMouseButtonClick(void* event);
		void OnRightMouseButtonRelease(void* event);

		void OnForwardPressed(void* payload);
		void OnForwardReleased(void* payload);

		void OnBackwardPressed(void* payload);
		void OnBackwardReleased(void* payload);

		void OnRightPressed(void* payload);
		void OnRightReleased(void* payload);

		void OnLeftPressed(void* payload);
		void OnLeftReleased(void* payload);

		void OnMouseMoved(void* payload);

		Mat4 GetVPMatrix() const { return _projection * _view; }

		Vec3 GetPosition() const { return _position; }
	};
}