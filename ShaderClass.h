#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string GetFileContents(const char* Filename);


class Shader {
	public:
		// Reference ID of the Shader Program
		GLuint ID;
		// Constructor that build the Shader Program from 2 different shaders
		Shader(const char* VertexFile, const char* FragmentFile);

		// Activates the Shader Program
		void Activate();
		// Deletes the Shader Program
		void Delete();
};
