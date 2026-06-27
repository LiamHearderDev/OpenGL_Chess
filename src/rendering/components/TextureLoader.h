#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H


/**
 * A class designed to load textures into memory. This is seperate 
 * from `MasterRenderer` to ensure only one class uses `stb_image`.
 */
class TextureLoader {
public:
    static unsigned int loadTexture(const char* filepath);
};

#endif // TEXTURE_LOADER_H