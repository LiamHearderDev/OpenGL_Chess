#ifndef BASE_MATERIAL_H
#define BASE_MATERIAL_H

#include <string>

class BaseMaterial {
    std::string vert_file_path; // TODO: ensure these are actually used.
    std::string frag_file_path;

    unsigned int shader_program; // Represents the initialised shader.
    unsigned int texture_id;

public:
    // Constructor
    BaseMaterial(std::string vert_file_path, std::string frag_file_path) : 
        vert_file_path(vert_file_path), frag_file_path(frag_file_path) {}

    // Destructor
    ~BaseMaterial() { finish(); }

    void init();
    void finish();
    void use();
    void init_textures();

    unsigned int get_texture_id() { return texture_id; }

private:
    std::string get_vert_shader_path();
    std::string get_frag_shader_path();
    std::string _get_shader_path(bool type);
    std::string _load_shader_source(const char* filepath);
};

#endif // BASE_MATERIAL_H