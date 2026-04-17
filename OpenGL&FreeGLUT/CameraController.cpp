#include "CameraController.h"
#include <gl/GLU.h> // gluLookAt

static float DegToRad(float d) { return d * 3.1415926535f / 180.0f; }

CameraController::CameraController()
{
    _cam.eye = { 0.0f, 0.0f, 15.0f };
    _cam.center = { 0.0f, 0.0f, 0.0f };
    _cam.up = { 0.0f, 1.0f, 0.0f };

    _yaw = -90.0f;     // looking toward -Z
    _pitch = 0.0f;

    _moveSpeed = 0.3f;
    _mouseSensitivity = 0.15f;

    _followEnabled = false;
    _followTargetPos = nullptr;
    _followOffset = { 0.0f, 3.0f, 12.0f };

    UpdateCenterFromYawPitch();
}

void CameraController::SetPosition(const Vector3& pos)
{
    _cam.eye = pos;
    UpdateCenterFromYawPitch();
}

void CameraController::SetLookAt(const Vector3& target)
{
    _cam.center = target;
}

void CameraController::SetMoveSpeed(float s) { _moveSpeed = s; }
void CameraController::SetMouseSensitivity(float s) { _mouseSensitivity = s; }

void CameraController::ApplyView() const
{
    gluLookAt(_cam.eye.x, _cam.eye.y, _cam.eye.z,
        _cam.center.x, _cam.center.y, _cam.center.z,
        _cam.up.x, _cam.up.y, _cam.up.z);
}

void CameraController::ProcessMouseDelta(int dx, int dy)
{
    if (_followEnabled) return; // optional: ignore mouse-look while following

    _yaw += dx * _mouseSensitivity;
    _pitch -= dy * _mouseSensitivity;

    // clamp pitch to avoid flipping
    if (_pitch > 89.0f) _pitch = 89.0f;
    if (_pitch < -89.0f) _pitch = -89.0f;

    UpdateCenterFromYawPitch();
}

void CameraController::MoveForward(float amount)
{
    if (_followEnabled) return;

    Vector3 forward = Normalize(Sub(_cam.center, _cam.eye));
    _cam.eye = Add(_cam.eye, Mul(forward, amount));
    _cam.center = Add(_cam.center, Mul(forward, amount));
}

void CameraController::StrafeRight(float amount)
{
    if (_followEnabled) return;

    Vector3 forward = Normalize(Sub(_cam.center, _cam.eye));
    Vector3 right = Normalize(Cross(forward, _cam.up));
    _cam.eye = Add(_cam.eye, Mul(right, amount));
    _cam.center = Add(_cam.center, Mul(right, amount));
}

void CameraController::MoveUp(float amount)
{
    if (_followEnabled) return;

    _cam.eye.y += amount;
    _cam.center.y += amount;
}

void CameraController::EnableFollow(bool enabled)
{
    _followEnabled = enabled;
}

bool CameraController::IsFollowEnabled() const
{
    return _followEnabled;
}

void CameraController::SetFollowTarget(Vector3* targetPos)
{
    _followTargetPos = targetPos;
}

void CameraController::SetFollowOffset(const Vector3& offset)
{
    _followOffset = offset;
}

void CameraController::UpdateFollow()
{
    if (!_followEnabled || _followTargetPos == nullptr) return;

    // camera eye = target + offset, camera looks at target
    _cam.eye = Add(*_followTargetPos, _followOffset);
    _cam.center = *_followTargetPos;
    _cam.up = { 0.0f, 1.0f, 0.0f };
}

Vector3 CameraController::Normalize(const Vector3& v)
{
    float len = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (len < 1e-6f) return { 0,0,0 };
    return { v.x / len, v.y / len, v.z / len };
}

Vector3 CameraController::Cross(const Vector3& a, const Vector3& b)
{
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

Vector3 CameraController::Add(const Vector3& a, const Vector3& b)
{
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}

Vector3 CameraController::Sub(const Vector3& a, const Vector3& b)
{
    return { a.x - b.x, a.y - b.y, a.z - b.z };
}

Vector3 CameraController::Mul(const Vector3& v, float s)
{
    return { v.x * s, v.y * s, v.z * s };
}

void CameraController::UpdateCenterFromYawPitch()
{
    // Compute forward vector from yaw/pitch
    float yawR = DegToRad(_yaw);
    float pitchR = DegToRad(_pitch);

    Vector3 forward;
    forward.x = std::cos(yawR) * std::cos(pitchR);
    forward.y = std::sin(pitchR);
    forward.z = std::sin(yawR) * std::cos(pitchR);
    forward = Normalize(forward);

    _cam.center = Add(_cam.eye, forward);
    _cam.up = { 0.0f, 1.0f, 0.0f };
}