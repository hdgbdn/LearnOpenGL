#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "CommonHeader.h"

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

enum Camera_Control_Mode
{
	NONE,
	FREE,
	ARCBALL,
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
        float yaw, float pitch);

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW, float pitch = PITCH);
	

    glm::mat4 GetViewMatrix() const;

    void SetControlMode(Camera_Control_Mode);

    void Move(Camera_Movement direction, float deltaTime);
    void RotateByMouse(float xOffset, float yOffset, GLboolean constrainPitch = false);
    void ProcessMouseScroll(float yOffset);

    glm::vec3 GetPosition() const;
    glm::vec3 GetFront() const;
    glm::vec3 GetUp() const;
    glm::vec3 GetRight() const;
    glm::vec3 GetWorldUp() const;
    float GetYaw() const;
    float GetPitch() const;
    float GetZoom() const;

private:
    Camera_Control_Mode ctrlMode;
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
	
    bool ViewMode;
	
    void updateCameraVectors();
};

#endif