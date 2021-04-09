#include "MyApp.h"


#include <math.h>
#include <vector>

#include <array>
#include <list>
#include <tuple>
#include <imgui/imgui.h>
#include "includes/GLUtils.hpp"

CMyApp::CMyApp(void)
{
	m_CubeVaoID=0; // vertex array object erõforrás azonosító
	m_CubeVboID=0; // vertex buffer object erõforrás azonosító
	m_CubeIbID=0;  // index buffer object erõforrás azonosító
	m_CurtainVaoID=0; // vertex array object erõforrás azonosító
	m_CurtainVboID=0; // vertex buffer object erõforrás azonosító
	m_CurtainIbID=0;  // index buffer object erõforrás azonosító

	m_programID = 0;
}


CMyApp::~CMyApp(void)
{
}


glm::vec3 CMyApp::toDesc(float fi, float theta) {
	return glm::vec3(sin(fi) * cos(theta), cos(fi), -sin(fi) * sin(theta));
}

float CMyApp::Bezier(int p1, int p2, int p3, float t) {
	//float t = SDL_GetTicks() / 1000.0f;
	return ((1 - t) * (1 - t) * p1 + 2 * (1 - t) * p2 + t * t * p3);
}

bool CMyApp::Init()
{
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);

	std::vector<Vertex>vertices;

	//front									 
	vertices.push_back({ glm::vec3(-0.5, -0.5, +0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(+0.5, -0.5, +0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, +0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, +0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	//back
	vertices.push_back({ glm::vec3(+0.5, -0.5, -0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, -0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, -0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	//right									 
	vertices.push_back({ glm::vec3(+0.5, -0.5, +0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(+0.5, -0.5, -0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, +0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, -0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	//left									 
	vertices.push_back({ glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(-0.5, -0.5, +0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, -0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, +0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	//top									 
	vertices.push_back({ glm::vec3(-0.5, +0.5, +0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, +0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, -0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, -0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	//bottom								 
	vertices.push_back({ glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(+0.5, -0.5, -0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(-0.5, -0.5, +0.5), glm::vec3(0.654f, 0.435f, 0.247f) });
	vertices.push_back({ glm::vec3(+0.5, -0.5, +0.5), glm::vec3(0.654f, 0.435f, 0.247f) });

	// curtain
	Vertex vert[(N + 1) * (M + 1)];
	float w = 1;
	for (int i = 0; i <= N; ++i)
		for (int j = 0; j <= M; ++j)
		{
			vert[i + j * (N + 1)].p = glm::vec3((float)w*(float)i , j+0.5f, 0.5f);
			//std::cout << i + j * (N + 1) << " " << vert[i + j * (N + 1)].p[0] << " " << vert[i + j * (N + 1)].p[1] << " " << vert[i + j * (N + 1)].p[2] << std::endl;
			vert[i + j * (N + 1)].c = glm::vec3(1, 0, 0);
		}


	GLushort indices[36];
	int index = 0;
	for (int i = 0; i < 6 * 4; i += 4)
	{
		indices[index + 0] = i + 0;
		indices[index + 1] = i + 1;
		indices[index + 2] = i + 2;
		indices[index + 3] = i + 1;
		indices[index + 4] = i + 3;
		indices[index + 5] = i + 2;
		index += 6;
	}


	GLushort indicesCurtain[3 * 2 * (N) * (M)];
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
		{
			indicesCurtain[6 * i + j * 3 * 2 * (N)+0] = (i)+(j) * (N + 1);
			indicesCurtain[6 * i + j * 3 * 2 * (N)+1] = (i + 1) + (j) * (N + 1);
			indicesCurtain[6 * i + j * 3 * 2 * (N)+2] = (i)+(j + 1) * (N + 1);
			indicesCurtain[6 * i + j * 3 * 2 * (N)+3] = (i + 1) + (j) * (N + 1);
			indicesCurtain[6 * i + j * 3 * 2 * (N)+4] = (i + 1) + (j + 1) * (N + 1);
			indicesCurtain[6 * i + j * 3 * 2 * (N)+5] = (i)+(j + 1) * (N + 1);
		}


	//std::cout << vertices[indices[41]].c[0] << " " << vertices[indices[41]].c[1] << " " << vertices[indices[41]].c[2];



	glGenVertexArrays(1, &m_CubeVaoID);
	glBindVertexArray(m_CubeVaoID);
	

	glGenBuffers(1, &m_CubeVboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_CubeVboID);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));

	glGenBuffers(1, &m_CubeIbID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_CubeIbID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	glGenVertexArrays(1, &m_CurtainVaoID);
	glBindVertexArray(m_CurtainVaoID);


	glGenBuffers(1, &m_CurtainVboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_CurtainVboID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));

	glGenBuffers(1, &m_CurtainIbID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_CurtainIbID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesCurtain), indicesCurtain, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	GLuint vs_ID = loadShader(GL_VERTEX_SHADER,		"myVert.vert");
	GLuint fs_ID = loadShader(GL_FRAGMENT_SHADER,	"myFrag.frag");

	m_programID = glCreateProgram();

	glAttachShader(m_programID, vs_ID);
	glAttachShader(m_programID, fs_ID);

	glBindAttribLocation(m_programID, 0, "vs_in_pos");
	glBindAttribLocation(m_programID, 1, "vs_in_col");

	glLinkProgram(m_programID);

	GLint infoLogLength = 0, result = 0;

	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (GL_FALSE == result || infoLogLength != 0)
	{
		std::vector<char> error_massage(infoLogLength);
		glGetProgramInfoLog(m_programID, infoLogLength, NULL, error_massage.data());

		std::cout << "Hiba a shader letrehozasakor: " << error_massage.data() << std::endl;
	}

	glDeleteShader( vs_ID );
	glDeleteShader( fs_ID );

	m_matProj = glm::perspective( 45.0f, 640/480.0f, 1.0f, 1000.0f );

	m_loc_mvp = glGetUniformLocation( m_programID, "MVP");
	m_loc_r = glGetUniformLocation(m_programID, "r");
	m_loc_R = glGetUniformLocation(m_programID, "R");

	return true;
}

void CMyApp::Clean()
{
	glDeleteBuffers(1, &m_CubeVboID);
	glDeleteBuffers(1, &m_CubeIbID);
	glDeleteVertexArrays(1, &m_CubeVaoID);

	glDeleteBuffers(1, &m_CurtainVboID);
	glDeleteBuffers(1, &m_CurtainIbID);
	glDeleteVertexArrays(1, &m_CurtainVaoID);

	glDeleteProgram( m_programID );
}

void CMyApp::Update()
{

	time1 = SDL_GetTicks() - time1;
	if (!stop) {
		passedTime += time1;
	}

	if (!stop) {
		m_eye = glm::vec3(Bezier(-12, 0, 12, passedTime/400000), Bezier(20, 20, 20, passedTime/400000), Bezier(0, -15, 0, passedTime/400000));
	}
	m_matView = glm::lookAt(m_eye, m_at, m_up);

	/*glm::vec3 forward = m_at - m_eye; // = toDesc(m_phi, m_theta);
	if (w) {
		m_eye += 0.1f * forward;
		m_at = m_eye + toDesc(m_fi, m_theta); // m_at += 0.1f * forward;
	}
	if (s) {
		m_eye -= 0.1f * forward;
		m_at = m_eye + toDesc(m_fi, m_theta);
	}
	glm::vec3 left = glm::normalize(glm::cross(m_up, forward));
	if (a) {
		m_eye += 0.1f * left;
		m_at = m_eye + toDesc(m_fi, m_theta);
	}
	if (d) {
		m_eye -= 0.1f * left;
		m_at = m_eye + toDesc(m_fi, m_theta);
	}

	m_matView = glm::lookAt(m_eye, m_at, m_up);*/
}



void CMyApp::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_programID);
	glUniform1f(m_loc_r, r);
	glUniform1f(m_loc_R, R);
	/*

	GLM transzformációs mátrixokra példák:
		glm::rotate<float>( szög, glm::vec3(tengely_x, tengely_y, tengely_z) ) <- tengely_{xyz} körüli elforgatás
		glm::translate<float>( glm::vec3(eltol_x, eltol_y, eltol_z) ) <- eltolás
		glm::scale<float>( glm::vec3(s_x, s_y, s_z) ) <- léptékezés

	*/

	m_matWorld = glm::scale<float>(glm::vec3(4, 2, 2));
	glm::mat4 mvp = m_matProj * m_matView * m_matWorld;
	glUniformMatrix4fv(m_loc_mvp, 1, GL_FALSE, &(mvp[0][0]));
	glBindVertexArray(m_CubeVaoID);

	glDrawElements(GL_TRIANGLES,		// primitív típus
		36,		// hany csucspontot hasznalunk a kirajzolashoz
		GL_UNSIGNED_SHORT,	// indexek tipusa
		0);					// indexek cime
		
	glBindVertexArray(0);


	m_matWorld = 
		glm::scale<float>(glm::vec3(1.0f / N * 4, h, 1)) *
		glm::translate(glm::vec3(-N/2, -h/N*4, 0))
		;
				//glm::rotate<float>(M_PI/2, glm::vec3(0, 1, 0));
	mvp = m_matProj * m_matView * m_matWorld;
	glUniformMatrix4fv(m_loc_mvp, 1, GL_FALSE, &(mvp[0][0]));
	glBindVertexArray(m_CurtainVaoID);

	glDrawElements(GL_TRIANGLES,		// primitív típus
		3 * 2 * (N) * (M),		// hany csucspontot hasznalunk a kirajzolashoz
		GL_UNSIGNED_SHORT,	// indexek tipusa
		0);					// indexek cime

	glBindVertexArray(0);

	//const std::string titleOfWindow = GetTitle();
	static char str0[128] = "OGL";
	char titleid[32] = "###IMGUIWindow";
	char title[128] = "";
	strcat(title, str0);
	strcat(title, titleid);


	if (ImGui::Begin(title)) {
		ImGui::Text("Hello %i", 10);
		ImGui::InputText("ablak cime", str0, IM_ARRAYSIZE(str0));
		ImGui::SliderFloat("gyurodesek melysege", &r, 0.01f, 4.0f);
		ImGui::SliderFloat("gyurodesek surusege", &R, 0.01f, 10.f);
		ImGui::SliderFloat("fuggony magassaga", &h, 0.3f, 7.f);
	}
	ImGui::End();



	glUseProgram( 0 );
}

void CMyApp::KeyboardDown(SDL_KeyboardEvent& key)
{
	switch (key.keysym.sym) {
	case SDLK_SPACE:
		stop = !stop;
		break;
	}

	/*	switch (key.keysym.sym) {
		case SDLK_w:
			w = true;
			break;
		case SDLK_s:
			s = true;
			break;
		case SDLK_a:
			a = true;
			break;
		case SDLK_d:
			d = true;
			break;
		}
		*/
}

void CMyApp::KeyboardUp(SDL_KeyboardEvent& key) {
	/*switch (key.keysym.sym) {
	case SDLK_w:
		w = false;
		break;
	case SDLK_s:
		s = false;
		break;
	case SDLK_a:
		a = false;
		break;
	case SDLK_d:
		d = false;
		break;
	}*/
}


void CMyApp::MouseMove(SDL_MouseMotionEvent& mouse) {
	/*if (mouse.state & SDL_BUTTON_LMASK) {
		m_theta -= mouse.xrel * 0.005;
		m_fi += mouse.yrel * 0.005;
		m_fi = glm::clamp(m_fi, 0.001f, 3.13f);
		m_at = m_eye + toDesc(m_fi, m_theta);
	}*/
}


void CMyApp::MouseDown(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseUp(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseWheel(SDL_MouseWheelEvent& wheel)
{
}

void CMyApp::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h);

	m_matProj = glm::perspective(45.0f, _w / (float)_h, 0.01f, 100.0f);
}