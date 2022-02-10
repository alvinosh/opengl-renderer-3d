#pragma once

#include <glad/glad.h>

#include <string>
#include <map>
#include <utility>
#include <sstream>
#include <fstream>
#include <iostream>
#include <assert.h>

#include "error.hpp"

std::string ParseShaderFile(uint32_t type, const std::string file_path);
uint32_t CompileShader(uint32_t type, std::string source);
uint32_t CreateProgram(uint32_t vs, uint32_t fs);

class Shader
{
private:
  uint32_t m_id;

public:
  Shader(std::string vert_src, std::string frag_src);
  Shader(std::string path);
  ~Shader();

  void Use();

  void SetBool(const char* name, bool value) const;
  void SetInt(const char* name, int32_t value) const;
  void SetFloat(const char* name, float value) const;

  uint32_t Id();
};