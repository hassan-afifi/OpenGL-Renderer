#version 430

layout( location = 0 ) in vec3 inputObjectSpacePosition;
layout( location = 1 ) in vec3 inputColor;

out vec3 color;

uniform mat4 world;
uniform mat4 viewProj;
uniform vec3 pickedColor;
uniform float colorPercent;

void main()
{
	gl_Position  = viewProj * world * vec4( inputObjectSpacePosition, 1.0 );
	color = (colorPercent * inputColor) + ((1-colorPercent) * pickedColor);
}