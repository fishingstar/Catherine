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

uniform sampler2D albedo;
uniform sampler2D normalmap;
uniform sampler2D metallicmap;
uniform sampler2D roughnessmap;
uniform sampler2D shadowmap;

const float PI = 3.14159265359;

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

vec3 PBRLightingImp(vec3 albedo, vec3 radiance, vec3 V, vec3 N, vec3 L, float roughness, float metallic)
{
	// base reflectivity
	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);

	vec3 H = normalize(V + L);
	float HdotV = max(dot(H, V), 0.0);
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, L), 0.0);

	float NDF = DistributionGGX(N, H, roughness);
	float G = GeometrySmith(N, V, L, roughness);
	vec3 F = fresnelSchlick(HdotV, F0);

	vec3 ks = F;
	vec3 kd = vec3(1.0) - ks;
	kd *= 1.0 - metallic;

	vec3 numerator = NDF * G * F;
	float denominator = 4.0 * NdotV * NdotL;
	vec3 specular = numerator / max(denominator, 0.001);

	vec3 tmp_color = (kd * albedo / PI + specular) * radiance * NdotL;

	return tmp_color;
}

vec3 PBRLighting(vec3 albedo, vec3 V, vec3 N, float roughness, float metallic, float shadow)
{
	vec3 tmp_color = vec3(0.0);

	// directional light
	vec3 tmp_dirLight = normalize(-dirLight.lightDir.xyz);
	vec3 tmp_dirColor = dirLight.lightColor.rgb;
	tmp_color += PBRLightingImp(albedo, tmp_dirColor, V, N, tmp_dirLight, roughness, metallic) * shadow;

	// point light
	for (int i = 0; i < POINT_LIGHT_COUNT; ++i)
	{
		vec3 tmp_pointOffset = pointLight[i].lightPos - WorldPos;
		vec3 tmp_pointDir = normalize(tmp_pointOffset);
		float tmp_distance = length(tmp_pointOffset);
		// atten = 1 / (a*x*x + b*x + c)
		float tmp_attenuation = 1.0 / (pointLight[i].constant + pointLight[i].linear * tmp_distance + pointLight[i].quadratic * tmp_distance * tmp_distance);
		vec3 tmp_pointColor = pointLight[i].lightColor.rgb * tmp_attenuation;
		tmp_color += PBRLightingImp(albedo, tmp_pointColor, V, N, tmp_pointDir, roughness, metallic);
	}

	// spot light
	vec3 tmp_spotOffset = spotLight.lightPos - WorldPos;
	vec3 tmp_spotDir = normalize(tmp_spotOffset);
	float tmp_spotDistance = length(tmp_spotOffset);
	// atten = 1 / (a*x*x + b*x + c)
	float tmp_spotAtten = 1.0 / (spotLight.constant + spotLight.linear * tmp_spotDistance + spotLight.quadratic * tmp_spotDistance * tmp_spotDistance);
	float tmp_cos = dot(tmp_spotDir, normalize(-spotLight.lightDir)); 
    float tmp_epsilon = spotLight.innerCutoff - spotLight.outerCutoff;
    float tmp_intensity = clamp((tmp_cos - spotLight.outerCutoff) / tmp_epsilon, 0.0, 1.0);
    vec3 tmp_spotColor = spotLight.lightColor.rgb * tmp_spotAtten * tmp_intensity;
    tmp_color += PBRLightingImp(albedo, tmp_spotColor, V, N, tmp_spotDir, roughness, metallic);

	return tmp_color;
}

void main()
{
	vec3 tmp_normal = normalize(WorldNormal);
	vec3 tmp_tangent = normalize(WorldTangent);
	vec3 tmp_binormal = normalize(WorldBinormal);
	vec3 tmp_viewDir = normalize(viewPos.xyz - WorldPos);

	vec3 tmp_albedo = pow(texture(albedo, Texcoord).xyz, vec3(2.2));
	vec3 tmp_normaldir = texture(normalmap, Texcoord).xyz;
	tmp_normaldir = normalize(tmp_normaldir * 2.0 - 1.0);
	tmp_normaldir = normalize(mat3(tmp_tangent, tmp_binormal, tmp_normal) * tmp_normaldir);
	float tmp_metallic = texture(metallicmap, Texcoord).r;
	float tmp_roughness = texture(roughnessmap, Texcoord).r;

	// shadow
	vec4 tmp_lightClipPos = lightprojection * lightview * vec4(WorldPos, 1.0);
	vec4 tmp_lightScreenPos = (tmp_lightClipPos.xyzw / tmp_lightClipPos.w + 1.0) / 2.0;
	float tmp_depth = texture(shadowmap, tmp_lightScreenPos.xy).x + 0.01;
	float tmp_shadow = 1.0 - step(tmp_lightScreenPos.z, 1.0) * step(tmp_depth, tmp_lightScreenPos.z);

	vec3 tmp_pbrColor = PBRLighting(tmp_albedo, tmp_viewDir, tmp_normaldir, tmp_roughness, tmp_metallic, tmp_shadow);
	vec3 tmp_ambient = ambient * tmp_albedo * 1.0;
	vec3 tmp_result = tmp_ambient + tmp_pbrColor;

	tmp_result = tmp_result / (tmp_result + vec3(1.0));
	tmp_result = pow(tmp_result, vec3(1.0 / 2.2));

	FragColor = vec4(tmp_result, 1.0f);
}
