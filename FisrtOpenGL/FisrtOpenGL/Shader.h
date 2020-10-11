#pragma once
#include <string>

class Shader
{
public:
	Shader(const char* vertexPath,const char* fragmenttPath);
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID; //shader program ID
	void use();

private:
	void checkCompileErrors(unsigned int ID,std::string type);

};

