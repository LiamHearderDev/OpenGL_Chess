#ifndef BASE_MATERIAL_H
#define BASE_MATERIAL_H

#include <string>

class BaseMaterial {
    std::string vert_file_path;
    std::string frag_file_path;

    unsigned int shader_program; // Represents the initialised shader.

public:
    // Constructor
    BaseMaterial(std::string vert_file_path, std::string frag_file_path) : 
        vert_file_path(vert_file_path), frag_file_path(frag_file_path) {}

    // Destructor
    ~BaseMaterial() { finish(); }

    void init();
    void finish();
    void use();

private:
    const char* get_vert_shader_path();
    const char* get_frag_shader_path();

    std::string _load_shader_source(const char* filepath);

};

#endif // BASE_MATERIAL_H