#include "MasterRenderer.h"
#include "components/TextureLoader.h"

#include <glad/glad.h>
#include <array>
#include <iostream>
#include <fstream>

#ifdef __APPLE__
	#include <CoreFoundation/CoreFoundation.h>
#endif


int MasterRenderer::init()
{
    // Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(board_vertices),
		board_vertices.data(),
		GL_STATIC_DRAW
	);

	#ifdef __APPLE__
		// TODO : ensure the following code can actually run

		const CFBundleRef bundle = CFBundleGetMainBundle();
		const CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(bundle);
		char path[PATH_MAX];
		CFURLGetFileSystemRepresentation(resourcesURL, true, (UInt8*)path, PATH_MAX);
    	CFRelease(resourcesURL);

		std::string vert_path = std::string(path) + "/../../../../res/shaders/vert.glsl";
		const char* vert_shader_path = vert_path.c_str();

		std::string frag_path = std::string(path) + "/../../../../res/shaders/frag.glsl";
		const char* frag_shader_path = frag_path.c_str();

		//const char* vert_shader_path = "../../../../res/shaders/vert.glsl";
		//const char* frag_shader_path = "../../../../res/shaders/frag.glsl";
	#else
		const char* vert_shader_path = "../res/shaders/vert.glsl";
		const char* frag_shader_path = "../res/shaders/frag.glsl";
	#endif

	shaderProgram = initShader(vert_shader_path, frag_shader_path);
	glUseProgram(shaderProgram);

	// Vertex Position
	GLuint vPosition_loc = glGetAttribLocation(shaderProgram, "vPosition");
	if (vPosition_loc < 0){
		fprintf(stderr, "Error: vPosition attrib could not be found.\n");
		return 1;
	}
	glVertexAttribPointer( vPosition_loc, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)0 );
	glEnableVertexAttribArray(vPosition_loc);

	// Vertex Texture Coordinate
	GLuint vTexCoord_loc = glGetAttribLocation(shaderProgram, "vTexCoord");
	if (vTexCoord_loc < 0){
		fprintf(stderr, "Error: vTexCoord attrib could not be found.\n");
		return 1;
	}
	glVertexAttribPointer( vTexCoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, texture_coordinate) );
	glEnableVertexAttribArray(vTexCoord_loc);

	glClearColor(0.0, 0.0, 0.0, 0.0); // Draw black background
	return 0;
}

void MasterRenderer::draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
	//glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(sizeof(squareVertices)/3));
	glDrawArrays(GL_LINE_LOOP, 0, static_cast<GLsizei>(board_vertices.size()));
	
	const std::array<uint64_t, 12> pieces = game_board.getPieces();
	
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

// unsigned int MasterRenderer::loadTexture(const char* filepath)
// {
// 	int width, height, channels;
// 	stbi_set_flip_vertically_on_load(true);

// 	// Load the image using stb
// 	unsigned char* data = stbi_load(filepath, &width, &height, &channels, 4);

// 	if (!data) {
// 		fprintf(stderr, "Error: Failed to load texture at [%s]", filepath);
// 		return 0;
// 	}

// 	GLuint texture;
// 	glGenTextures(1, &texture);
// 	glBindTexture(GL_TEXTURE_2D, texture);
// 	glTexImage2D(
// 		GL_TEXTURE_2D, 0, GL_RGBA, 
// 		width, height, 0, GL_RGBA, 
// 		GL_UNSIGNED_BYTE, data
// 	);
// 	glGenerateMipmap(GL_TEXTURE_2D);

// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// 	// Free the stb image memory
// 	stbi_image_free(data);
//     return texture;
// }

void MasterRenderer::drawPiece()
{

}
