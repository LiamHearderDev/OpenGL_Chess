#include "BaseMaterial.h"

#include <glad/glad.h>
#include <fstream>      // For _loadShaderSource()

#ifdef __APPLE__
	#include <CoreFoundation/CoreFoundation.h>
#endif

void BaseMaterial::init()
{
    // 1. Load source code
	vert_file_path = get_vert_shader_path();
	frag_file_path = get_frag_shader_path();

	std::string vCodeStr = _load_shader_source(vert_file_path.c_str());
	std::string fCodeStr = _load_shader_source(frag_file_path.c_str());

    if (vCodeStr.empty() || fCodeStr.empty()) {
    	fprintf(stderr, "Error: Failed to load shader files: %s , %s\n", vert_file_path.c_str(), frag_file_path.c_str());
    	return;
	}

	// 2. Create shader objects
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	// 3. Attach source code and compile
    const char* vCode = vCodeStr.c_str();
	glShaderSource(vertex, 1, &vCode, NULL);
	glCompileShader(vertex);

    const char* fCode = fCodeStr.c_str();
	glShaderSource(fragment, 1, &fCode, NULL);
	glCompileShader(fragment);
	
	// 4. Create Program and link shaders
	shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex);
    glAttachShader(shader_program, fragment);
    glLinkProgram(shader_program);

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

std::string BaseMaterial::_load_shader_source(const char* filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) return "";
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}


/**
 * NEVER CALL MANUALLY. Only for internal use.
 * This function returns the file path of either a vert or frag shader, depending on input type.
 * If you want to get a shader, use either `get_vert_shader_path()` or `get_frag_shader_path()`.
 */
std::string _get_shader_path(bool type)
{
    #ifdef __APPLE__
		// TODO : ensure the following code can actually run

		const CFBundleRef bundle = CFBundleGetMainBundle();
		const CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(bundle);
		char path[PATH_MAX];
		
		CFURLGetFileSystemRepresentation(resourcesURL, true, (UInt8*)path, PATH_MAX);
    	CFRelease(resourcesURL);

		std::string vert_path = std::string(path) + "/../../../../res/shaders/vert.glsl";
		std::string frag_path = std::string(path) + "/../../../../res/shaders/frag.glsl";

	#else
		std::string vert_shader_path = "../res/shaders/vert.glsl";
		std::string frag_shader_path = "../res/shaders/frag.glsl";
	#endif
    
    return (type == 0) ? (vert_path) : (frag_path);
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