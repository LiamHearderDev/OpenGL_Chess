#include "BaseMaterial.h"

#include <glad/glad.h>
#include <fstream>      // for `_loadShaderSource()`
#include <filesystem>   // for `_get_shader_path()`
#include <iostream>     // for logs

#include "rendering/components/TextureLoader.h"


void log_shader_errors(GLuint shader, const char* label)
{
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << label << " compilation failed:\n" << infoLog << std::endl;
    }
}

void log_program_errors(GLuint program)
{
    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[1024];
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Shader program link failed:\n" << infoLog << std::endl;
    }
}


void BaseMaterial::init()
{
    std::string vert_shader = get_vert_shader_path();
    std::string frag_shader = get_frag_shader_path();

	std::string vCodeStr = _load_shader_source(vert_shader.c_str());
	std::string fCodeStr = _load_shader_source(frag_shader.c_str());

    if (vCodeStr.empty() || fCodeStr.empty()) {
    	fprintf(stderr, "Error: Failed to load shader files: %s , %s\n", vert_shader.c_str(), frag_shader.c_str());
    	return;
	}

	// 2. Create shader objects
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	// 3. Attach source code and compile
    const char* vCode = vCodeStr.c_str();
	glShaderSource(vertex, 1, &vCode, NULL);
	glCompileShader(vertex);
    log_shader_errors(vertex, "Vertex shader");

    const char* fCode = fCodeStr.c_str();
	glShaderSource(fragment, 1, &fCode, NULL);
	glCompileShader(fragment);
    log_shader_errors(fragment, "Fragment shader");
	
	// 4. Create Program and link shaders
	shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex);
    glAttachShader(shader_program, fragment);
    glLinkProgram(shader_program);
    log_program_errors(shader_program);

	// 5. Clean up (shaders are now linked into the program)
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void BaseMaterial::finish() 
{
    glDeleteProgram(shader_program);
}

void BaseMaterial::use()
{
    glUseProgram(shader_program);
}

void BaseMaterial::init_textures()
{	
	glActiveTexture(GL_TEXTURE0);
	//unsigned int texture_id = TextureLoader::loadTexture();
}

std::string BaseMaterial::_load_shader_source(const char* filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) return "";
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}


/**
 * NEVER CALL MANUALLY. Only for internal use.
 * This function returns the file path of either a vert or frag shader, depending on input type.
 * If you want to get a shader, use either `get_vert_shader_path()` or `get_frag_shader_path()`.
 * 
 * This code recursively checks if a file exists in the current directory or the parent directory.
 */
std::string BaseMaterial::_get_shader_path(bool type)
{
    const std::string shader_path = (type == 0) ? vert_file_path : frag_file_path;

    const int max_depth = 5;
    int current_depth = 0;

    for (std::filesystem::path dir = std::filesystem::current_path(); !dir.empty(); dir = dir.parent_path())
    {
        if (current_depth > max_depth){ break; }
        const std::filesystem::path candidate = dir / "res" / "shaders" / shader_path;
        if (std::filesystem::exists(candidate))
        {
            return candidate.string();
        }
        current_depth++;
    }

    return (std::filesystem::current_path() / "res" / "shaders" / shader_path).string();
}


// Returns the file path of the vertex shader used by this entity.
std::string BaseMaterial::get_vert_shader_path()
{
    return _get_shader_path(0); // 0 = vertex shader
}


// Returns the file path of the fragment shader used by this entity.
std::string BaseMaterial::get_frag_shader_path()
{
    return _get_shader_path(1); // 1 = fragment shader
}