#version 330

attribute vec3 Position;

uniform mat4 gWorld;
uniform mat4 gView;
uniform mat4 gProj;
uniform mat4 gWVP;

out vec4 Color;

void main()
{
    //gl_Position = gProj * gView * gWorld * vec4(Position, 1.0);
    gl_Position = vec4(Position, 1.0) * gWorld * gView * gProj;
    Color = vec4(clamp(Position, 0.0, 1.0), 1.0);
}
