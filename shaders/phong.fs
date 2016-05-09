#version 330

in vec2 TexCoord0;
in vec3 Normal0;

uniform vec3 gLightDirection;
uniform sampler2D diffuseTexture;

vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
vec4 diffuse = vec4(0.8, 0.8, 0.8, 1.0);
vec4 specular = vec4(1.0, 1.0, 1.0, 1.0);
float shininess = 128.0;


void main()
{
    vec4 DiffuseColor = diffuse * max(dot(normalize(gLightDirection), normalize(Normal0)), 0);

    gl_FragColor = texture2D(diffuseTexture, TexCoord0) * ( ambient * 0.5 + DiffuseColor  );
}
