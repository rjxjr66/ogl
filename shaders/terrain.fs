#version 330

in vec2 TexCoord0;
in vec3 Normal0;
in float Height0;

uniform vec3 gLightDirection;
uniform sampler2D diffuseTexture;

vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
vec4 diffuse = vec4(0.8, 0.8, 0.8, 1.0);


void main()
{
    vec4 DiffuseColor = diffuse * max(dot(normalize(gLightDirection), normalize(Normal0)), 0);

    vec4 color = vec4(0,0.2,1,1);
    color = texture2D(diffuseTexture, TexCoord0);
    gl_FragColor = color;
}
