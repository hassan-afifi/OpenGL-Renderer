#include "MyApp.h"
#include "SDL_GLDebugMessageCallback.h"

#include <imgui.h>

CMyApp::CMyApp()
{
}

CMyApp::~CMyApp()
{
}

void CMyApp::SetupDebugCallback()
{
	GLint context_flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
	if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
		glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, GL_DONT_CARE, 0, nullptr, GL_FALSE);
		glDebugMessageCallback(SDL_GLDebugMessageCallback, nullptr);
	}
}

void CMyApp::InitShaders()
{
	m_programID = glCreateProgram();
	AttachShader( m_programID, GL_VERTEX_SHADER, "Shaders/Vert_PosCol.vert" );
	AttachShader( m_programID, GL_FRAGMENT_SHADER, "Shaders/Frag_PosCol.frag" );
	LinkProgram( m_programID );
}

void CMyApp::CleanShaders()
{
	glDeleteProgram( m_programID );
}

void CMyApp::InitGeometry()
{
	MeshObject<VertexPosColor> meshCPU;
	static constexpr float SQRT_2 = glm::root_two<float>();

	meshCPU.vertexArray =
	{
		{ glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.0, 0.0, 0.0)}, //0
		{ glm::vec3( 0.5, -0.5, -0.5), glm::vec3(1.0, 0.0, 0.0)}, //1
		{ glm::vec3(-0.5,  0.5, -0.5), glm::vec3(0.0, 1.0, 0.0)}, //2
		{ glm::vec3(-0.5, -0.5,  0.5), glm::vec3(0.0, 0.0, 1.0)}, //3
		{ glm::vec3( 0.5,  0.5, -0.5), glm::vec3(1.0, 1.0, 0.0)}, //4
		{ glm::vec3( 0.5, -0.5,  0.5), glm::vec3(1.0, 0.0, 1.0)}, //5
		{ glm::vec3(-0.5,  0.5,  0.5), glm::vec3(0.0, 1.0, 1.0)}, //6
		{ glm::vec3( 0.5,  0.5,  0.5), glm::vec3(1.0, 1.0, 1.0)}, //7
	};

	meshCPU.indexArray =
	{
		0, 1, 5,
		0, 5, 3,
		0, 3, 6,
		0, 6, 2,
		0, 2, 1,
		1, 2, 4,
		1, 4, 5,
		4, 7, 5,
		2, 6, 4,
		4, 6, 7,
		3, 5, 7,
		3, 7, 6
	};

	glCreateBuffers( 1, &vboID );
	glNamedBufferData( vboID, meshCPU.vertexArray.size() * sizeof( VertexPosColor ), meshCPU.vertexArray.data(), GL_STATIC_DRAW );
	glCreateBuffers( 1, &iboID );
	glNamedBufferData( iboID, meshCPU.indexArray.size() * sizeof( GLuint ), meshCPU.indexArray.data(), GL_STATIC_DRAW );
	count = static_cast<GLsizei>( meshCPU.indexArray.size() );
	glCreateVertexArrays( 1, &vaoID );
	glVertexArrayVertexBuffer( vaoID, 0, vboID, 0, sizeof( VertexPosColor ) );
	glEnableVertexArrayAttrib( vaoID, 0 );
	glVertexArrayAttribBinding( vaoID, 0, 0 );
	glVertexArrayAttribFormat( vaoID, 0, 3, GL_FLOAT, GL_FALSE, offsetof( VertexPosColor, position ));
	glEnableVertexArrayAttrib( vaoID, 1 );
	glVertexArrayAttribBinding( vaoID, 1, 0 );
	glVertexArrayAttribFormat( vaoID, 1, 3, GL_FLOAT, GL_FALSE, offsetof( VertexPosColor, color ) );
	glVertexArrayElementBuffer( vaoID, iboID );

	cubesCoords[0] = glm::vec3( 0,  0, 0);
	cubesCoords[1] = glm::vec3( 0,  1, 0);
	cubesCoords[2] = glm::vec3(-1,  1, 0);
	cubesCoords[3] = glm::vec3( 0, -1, 0);
	cubesCoords[4] = glm::vec3( 1, -1, 0);

	for (int i = 0; i < 7; i++)
	{
		/*flag = true;
		while (flag) {
			flag = false;
		*/
			randR = (float)rand() / (RAND_MAX / 10.0f);
			randTheta = (float)rand() / (RAND_MAX / pi);
			randPhi = (float)rand() / (RAND_MAX / (2 * pi));

			randCoords[i] = glm::vec3(randR * sin(randTheta) * cos(randPhi), randR* sin(randTheta)* sin(randPhi), randR* cos(randTheta));
			/*
			for (int j = 0; j < i; j++)
			{
				glm::vec3 temp(randCoords[j].x, randCoords[j].y, randCoords[j].z);

				if (glm::distance(randCoords[i], temp) <= 6.f)
				{
					flag = true;
					break;
				}
			}

		}*/
	}
}

