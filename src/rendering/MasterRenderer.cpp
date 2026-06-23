#include "MasterRenderer.h"

#include <array>
#include <iostream>
#include <fstream>

void MasterRenderer::init()
{

    // Vertex Array Object
	glGenVertexArrays(1, &VAO); // TODO: Add the apple version for this
	glBindVertexArray(VAO);

	// Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(squareVertices),
		squareVertices,
		GL_STATIC_DRAW
	);

	// shaders
	shaderProgram = initShader("../res/shaders/vert.glsl", "../res/shaders/frag.glsl");
	glUseProgram(shaderProgram);

	// Initialise vertex position attribute
	GLuint vPos = glGetAttribLocation(shaderProgram, "vPosition");
	glVertexAttribPointer(vPos, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
	glEnableVertexAttribArray(vPos);

	glClearColor(0.0, 0.0, 0.0, 0.0); // Draw black background
}

void MasterRenderer::draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
	glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(sizeof(squareVertices)/3));
}

void MasterRenderer::finish()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
}


std::string loadShaderSource(const char* filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) return "";
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

GLuint MasterRenderer::initShader(const char* vert_shader, const char* frag_shader) {
	// 1. Load source code
	std::string vCodeStr = loadShaderSource(vert_shader);
	std::string fCodeStr = loadShaderSource(frag_shader);
	const char* vCode = vCodeStr.c_str();
	const char* fCode = fCodeStr.c_str();

	if (vCodeStr.empty() || fCodeStr.empty()) {
    	fprintf(stderr, "Failed to load shader files: %s , %s\n", vert_shader, frag_shader);
    	return 0;
	}

	// 2. Create shader objects
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	// 3. Attach source code and compile
	glShaderSource(vertex, 1, &vCode, NULL);
	glCompileShader(vertex);
	glShaderSource(fragment, 1, &fCode, NULL);
	glCompileShader(fragment);
	
	// 4. Create Program and link shaders
	GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

	// 5. Clean up (shaders are now linked into the program)
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}