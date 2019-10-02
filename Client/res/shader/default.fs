#version 330 core

in vec3 WorldPos;
in vec3 WorldNormal;

out vec4 FragColor;

struct DirectionalLight
{
	vec3 lightDir;
	vec4 lightColor;
};

uniform DirectionalLight dirLight;

uniform float ambient;

uniform vec3 viewPos;
uniform mat4 lightview;
uniform mat4 lightprojection;

uniform sampler2D shadowmap;

vec3 calculateDirLight(DirectionalLight param_Light, vec3 param_ViewDir, vec3 param_Normal, vec3 param_Diffuse, vec4 param_Specular)
{
	vec3 tmp_lightDir = normalize(-param_Light.lightDir.xyz);
	vec3 tmp_half = normalize(tmp_lightDir + param_ViewDir);

	float tmp_diffuse = max(0.0, dot(param_Normal, tmp_lightDir));
	float tmp_specular = pow(max(0.0, dot(tmp_half, param_Normal)), 32);

	vec3 tmp_color = (tmp_diffuse * param_Diffuse.rgb + tmp_specular * param_Specular.rgb * param_Specular.w) * param_Light.lightColor.rgb;

	return tmp_color;
}

void main()
{
	vec3 tmp_normal = normalize(WorldNormal);
	vec3 tmp_viewDir = normalize(viewPos.xyz - WorldPos);

	vec3 tmp_diffuse = vec3(1.0, 1.0, 1.0);
	// caculate directional light color
	vec3 tmp_dirColor = calculateDirLight(dirLight, tmp_viewDir, tmp_normal, tmp_diffuse, vec4(1.0, 1.0, 1.0, 0.5f));

	// shadow
	vec4 tmp_lightClipPos = lightprojection * lightview * vec4(WorldPos, 1.0);
	vec4 tmp_lightScreenPos = (tmp_lightClipPos.xyzw / tmp_lightClipPos.w + 1.0) / 2.0;
	float tmp_depth = texture(shadowmap, tmp_lightScreenPos.xy).x + 0.01;
	float tmp_shadow = 1.0 - step(tmp_lightScreenPos.z, 1.0) * step(tmp_depth, tmp_lightScreenPos.z);

	vec3 tmp_result = ambient * tmp_diffuse + tmp_dirColor * tmp_shadow * 2.0;
	tmp_result.rgb = pow(tmp_result.rgb, vec3(1.0 / 2.2));

	FragColor = vec4(tmp_result, 1.0f);
}
