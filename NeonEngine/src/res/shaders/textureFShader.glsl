#version 330 core
in vec4 fcolor;
in vec2 texFrag;

uniform sampler2D tex;

out vec4 out_FragColor;

void main() 
{ 
  out_FragColor = fcolor * texture(tex, texFrag);
}