#version 330 core
layout (points) in;
//layout (line_strip, max_vertices = 40) out;
layout (triangle_strip, max_vertices = 40) out;

uniform float angle;
uniform float size;

const float PI = 3.1415926;
const float multiplier = (PI * 2) / 360.0;

void main()
{
	float rClose = gl_in[0].gl_Position.y;
	float rFar = rClose + 0.02;

	float currentAngle = (angle - (size / 2.0)) * multiplier;
	float stepSize = (size / 20.0) * multiplier;

	for (int i = 0; i < 20; i++)
	{
		// draw close
		gl_Position = vec4(cos(currentAngle) * rClose, sin(currentAngle) * rClose, 0.0, 1.0);
		EmitVertex();
	
		// draw far
		gl_Position = vec4(cos(currentAngle) * rFar, sin(currentAngle) * rFar, 0.0, 1.0);
		EmitVertex();

		currentAngle = currentAngle + stepSize;
	}
	
	EndPrimitive();
}
