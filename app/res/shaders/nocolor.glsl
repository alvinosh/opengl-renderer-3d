//SHADER VERTEX
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.xyz , 1.0);
}

//SHADER FRAGMENT
#version 330 core

out vec4 FragColor;

void main()
{
  FragColor = vec4(0.2,0.5,0.8, 1.0);
}

