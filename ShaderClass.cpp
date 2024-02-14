#include"ShaderClass.h"

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

	// Create Fragment Shader Object and get its reference
	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(FragmentShader, 1, &FragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(FragmentShader);

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, VertexShader);
	glAttachShader(ID, FragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

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