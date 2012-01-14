#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include<map>
#include<string>
#include<GL/gl.h>
#include<algorithm>

class TextureManager
{
    public:
        TextureManager();
        virtual ~TextureManager();
        std::string addTexture(const std::string&, const std::string&);
        bool IDExists(const std::string&) const;
        GLuint getTextureFromID(const std::string&) const;
        GLuint getTextureFromFilename(const std::string&) const;
        void bindTextureID(const std::string&) const;
        void bindFilename(const std::string&) const;
        void clear();
    protected:
    private:
        std::map<std::string,GLuint> textures;
        std::map<std::string,GLuint> file2idMap;
        bool glTextureEnabled;
};

#endif // TEXTUREMANAGER_H
