////
//// Created by adun on 2017. 11. 20..
////
//
//#include <GL/glut.h>     // ¶Ç´Â <GL/feeeglut.h> 
//#include "FreeImage.h"
//#include"imageload.h"
//#include <string>
//
//
//        enum TextureWrap
//        {
//            REPEAT          = GL_REPEAT,
//            CLAMP           = GL_CLAMP,
//            //MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
//            //CLAMP_TO_EDGE   = GL_CLAMP_TO_EDGE,
//            //CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
//        };
//
//        class Texture
//        {
//        private:
//            static TextureWrap s_wrapMode;
//
//        private:
//            std::string m_name;
//            std::string m_fileName;
//            GLuint m_TID;
//            GLsizei m_width, m_height;
//            unsigned m_bits;
//
//        public:
//            Texture(const std::string name, const std::string fileName);
//            ~Texture();
//
//            void bind()   const;
//            void unbind() const;
//
//            inline const std::string& getName  () const { return m_name;   }
//            inline const unsigned int getWidth () const { return m_width;  }
//            inline const unsigned int getHeight() const { return m_height; }
//            inline const unsigned int getID    () const { return m_TID;    }
//
//        public:
//            inline static void SetWrap(TextureWrap mode) { s_wrapMode = mode; }
//
//        private:
//            GLuint load();
//        };
//
// Created by adun on 2017. 11. 20..
//
#include <string>
#include "imageload.h"

enum TextureWrap
{
	REPEAT = GL_REPEAT,
	CLAMP = GL_CLAMP,
	//MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
	//CLAMP_TO_EDGE   = GL_CLAMP_TO_EDGE,
	//CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
};

class Texture
{
private:
	static TextureWrap s_wrapMode;

private:
	std::string m_name;
	std::string m_fileName;
	GLuint m_TID;
	GLsizei m_width, m_height;
	unsigned m_bits;

public:
	Texture(const std::string name, const std::string fileName);
	~Texture();

	void bind()   const;
	void unbind() const;

	inline const std::string& getName() const { return m_name; }
	inline const unsigned int getWidth() const { return m_width; }
	inline const unsigned int getHeight() const { return m_height; }
	inline const unsigned int getID() const { return m_TID; }

public:
	inline static void SetWrap(TextureWrap mode) { s_wrapMode = mode; }

private:
	GLuint load();
};