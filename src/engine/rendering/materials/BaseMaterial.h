#ifndef BASE_MATERIAL_H
#define BASE_MATERIAL_H

#include <string>
#include <utility>

class BaseMaterial {
protected:
    std::string vert_file_path;
    std::string frag_file_path;
    std::string texture_file_path;

    unsigned int shader_program; // Represents the initialised shader.
    unsigned int texture_id;

public:
    // Constructor
    BaseMaterial(std::string vert_file_path, std::string frag_file_path, std::string texture_file_path = "") :
        vert_file_path(std::move(vert_file_path)),
        frag_file_path(std::move(frag_file_path)),
        texture_file_path(std::move(texture_file_path)),
        shader_program(0),
        texture_id(0) {}

    // Destructor
    ~BaseMaterial() { finish(); }

    void init();
    void finish();
    void use();
    void init_textures();

    unsigned int get_texture_id() { return texture_id; }
    std::string _get_texture_file_path(const char* filepath);
    unsigned int get_shader_program() { return shader_program; }

private:
    std::string get_vert_shader_path();
    std::string get_frag_shader_path();
    std::string _get_shader_path(bool type);
    std::string _load_shader_source(const char* filepath);
};

#endif // BASE_MATERIAL_H