#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include "GLUtils.hpp"
#include "Camera.h"
#include "CameraManipulator.h"

struct SUpdateInfo
{
	float ElapsedTimeInSec = 0.0f;
	float DeltaTimeInSec   = 0.0f;
};

class CMyApp
{
public:
	CMyApp();
	~CMyApp();
	bool Init();
	void Clean();
	void Update( const SUpdateInfo& );
	void Render();
	void RenderGUI();
	void KeyboardDown(const SDL_KeyboardEvent&);
	void KeyboardUp(const SDL_KeyboardEvent&);
	void MouseMove(const SDL_MouseMotionEvent&);
	void MouseDown(const SDL_MouseButtonEvent&);
	void MouseUp(const SDL_MouseButtonEvent&);
	void MouseWheel(const SDL_MouseWheelEvent&);
	void Resize(int, int);
	void OtherEvent( const SDL_Event& );
protected:
	void SetupDebugCallback();

	float m_ElapsedTimeInSec = 0.0f;
	float m_DeltaTimeInSec = 0.0f;

	glm::vec3 cubesCoords[5];

	//bool flag = true;

	float pi = 3.1415927;
	float randR;
	float randTheta;
	float randPhi;
	glm::vec3 randCoords[7];

	glm::vec3 moveCoords = glm::vec3(0.f);
	bool moveForward = true;

	glm::vec3 pickedColor = glm::vec3(0.f);
	bool colorPicked = false;
	bool colorForward = true;
	float colorPercent = 1.0f;

	glm::mat4 m_objectWorldTransformations[35];

	Camera m_camera;
	CameraManipulator m_cameraManipulator;

	GLuint m_programID = 0;

	void InitShaders();
	void CleanShaders();

	GLuint  vaoID = 0;
	GLuint  vboID = 0;
	GLuint  iboID = 0;
	GLsizei count = 0;

	void InitGeometry();
	void CleanGeometry();
};
