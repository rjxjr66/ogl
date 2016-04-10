#version 330

in vec3 WorldPos0;
in vec2 TexCoord0;
in vec3 Normal0;

uniform vec3 gLightDirection;

vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
vec4 diffuse = vec4(0.8, 0.8, 0.8, 1.0);
vec4 specular = vec4(1.0, 1.0, 1.0, 1.0);
float shininess = 128.0;


void main()
{
    vec4 DiffuseColor = diffuse * max(dot(normalize(gLightDirection), normalize(Normal0)), 0);

    gl_FragColor = vec4(0.5, 0.1, 0.8, 1) * ( ambient * 0.5 + DiffuseColor  );
}
