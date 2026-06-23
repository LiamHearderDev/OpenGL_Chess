#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <array>
#include <iostream>
#include <cstdint>
#include <fstream>


GLuint shaderProgram{};

constexpr auto squareVertices = std::array{
    -0.5f, 0.5f, 0.0f,  // Top-left
    0.5f, 0.5f, 0.0f,   // Top-right
    0.5f, 0.5f, 0.0f,   // Top-right
    0.5f, -0.5f, 0.0f,  // Bottom-right
    0.5f, -0.5f, 0.0f,  // Bottom-right
    -0.5f, -0.5f, 0.0f, // Bottom-left
    -0.5f, -0.5f, 0.0f, // Bottom-left
    -0.5f, 0.5f, 0.0f   // Top-left
};


void OnFramebufferSizeChanged(GLFWwindow *window, int32_t width, int32_t height);
void render(GLFWwindow *window);
void error_callback(int error, const char* description);
GLuint InitShader(const char* vert_shader, const char* frag_shader);


int main() {

	// ======== GLFW setup ======== //

	// Initialize GLFW
	// TODO: This will all be abstracted out into its own class
	if (!glfwInit())
	{
		fprintf(stderr, "Error: Failed to initialise GLFW.");
		return 1;
	}
	glfwSetErrorCallback(error_callback);

	// Add window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Needed for apple devices, as only forward compatability is supported
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create Window
	GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Chess", NULL, NULL);
	if (NULL == window) {
		fprintf(stderr, "Error: Failed to create GLFW window.");
		glfwTerminate();
		return 1;
	}

	// Activate the GLFW context
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
		fprintf(stderr, "Error: Failed to initialise GLEW.");
		return 1;
	}

	// Connect frame buffer size changed callback
	glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChanged);


	// ======== OpenGL setup ======== //

	// Vertex Array Object
	GLuint VAO;
	glGenVertexArrays(1, &VAO); // TODO: Add the apple version for this
	glBindVertexArray(VAO);

	// Vertex Buffer Object
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(
		GL_ARRAY_BUFFER, 
		squareVertices.size() * sizeof(float),
		squareVertices.data(),
		GL_STATIC_DRAW
	);

	// shaders
	shaderProgram = InitShader("../res/shaders/vert.glsl", "../res/shaders/frag.glsl");
	glUseProgram(shaderProgram);

	// Initialise vertex position attribute
	GLuint vPos = glGetAttribLocation(shaderProgram, "vPosition");
	glVertexAttribPointer(vPos, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(vPos);

	glClearColor(0.0, 0.0, 0.0, 0.0); // Draw black background
	
	// Event Loop
	while (false == glfwWindowShouldClose(window)) {
		render(window);
		glfwPollEvents();
	}

	// Finish up OpenGL
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	return 0;
}



void OnFramebufferSizeChanged(GLFWwindow *window, int32_t width, int32_t height) {
	glViewport(0, 0, width, height);
	render(window);
}

void render(GLFWwindow *window){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);
	glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(squareVertices.size()/3));
	
	glfwSwapBuffers(window);
}

std::string loadShaderSource(const char* filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) return "";
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

GLuint InitShader(const char* vert_shader, const char* frag_shader) {
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

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}