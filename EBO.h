#pragma once

#include<glad/glad.h>

namespace Classes {
	class EBO {
	public:
		// ID reference of Elements Buffer Object
		GLuint ID;
		// Constructor that generates a Elements Buffer Object and links it to indices
		EBO(GLuint* Indices, GLsizeiptr Size);

		// Binds the EBO
		void Bind();
		// Unbinds the EBO
		void Unbind();
		// Deletes the EBO
		void Delete();
	};
}