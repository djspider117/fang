#pragma once
#include "pch.h"

namespace Fang::Rendering
{
	public class Camera
	{
	public:
		Camera(float aspectRatio, float fov, float nearZ, float farZ) :
			AspectRatio(aspectRatio),
			FieldOfView(fov),
			NearZ(nearZ),
			FarZ(farZ),
			X(0), Y(0), Z(0),
			Yaw(0), Pitch(0), Roll(0)
		{

		}

		DirectX::XMMATRIX GetTransform() const noexcept;

	public:
		float X;
		float Y;
		float Z;
		float Yaw;
		float Pitch;
		float Roll;
		float AspectRatio;
		float FieldOfView;
		float NearZ;
		float FarZ;
	};

	public ref class CameraInterop
	{
	private:
		Camera* _camera;

	public:
		CameraInterop(Camera* camera)
			: _camera(camera)
		{

		}

		void SetPosition(float x, float y, float z)
		{
			_camera->X = x;
			_camera->Y = y;
			_camera->Z = z;
		}

		void SetRotations(float y, float p, float r)
		{
			_camera->Yaw = y;
			_camera->Pitch = p;
			_camera->Roll = r;
		}
	};
}

