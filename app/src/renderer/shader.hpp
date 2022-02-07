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

std::string parse_shader_file(uint32_t type, const std::string file_path);
uint32_t compile_shader(uint32_t type, std::string source);
uint32_t create_program(uint32_t vs, uint32_t fs);

class Shader
{
private:
  uint32_t m_id;

public:
  Shader(std::string vert_src, std::string frag_src);
  Shader(std::string path);
  ~Shader();

  void use();

  void set_bool(const char* name, bool value) const;
  void set_int(const char* name, int32_t value) const;
  void set_float(const char* name, float value) const;

  uint32_t id();
};