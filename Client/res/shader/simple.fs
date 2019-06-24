#version 330 core

in vec2 Texcoord;
in vec3 WorldNormal;
in vec3 WorldPos;

out vec4 FragColor;

uniform vec4 lightColor;
uniform float ambient;
uniform vec3 viewPos;
uniform vec4 lightPos;

uniform sampler2D diffuse1;
uniform sampler2D diffuse2;

void main()
{
	vec3 tmp_normal = normalize(WorldNormal);
	vec3 tmp_lightDir = normalize(lightPos.xyz - WorldPos);
	vec3 tmp_viewDir = normalize(viewPos.xyz - WorldPos);
	vec3 tmp_half = normalize(tmp_lightDir + tmp_viewDir);

	float tmp_diffuse = max(0.0, dot(tmp_normal, tmp_lightDir));
	float tmp_specular = pow(max(0.0, dot(tmp_half, tmp_normal)), 32) * 0.5;

	vec3 tmp_color1 = texture(diffuse1, Texcoord).xyz;
	vec3 tmp_color2 = texture(diffuse2, Texcoord).xyz;

	vec3 tmp_color = (ambient + tmp_diffuse + tmp_specular) * tmp_color1 * lightColor.rgb;

	FragColor = vec4(tmp_color, 1.0f);
}
