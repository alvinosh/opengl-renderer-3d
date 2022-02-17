#include "mesh.hpp"
#include "vertex.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Mesh::Mesh(const char* path)
  : count(0)
{
  std::vector<glm::vec3> pos;
  std::vector<glm::vec3> normal;
  std::vector<glm::vec2> tex_pos;

  std::vector<Vertex> verticies;

  std::vector<uint32_t> indicies = {};

  std::ifstream file;
  file.open(path);

  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::stringstream sstream(line);
      std::string token, val1, val2, val3;
      sstream >> token >> val1 >> val2 >> val3;
      if (token.compare(std::string("o")) == 0) {
        name = val1;
      }

      if (token.compare(std::string("v")) == 0) {
        glm::vec3 temp(std::stof(val1), std::stof(val2), std::stof(val3));
        pos.push_back(temp);
      }

      if (token.compare(std::string("vt")) == 0) {
        glm::vec2 temp(std::stof(val1), std::stof(val2));
        tex_pos.push_back(temp);
      }

      if (token.compare(std::string("vn")) == 0) {
        glm::vec3 temp(std::stof(val1), std::stof(val2), std::stof(val3));
        normal.push_back(temp);
      }

      if (token.compare(std::string("f")) == 0) {
        std::string value;
        std::replace(val1.begin(), val1.end(), '/', ' ');
        std::replace(val2.begin(), val2.end(), '/', ' ');
        std::replace(val3.begin(), val3.end(), '/', ' ');
        std::stringstream s1(val1);
        std::stringstream s2(val2);
        std::stringstream s3(val3);

        Vertex ver1;
        Vertex ver2;
        Vertex ver3;

        uint32_t v, t, n;

        s1 >> v >> t >> n;
        ver1.position = pos[v - 1];
        ver1.texture = tex_pos[t - 1];
        ver1.normal = normal[n - 1];

        s2 >> v >> t >> n;
        ver2.position = pos[v - 1];
        ver2.texture = tex_pos[t - 1];
        ver2.normal = normal[n - 1];

        s3 >> v >> t >> n;
        ver3.position = pos[v - 1];
        ver3.texture = tex_pos[t - 1];
        ver3.normal = normal[n - 1];

        verticies.push_back(ver1);
        verticies.push_back(ver2);
        verticies.push_back(ver3);

        indicies.push_back(count);
        indicies.push_back(count + 1);
        indicies.push_back(count + 2);

        count += 3;
      }
    }
  }

  vb.SetData(verticies);
  VertexArrayLayout layout;
  layout.push<float>(3);
  layout.push<float>(3);
  layout.push<float>(2);
  va.AddBuffer(vb, layout);
  ib.SetData(indicies);

  file.close();
}
