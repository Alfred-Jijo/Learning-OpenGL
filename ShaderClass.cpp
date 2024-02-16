#include "ShaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string GetFileContents(const char* Filename)
{
	std::ifstream in(Filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* VertexFile, const char* FragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string VertexCode = GetFileContents(VertexFile);
	std::string FragmentCode = GetFileContents(FragmentFile);

	// Convert the shader source strings into character arrays
	const char* VertexSource = VertexCode.c_str();
	const char* FragmentSource = FragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(VertexShader, 1, &VertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(VertexShader);
	CompileErrors(VertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(FragmentShader, 1, &FragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(FragmentShader);
	CompileErrors(FragmentShader, "FRAGMENT");

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, VertexShader);
	glAttachShader(ID, FragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	CompileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

}

// Checks if the different Shaders have compiled properly
void Shader::CompileErrors(unsigned int shader, const char* type) {
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM") {

		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else {
		
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}