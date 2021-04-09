#pragma once

#include <memory>
#include <string>


// GLEW
#include <GL/glew.h>

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>


class CMyApp
{
public:
	CMyApp(void);
	~CMyApp(void);

	bool Init();
	void Clean();

	void Update();
	void Render();

	void KeyboardDown(SDL_KeyboardEvent&);
	void KeyboardUp(SDL_KeyboardEvent&);
	void MouseMove(SDL_MouseMotionEvent&);
	void MouseDown(SDL_MouseButtonEvent&);
	void MouseUp(SDL_MouseButtonEvent&);
	void MouseWheel(SDL_MouseWheelEvent&);
	void Resize(int, int);

	/*std::string GetTitle() {
		return title;
	}*/

	glm::vec3 toDesc(float fi, float theta);
protected:

	// shaderekhez sz�ks�ges v�ltoz�k
	GLuint m_programID; // shaderek programja

	// OpenGL-es dolgok
	GLuint m_CubeVaoID; // vertex array object er�forr�s azonos�t�
	GLuint m_CubeVboID; // vertex buffer object er�forr�s azonos�t�
	GLuint m_CubeIbID;  // index buffer object er�forr�s azonos�t�
	GLuint m_CurtainVaoID; // vertex array object er�forr�s azonos�t�
	GLuint m_CurtainVboID; // vertex buffer object er�forr�s azonos�t�
	GLuint m_CurtainIbID;  // index buffer object er�forr�s azonos�t�


	// transzform�ci�s m�trixok
	glm::mat4 m_matWorld;
	glm::mat4 m_matView;
	glm::mat4 m_matProj;

	// m�trixok helye a shaderekben
	GLuint	m_loc_mvp; // a h�rom m�trixunk szorzat�t adjuk �t a hat�konys�g �rdek�ben

	GLuint	m_loc_r;
	GLuint	m_loc_R;
	float r = 0.1f;
	float R = 1.0f;
	float h = 1.0f;
	//char title[125] = "OGL window";

	float Bezier(int p1, int p2, int p3, float t);

	glm::vec3 m_eye = glm::vec3(10, 0, 10);
	glm::vec3 m_at = glm::vec3(0, 0, 0);
	glm::vec3 m_up = glm::vec3(0, 1, 0);


	/*float m_fi = M_PI / 2.0;
	float m_theta = M_PI / 2.0;

	glm::vec3 m_eye = glm::vec3(0, 0, 10);
	glm::vec3 m_at = m_eye + toDesc(m_fi, m_theta);
	glm::vec3 m_up = glm::vec3(0, 1, 0);

	bool w = false, a = false, s = false, d = false;*/

	bool stop = false;
	float passedTime = 0;
	float time1 = 0;
	float time2 = 0;


	struct Vertex
	{
		glm::vec3 p;
		glm::vec3 c;
	};

	static const int N = 50;
	static const int M = 1;

};

