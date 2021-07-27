#include "Camera.h"

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
    float yaw, float pitch)
    : Position(posX, posY, posZ), WorldUp(upX, upY, upZ), Yaw(yaw), Pitch(pitch),
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM), ctrlMode(Camera_Control_Mode::NONE)
{
    updateCameraVectors();
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Camera(position.x, position.y, position.z, up.x, up.y, up.z, yaw, pitch) {}

glm::vec3 Camera::GetPosition() const
{
    return Position;
}

glm::vec3 Camera::GetFront() const
{
    return Front;
}

glm::vec3 Camera::GetUp() const
{
    return Up;
}

glm::vec3 Camera::GetRight() const
{
    return Right;
}

glm::vec3 Camera::GetWorldUp() const
{
    return WorldUp;
}

float Camera::GetYaw() const
{
    return Yaw;
}

float Camera::GetPitch() const
{
    return Pitch;
}

float Camera::GetZoom() const
{
    return Zoom;
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::SetControlMode(Camera_Control_Mode mode)
{
    ctrlMode = mode;
}


void Camera::Move(Camera_Movement direction, float deltaTime)
{
    float distance = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * distance;
    if (direction == BACKWARD)
        Position -= Front * distance;
    if (direction == LEFT)
        Position -= Right * distance;
    if (direction == RIGHT)
        Position += Right * distance;
}

void Camera::RotateByMouse(float xoffset, float yoffset, GLboolean constrainPitch)
{
    if(ctrlMode == Camera_Control_Mode::FREE)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch -= yoffset;

        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }
        updateCameraVectors();
    }
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}