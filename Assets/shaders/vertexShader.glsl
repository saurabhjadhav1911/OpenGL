#version 330 core

//#extension GL_ARB_separate_shader_objects : enable
layout(location = 0) in vec4 position;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
}