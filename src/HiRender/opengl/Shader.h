#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iterator>
#include <fstream>

#include "Logger.h"

namespace Hi {

	class Shader
	{
	public:
		Shader();
		~Shader();
		void Init(const std::string& vertFilename, const std::string& fragFilename);

		void UseShader();
		unsigned int getShaderProgram() {
			return this->m_shaderProgram;
		}

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
	private:
		unsigned int m_shaderProgram;
	};
}