void CMyApp::CleanGeometry()
{
	glDeleteBuffers(1,      &vboID);
	glDeleteBuffers(1,      &iboID);
	glDeleteVertexArrays(1, &vaoID);
}

bool CMyApp::Init()
{
	SetupDebugCallback();
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);
	InitShaders();
	InitGeometry();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	m_camera.SetView(
		glm::vec3(0.0, 0.0, 60.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0));

	m_cameraManipulator.SetCamera( &m_camera );
	return true;
}

void CMyApp::Clean()
{
	CleanShaders();
	CleanGeometry();
}

void CMyApp::Update(const SUpdateInfo& updateInfo)
{
	m_ElapsedTimeInSec = updateInfo.ElapsedTimeInSec;
	m_cameraManipulator.Update(updateInfo.DeltaTimeInSec);
	m_DeltaTimeInSec = updateInfo.DeltaTimeInSec;

	if (moveForward) {
		moveCoords.x += m_DeltaTimeInSec * (20.f / 3.f);
	}
	else {
		moveCoords.x -= m_DeltaTimeInSec * (20.f / 3.f);
	}

	if (moveCoords.x >= 10.f) {
		moveForward = false;
	}

	if (moveCoords.x <= -10.f) {
		moveForward = true;
	}

	moveCoords.z = (0.01f * pow(moveCoords.x, 3)) + (0.05f * pow(moveCoords.x, 2));

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 5; j++) {
			m_objectWorldTransformations[(5 * i) + j] = glm::translate(moveCoords) * glm::translate(randCoords[i]) * glm::translate(cubesCoords[j]);

		}
	}

	if (colorPicked) {
		if (colorForward) {
			colorPercent += m_DeltaTimeInSec / (8.f);
		}
		else {
			colorPercent -= m_DeltaTimeInSec / (8.f);
		}
	}

	if (colorPercent >= 1.f) {
		colorForward = false;
	}

	if (colorPercent <= 0.f) {
		colorForward = true;
	}
}

void CMyApp::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram( m_programID );
	glBindVertexArray(vaoID);

	glUniformMatrix4fv( ul("viewProj"), 1, GL_FALSE, glm::value_ptr( m_camera.GetViewProj() ) );
	glUniform3fv(glGetUniformLocation(m_programID, "pickedColor"), 1, &pickedColor[0]);
	glUniform1f(glGetUniformLocation(m_programID, "colorPercent"), colorPercent);

	for (int i = 0; i < 35; i++)
	{
		glUniformMatrix4fv(ul("world"), 1, GL_FALSE, glm::value_ptr(m_objectWorldTransformations[i]));
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
	glUseProgram( 0 );
	glBindVertexArray( 0 );
}

void CMyApp::RenderGUI()
{
	ImGui::Begin("Color animation");
	float col[3] = { pickedColor.r, pickedColor.g, pickedColor.b };

	if (ImGui::ColorEdit3("Pick a color", col))
	{
		pickedColor = glm::vec3(col[0], col[1], col[2]);
		colorPicked = true;
	}

	ImGui::End();
}

void CMyApp::KeyboardDown(const SDL_KeyboardEvent& key)
{	
	if ( !key.repeat )
	{
		if ( key.key == SDLK_F5 && key.mod & SDL_KMOD_CTRL )
		{
			CleanShaders();
			InitShaders();
		}
		if ( key.key == SDLK_F1 )
		{
			GLint polygonModeFrontAndBack[ 2 ] = {};
			glGetIntegerv( GL_POLYGON_MODE, polygonModeFrontAndBack );
			GLenum polygonMode = ( polygonModeFrontAndBack[ 0 ] != GL_FILL ? GL_FILL : GL_LINE );
			glPolygonMode( GL_FRONT_AND_BACK, polygonMode );
		}
	}
	m_cameraManipulator.KeyboardDown( key );
}

void CMyApp::KeyboardUp(const SDL_KeyboardEvent& key)
{
	m_cameraManipulator.KeyboardUp( key );
}

void CMyApp::MouseMove(const SDL_MouseMotionEvent& mouse)
{
	m_cameraManipulator.MouseMove( mouse );
}

void CMyApp::MouseDown(const SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseUp(const SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseWheel(const SDL_MouseWheelEvent& wheel)
{
	m_cameraManipulator.MouseWheel( wheel );
}

void CMyApp::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h);
	m_camera.SetAspect( static_cast<float>(_w) / _h );
}

void CMyApp::OtherEvent( const SDL_Event& ev )
{

}