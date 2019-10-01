#version 330 core

#define POINT_LIGHT_COUNT 4

in vec2 Texcoord;
in vec3 WorldNormal;
in vec3 WorldTangent;
in vec3 WorldBinormal;
in vec3 WorldPos;

out vec4 FragColor;

struct DirectionalLight
{
	vec3 lightDir;
	vec4 lightColor;
};

struct PointLight
{
	vec3 lightPos;
	vec4 lightColor;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 lightPos;
	vec4 lightColor;
	vec3 lightDir;

	float innerCutoff;
	float outerCutoff;

	float constant;
	float linear;
	float quadratic;
};

uniform DirectionalLight dirLight;
uniform PointLight pointLight[POINT_LIGHT_COUNT];
uniform SpotLight spotLight;

uniform float ambient;
uniform vec3 viewPos;
uniform mat4 lightview;
uniform mat4 lightprojection;

uniform sampler2D diffuse;
uniform sampler2D normalmap;
uniform sampler2D specularmap;
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

vec3 calculatePointLight(PointLight param_Light, vec3 param_ViewDir, vec3 param_Normal, vec3 param_Pos, vec3 param_Diffuse, vec4 param_Specular)
{
	vec3 tmp_offset = param_Light.lightPos - param_Pos;
	vec3 tmp_lightDir = normalize(tmp_offset);
	vec3 tmp_half = normalize(tmp_lightDir + param_ViewDir);
	float tmp_distance = length(tmp_offset);

	float tmp_diffuse = max(0.0, dot(param_Normal, tmp_lightDir));
	float tmp_specular = pow(max(0.0, dot(tmp_half, param_Normal)), 32);

	// atten = 1 / (a*x*x + b*x + c)
	float tmp_attenuation = 1.0 / (param_Light.constant + param_Light.linear * tmp_distance + param_Light.quadratic * tmp_distance * tmp_distance);

	vec3 tmp_color = (tmp_diffuse * param_Diffuse + tmp_specular * param_Specular.rgb * param_Specular.w) * tmp_attenuation * param_Light.lightColor.rgb;

	return tmp_color;
}

vec3 calculateSpotLight(SpotLight param_Light, vec3 param_ViewDir, vec3 param_Normal, vec3 param_Pos, vec3 param_Diffuse, vec4 param_Specular)
{
	vec3 tmp_offset = param_Light.lightPos - param_Pos;
	vec3 tmp_lightDir = normalize(tmp_offset);
	vec3 tmp_half = normalize(tmp_lightDir + param_ViewDir);
	float tmp_distance = length(tmp_offset);

	float tmp_diffuse = max(0.0, dot(param_Normal, tmp_lightDir));
	float tmp_specular = pow(max(0.0, dot(tmp_half, param_Normal)), 32);

	// atten = 1 / (a*x*x + b*x + c)
	float tmp_attenuation = 1.0 / (param_Light.constant + param_Light.linear * tmp_distance + param_Light.quadratic * tmp_distance * tmp_distance);

	float tmp_cos = dot(tmp_lightDir, normalize(-param_Light.lightDir)); 
    float tmp_epsilon = param_Light.innerCutoff - param_Light.outerCutoff;
    float tmp_intensity = clamp((tmp_cos - param_Light.outerCutoff) / tmp_epsilon, 0.0, 1.0);

    vec3 tmp_color = (tmp_diffuse * param_Diffuse + tmp_specular * param_Specular.rgb * param_Specular.w) * tmp_intensity * tmp_attenuation * param_Light.lightColor.rgb;

	return tmp_color;
}

void main()
{
	vec3 tmp_normal = normalize(WorldNormal);
	vec3 tmp_tangent = normalize(WorldTangent);
	vec3 tmp_binormal = normalize(WorldBinormal);
	vec3 tmp_viewDir = normalize(viewPos.xyz - WorldPos);

	vec3 tmp_diffuse = texture(diffuse, Texcoord).xyz;
	vec3 tmp_normalMap = texture(normalmap, Texcoord).xyz;
	tmp_normalMap = normalize(tmp_normalMap * 2.0 - 1.0);
	tmp_normalMap = normalize(mat3(tmp_tangent, tmp_binormal, tmp_normal) * tmp_normalMap);
	// nanosuit's normal is wrong, turn off
	tmp_normalMap = tmp_normal;
	vec4 tmp_specularmap = texture(specularmap, Texcoord).xyzw;

	// caculate directional light color
	vec3 tmp_dirColor = calculateDirLight(dirLight, tmp_viewDir, tmp_normalMap, tmp_diffuse, tmp_specularmap);

	// calculate point lights color
	vec3 tmp_pointColor = vec3(0.0, 0.0, 0.0);
	for (int i = 0; i < POINT_LIGHT_COUNT; ++i)
	{
		tmp_pointColor += calculatePointLight(pointLight[i], tmp_viewDir, tmp_normalMap, WorldPos, tmp_diffuse, tmp_specularmap);
	}

	// calculate spot light color
	vec3 tmp_spotColor = calculateSpotLight(spotLight, tmp_viewDir, tmp_normalMap, WorldPos, tmp_diffuse, tmp_specularmap);

	// shadow
	vec4 tmp_lightClipPos = lightprojection * lightview * vec4(WorldPos, 1.0);
	vec4 tmp_lightScreenPos = (tmp_lightClipPos.xyzw / tmp_lightClipPos.w + 1.0) / 2.0;
	float tmp_depth = texture(shadowmap, tmp_lightScreenPos.xy).x + 0.01;
	float tmp_shadow = 1.0 - step(tmp_lightScreenPos.z, 1.0) * step(tmp_depth, tmp_lightScreenPos.z);

	vec3 tmp_result = ambient * tmp_diffuse + tmp_dirColor * tmp_shadow * 2.0f;

	FragColor = vec4(tmp_result, 1.0f);
}
