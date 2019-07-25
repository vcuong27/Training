#pragma once

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <string>


class GLProgram
{
public:
	static const std::string ATTRIBUTE_POSITION;

	static GLProgram* createWithFiles(const std::string& vsFile, const std::string& fsFile);
	bool initWithFiles(const std::string& vsFile, const std::string& fsFile);
	bool initWithCompiledShaders(GLuint vsId, GLuint fsId);

	void use();

	GLint getAttribute(const std::string& name);
	GLint getUniform(const std::string& name);

	std::string getLastError(GLenum errortype);

	virtual ~GLProgram();

	void setName(std::string name){
		_name	=	name;
	}
	std::string getName(){
		return _name;
	}
	void setId(GLuint id){
		_id		=	id;
	}
	GLuint getId(){
		return _id;
	}

private:
	GLuint		_GLProgramid;
	GLuint		_vsId;
	GLuint		_fsId;
	std::string _name;
	GLuint		_id;

	GLuint compileShader(GLenum type, const std::string& filepath);
	bool link();
};

