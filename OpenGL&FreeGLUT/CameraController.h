
#pragma once
#include "Structures.h"   // Vector3 + Camera struct
#include <cmath>

class CameraController
{
public:
    CameraController();

    // Setup
    void SetPosition(const Vector3& pos);
    void SetLookAt(const Vector3& target);
    void SetMoveSpeed(float s);
    void SetMouseSensitivity(float s);

    // Update / Apply
    void ApplyView() const;         // calls gluLookAt using internal Camera data
    void ProcessMouseDelta(int dx, int dy);  // mouse-look (yaw/pitch)
    void MoveForward(float amount);
    void StrafeRight(float amount);
    void MoveUp(float amount);

    // Follow mode
    void EnableFollow(bool enabled);
    bool IsFollowEnabled() const;
    void SetFollowTarget(Vector3* targetPos);  // follow a Vector3 position
    void SetFollowOffset(const Vector3& offset);
    void UpdateFollow();             // update camera position if follow enabled

    // Access
    const Camera& GetData() const { return _cam; } // for HUD/debug
    float GetYaw() const { return _yaw; }
    float GetPitch() const { return _pitch; }

private:
    Camera _cam{};          // uses your existing Camera struct (eye/center/up)
    float _yaw;             // degrees
    float _pitch;           // degrees
    float _moveSpeed;       // units per key step
    float _mouseSensitivity;// degrees per pixel

    // follow
    bool _followEnabled;
    Vector3* _followTargetPos; // pointer to target position
    Vector3 _followOffset;

private:
    static Vector3 Normalize(const Vector3& v);
    static Vector3 Cross(const Vector3& a, const Vector3& b);
    static Vector3 Add(const Vector3& a, const Vector3& b);
    static Vector3 Sub(const Vector3& a, const Vector3& b);
    static Vector3 Mul(const Vector3& v, float s);

    void UpdateCenterFromYawPitch();
};
