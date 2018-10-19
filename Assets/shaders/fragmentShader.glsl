#version 330 core

//#extension GL_ARB_separate_shader_objects : enable
layout(location = 0) out vec4 color;
uniform vec4 u_Color;

void main()
{
	color = u_Color;
}