//SHADER VERTEX
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor; 

void main()
{
    gl_Position = vec4(aPos.xyz , 1.0);
    ourColor = aColor;
}

//SHADER FRAGMENT
#version 330 core

in vec3 ourColor;
out vec4 FragColor;

void main()
{
  FragColor = vec4(ourColor, 1.0f);
}

