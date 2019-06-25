#version 330 core

#define POINT_LIGHT_COUNT 4

in vec2 Texcoord;
in vec3 WorldNormal;
in vec3 WorldPos;

out vec4 FragColor;

struct DirectionalLight
{
	vec3 lightDir;
	vec3 lightColor;
};

struct PointLight
{
	vec3 lightPos;
	vec3 lightColor;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 lightPos;
	vec3 lightDir;
};

uniform DirectionalLight dirLight;
uniform PointLight pointLight[POINT_LIGHT_COUNT]; 

uniform float ambient;
uniform vec3 viewPos;

uniform sampler2D diffuse1;
uniform sampler2D diffuse2;

vec3 calculateDirLight(DirectionalLight param_Light, vec3 param_ViewDir, vec3 param_Normal)
{
	vec3 tmp_lightDir = normalize(-param_Light.lightDir.xyz);
	vec3 tmp_half = normalize(tmp_lightDir + param_ViewDir);

	float tmp_diffuse = max(0.0, dot(param_Normal, tmp_lightDir));
	float tmp_specular = pow(max(0.0, dot(tmp_half, param_Normal)), 32) * 0.5;

	vec3 tmp_color = (tmp_diffuse + tmp_specular) * param_Light.lightColor.rgb;

	return tmp_color;
}

vec3 calculatePointLight(PointLight param_Light, vec3 param_ViewDir, vec3 param_Normal, vec3 param_Pos)
{
	vec3 tmp_offset = param_Light.lightPos - param_Pos;
	vec3 tmp_lightDir = normalize(tmp_offset);
	vec3 tmp_half = normalize(tmp_lightDir + param_ViewDir);
	float tmp_distance = length(tmp_offset);

	float tmp_diffuse = max(0.0, dot(param_Normal, tmp_lightDir));
	float tmp_specular = pow(max(0.0, dot(tmp_half, param_Normal)), 32) * 0.5;

	float tmp_attenuation = 1.0 / (param_Light.constant + param_Light.linear * tmp_distance + param_Light.quadratic * tmp_distance * tmp_distance);

	vec3 tmp_color = (tmp_diffuse + tmp_specular) * tmp_attenuation * param_Light.lightColor.rgb;

	return tmp_color;
}

vec3 calculateSpotLight()
{
	return vec3(0.0, 0.0, 0.0);
}

void main()
{
	vec3 tmp_normal = normalize(WorldNormal);
	vec3 tmp_viewDir = normalize(viewPos.xyz - WorldPos);

	// caculate directional light color
	vec3 tmp_dirColor = calculateDirLight(dirLight, tmp_viewDir, tmp_normal);

	// calculate point lights color
	vec3 tmp_pointColor = vec3(0.0, 0.0, 0.0);
	for (int i = 0; i < POINT_LIGHT_COUNT; ++i)
	{
		tmp_pointColor += calculatePointLight(pointLight[i], tmp_viewDir, tmp_normal, WorldPos);
	}

	// calculate spot light color
	vec3 tmp_spotColor = calculateSpotLight();

	vec3 tmp_diffuse = texture(diffuse1, Texcoord).xyz;
	vec3 tmp_color2 = texture(diffuse2, Texcoord).xyz;

	vec3 tmp_result = (ambient + tmp_dirColor + tmp_pointColor + tmp_spotColor) * tmp_diffuse;

	FragColor = vec4(tmp_result, 1.0f);
}
