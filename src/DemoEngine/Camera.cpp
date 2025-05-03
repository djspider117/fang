#include "pch.h"
#include "Camera.h"

namespace Fang::Rendering
{
	DirectX::XMMATRIX Camera::GetTransform() const noexcept
	{
		return DirectX::XMMatrixRotationRollPitchYaw(Pitch, Yaw, Roll) *
			DirectX::XMMatrixTranslation(X, Y, Z) *
			DirectX::XMMatrixPerspectiveFovLH(FieldOfView, AspectRatio, NearZ, FarZ);
	}
}