//SHADER VERTEX
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal; 
out vec3 FragPos; 

out vec2 v_TexCoord;


void main()
{
  gl_Position = projection * view * model * vec4(aPos , 1.0);
  FragPos = vec3(model * vec4(aPos, 1.0));
  Normal = mat3(transpose(inverse(model))) * aNormal;  
  v_TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}

//SHADER FRAGMENT
#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

uniform vec3 viewPos;

uniform sampler2D u_Texture;

in vec3 Normal;
in vec3 FragPos;

in vec2 v_TexCoord;


out vec4 FragColor;


void main()
{
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * lightColor;

  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos); 

  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  float specularStrength = 0.8;
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
  vec3 specular = specularStrength * spec * lightColor;  

  vec4 texcolor = texture(u_Texture, v_TexCoord);

  vec3 result = (ambient + diffuse + specular) * texcolor.xyz;
  FragColor = vec4(result, 1.0f);
}

