#include "hbpch.h"
#include "HoneyBadgerCore/Rendering/Public/Camera.h"

#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "HoneyBadgerCore/Window/Public/Window.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Math/Public/MathCore.h"

namespace HoneyBadger
{
    Vec3 Camera::GetVelocity() const
    {
        Vec3 retVelocity = Vec3(0.0f, 0.0f, 0.0f);

		if (!_canMove)
		{
			return { 0.0f, 0.0f, 0.0f };
		}

		if (_movingForward)
		{
			retVelocity += _orientation * _speed;
		}
		if (_movingBackward)
		{
			retVelocity -= _orientation * _speed;
		}
		if (_movingRight)
		{
			retVelocity += GetRightVector() * _speed;
		}
		if (_movingLeft)
		{
			retVelocity -= GetRightVector() * _speed;
		}

		return retVelocity;
    }

    void Camera::Init()
    {
        _width = 1920; // TODO: window get viewport size
        _height = 1080;

		HB_BIND_EVENT(MouseButtonEvent::Type(GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, 0), OnRightMouseButtonClick)
        HB_BIND_EVENT(MouseButtonEvent::Type(GLFW_MOUSE_BUTTON_RIGHT, GLFW_RELEASE, 0), OnRightMouseButtonRelease)

		HB_BIND_EVENT(MousePositionEvent::Type(), OnMouseMoved)
        
		HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_W, GLFW_PRESS, 0), OnForwardPressed)
		HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_W, GLFW_RELEASE, 0), OnForwardReleased)
        
		HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_S, GLFW_PRESS, 0), OnBackwardPressed)
		HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_S, GLFW_RELEASE, 0), OnBackwardReleased)
        
		HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_D, GLFW_PRESS, 0), OnRightPressed)
		HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_D, GLFW_RELEASE, 0), OnRightReleased)
        
		HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_A, GLFW_PRESS, 0), OnLeftPressed)
		HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_A, GLFW_RELEASE, 0), OnLeftReleased)
    }

    void Camera::Update()
    {
		_position += GetVelocity();

		_view = Mat4::LookAt(_position, _position + _orientation, _up);
		_projection = Mat4::Perspective(MathCore::DegToRad(_FOVdeg), static_cast<float>(_width) / static_cast<float>(_height), _nearPlane, _farPlane);
    }

    Vec3 Camera::GetRightVector() const
    {
        return Vec3::Cross(_orientation, _up).Normalized();
    }

    void Camera::OnRightMouseButtonClick(void* event)
    {
		_canMove = true;
		_canLook = true;
		glfwSetCursorPos(_window->GetGlfwWindow(), (_width / 2), (_height / 2));
		glfwSetInputMode(_window->GetGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void Camera::OnRightMouseButtonRelease(void* event)
    {
		_canMove = false;
		_canLook = false;
		glfwSetInputMode(_window->GetGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void Camera::OnForwardPressed(void* payload)
    {
        _movingForward = true;
    }

    void Camera::OnForwardReleased(void* payload)
    {
        _movingForward = false;
    }

    void Camera::OnBackwardPressed(void* payload)
    {
        _movingBackward = true;
    }

    void Camera::OnBackwardReleased(void* payload)
    {
        _movingBackward = false;
    }

    void Camera::OnRightPressed(void* payload)
    {
        _movingRight = true;
    }

    void Camera::OnRightReleased(void* payload)
    {
        _movingRight = false;
    }

    void Camera::OnLeftPressed(void* payload)
    {
        _movingLeft = true;
    }

    void Camera::OnLeftReleased(void* payload)
    {
        _movingLeft = false;
    }

    void Camera::OnMouseMoved(void* payload)
    {
		const int32_t posX = *static_cast<int32_t*>(payload);
		const int32_t posY = *reinterpret_cast<int32_t*>(static_cast<char*>(payload) + sizeof(int32_t));

		if (!_canLook) return;

		const float rotX = _sensitivity * static_cast<float>(posY - (_height / 2)) / _height;
		const float rotY = _sensitivity * static_cast<float>(posX - (_width / 2)) / _width;

		//const Vec3 newOrientation = glm::rotate(_orientation, glm::radians(-rotX), glm::normalize(glm::cross(_orientation, _up)));
		//
		//// Decides whether or not the next vertical Orientation is legal or not
		//if (abs(glm::angle(newOrientation, _up) - glm::radians(90.0f)) <= glm::radians(85.0f)
		//	&& abs(glm::angle(newOrientation, -_up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		//{
		//	_orientation = newOrientation;
		//}
		//
		//// Rotates the Orientation left and right
		//_orientation = glm::rotate(_orientation, glm::radians(-rotY), _up);
		//
		//glfwSetCursorPos(_window->GetGlfwWindow(), (_width / 2), (_height / 2));
    }
}