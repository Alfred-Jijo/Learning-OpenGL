#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>


std::string GetFileContents(const char* Filename);

class Shader
{
public :
	GLuint ID;
	Shader(const char* VertexFile, const char* FragmentFile);

	void Activate();
	void Delete();
};

