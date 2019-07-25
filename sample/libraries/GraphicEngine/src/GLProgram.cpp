#include "GLProgram.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils\FileUtils.h"


const std::string GLProgram::ATTRIBUTE_POSITION = "a_posL";

bool GLProgram::initWithCompiledShaders(GLuint vsId, GLuint fsId)
{
	_GLProgramid = glCreateProgram();

	if (_GLProgramid == 0)
	{
		return false;
	}

	glAttachShader(_GLProgramid, vsId);
	glAttachShader(_GLProgramid, fsId);

	if (!link())
	{
		return false;
	}

	return true;
}

bool GLProgram::initWithFiles(const std::string& vsFile, const std::string& fsFile)
{
	_vsId = compileShader(GL_VERTEX_SHADER, vsFile);

	if (_vsId == 0)
	{
		return false;
	}

	_fsId = compileShader(GL_FRAGMENT_SHADER, fsFile);

	if (_fsId == 0)
	{
		glDeleteShader(_vsId);
		return false;
	}

	if (!initWithCompiledShaders(_vsId, _fsId))
	{
		return false;
	}

	return true;
}

void GLProgram::use()
{
	glUseProgram(_GLProgramid);
}

bool GLProgram::link()
{
	glLinkProgram(_GLProgramid);

	std::string errorStr = getLastError(GL_LINK_STATUS);
	if (errorStr != "")
	{
		glDeleteProgram(_GLProgramid);
		printf("link shader error: %s", errorStr.c_str());
		return false;
	}

	return true;
}

GLint GLProgram::getAttribute(const std::string& name)
{
	return glGetAttribLocation(_GLProgramid, name.c_str());
}

GLint GLProgram::getUniform(const std::string& name)
{
	return glGetUniformLocation(_GLProgramid, name.c_str());
}



/*
type: GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
*/
GLuint GLProgram::compileShader(GLenum type, const std::string& filepath)
{
	GLuint shader;

	// Create the shader object
	shader = glCreateShader(type);

	if (shader == 0)
		return 0;

	std::string shaderSrc = FileUtils::getInstance()->getFileContentText(filepath);
	const char* rawShaderSrc = shaderSrc.c_str();

	glShaderSource(shader, 1, &rawShaderSrc, NULL);

	// Compile the shader
	glCompileShader(shader);

	std::string errorStr = getLastError(GL_COMPILE_STATUS);
	if (errorStr != "")
	{
		glDeleteShader(shader);
		printf("compile shader error: %s", errorStr.c_str());
		return 0;
	}

	return shader;
}

GLProgram::~GLProgram()
{
	glDeleteProgram(_GLProgramid);
	glDeleteShader(_vsId);
	glDeleteShader(_fsId);
}

GLProgram* GLProgram::createWithFiles(const std::string& vsFile, const std::string& fsFile)
{
	auto program = new GLProgram();

	if (program && program->initWithFiles(vsFile, fsFile))
	{
		return program;
	}

	delete program;
	program = 0;

	return nullptr;
}

std::string GLProgram::getLastError(GLenum errortype)
{
	GLint hasError = 0;
	glGetProgramiv(_GLProgramid, errortype, &hasError);

	if (!hasError)
	{
		GLint errorStrLen = 0;
		glGetProgramiv(_GLProgramid, GL_INFO_LOG_LENGTH, &errorStrLen);

		if (errorStrLen > 1)
		{
			char* errorStrBuffer = new char[sizeof(char) * errorStrLen];
			glGetProgramInfoLog(_GLProgramid, errorStrLen, NULL, errorStrBuffer);

			std::string errorString = errorStrBuffer;
			delete[] errorStrBuffer;

			return errorString;
		}
	}

	return "";
}
