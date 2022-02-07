#include "shader.hpp"

std::map<uint32_t, const char*> names = {
  std::make_pair(GL_VERTEX_SHADER, "VERTEX"),
  std::make_pair(GL_FRAGMENT_SHADER, "FRAGMENT")
};

uint32_t
create_program(uint32_t vs, uint32_t fs)
{
  uint32_t shader_program = glCreateProgram();
  GLCALL(glAttachShader(shader_program, fs));
  GLCALL(glAttachShader(shader_program, vs));
  GLCALL(glLinkProgram(shader_program));

  int success;
  char infoLog[512];
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog
              << std::endl;
  }
  glDeleteShader(vs);
  glDeleteShader(fs);

  return shader_program;
}

uint32_t
compile_shader(uint32_t type, std::string source)
{

  assert(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER);

  const char* src = source.c_str();

  uint32_t shader = glCreateShader(type);
  GLCALL(glShaderSource(shader, 1, &src, nullptr));
  GLCALL(glCompileShader(shader));

  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::" << names[type] << "::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  return shader;
}

std::string
parse_shader_file(uint32_t type, const std::string file_path)
{
  bool read = false;
  std::ifstream file(file_path);
  std::stringstream output;
  if (file.is_open()) {
    std::string line;
    while (getline(file, line)) {
      if (line.find("//SHADER") != std::string::npos) {
        if (line.find(names[type]) != std::string::npos) {
          read = true;
        } else {
          read = false;
        }
      } else if (read == true) {
        output << line << "\n";
      }
    }
  }
  return output.str();
}

Shader::Shader(std::string vert_src, std::string frag_src)
{
  uint32_t v_shader = compile_shader(GL_VERTEX_SHADER, vert_src);
  uint32_t f_shader = compile_shader(GL_FRAGMENT_SHADER, frag_src);
  m_id = create_program(v_shader, f_shader);
  glDeleteShader(v_shader);
  glDeleteShader(f_shader);
}

Shader::Shader(std::string path)
{
  std::string f_shader_source = parse_shader_file(GL_FRAGMENT_SHADER, path);
  std::string v_shader_source = parse_shader_file(GL_VERTEX_SHADER, path);

  uint32_t v_shader = compile_shader(GL_VERTEX_SHADER, v_shader_source);
  uint32_t f_shader = compile_shader(GL_FRAGMENT_SHADER, f_shader_source);
  m_id = create_program(v_shader, f_shader);
  glDeleteShader(v_shader);
  glDeleteShader(f_shader);
}

Shader::~Shader()
{
  glDeleteProgram(m_id);
}

void
Shader::use()
{
  GLCALL(glUseProgram(m_id));
}

void
Shader::set_bool(const char* name, bool value) const
{
  GLCALL(glUniform1i(glGetUniformLocation(m_id, name), (int)value));
}

void
Shader::set_int(const char* name, int32_t value) const
{
  GLCALL(glUniform1i(glGetUniformLocation(m_id, name), value));
}

void
Shader::set_float(const char* name, float value) const
{
  GLCALL(glUniform1f(glGetUniformLocation(m_id, name), value));
}

uint32_t
Shader::id()
{
  return m_id;
}
