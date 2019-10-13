#version 430 core

#define POINT_LIGHT_COUNT 4

in vec2 Texcoord;

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

uniform sampler2D GColor;
uniform sampler2D GNormal;
uniform sampler2D GMask;
uniform sampler2D GDepth;
uniform sampler2D brdfLUT;
uniform samplerCube prefilterMap;

uniform mat4 invProjection;
uniform mat4 invView;

const uint MAX_POINT_LIGHT_COUNT = 4;
const uint MAX_SPOT_LIGHT_COUNT = 4;

struct TileLightList
{
	uint PointLightCount;
    uint PointLightIndices[MAX_POINT_LIGHT_COUNT];
    uint SpotLightCount;
    uint SpotLightIndices[MAX_SPOT_LIGHT_COUNT];
};

layout(std430, binding = 0) buffer LightList
{
    TileLightList tile[];
};

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

vec3 PBRLighting(vec3 albedo, vec3 worldPos, vec3 V, vec3 N, float roughness, float metallic, float shadow)
{
	vec3 tmp_color = vec3(0.0);

	// directional light
	vec3 tmp_dirLight = normalize(-dirLight.lightDir.xyz);
	vec3 tmp_dirColor = dirLight.lightColor.rgb * 2.7;
	tmp_color += PBRLightingImp(albedo, tmp_dirColor, V, N, tmp_dirLight, roughness, metallic) * shadow;

	// point light

	uvec2 tmp_tileTexcoord = uvec2(Texcoord.xy * vec2(80.0, 45.0));
	tmp_tileTexcoord = clamp(tmp_tileTexcoord, uvec2(0, 0), uvec2(79, 44));
	uint tmp_index = tmp_tileTexcoord.x + tmp_tileTexcoord.y * 80;
	uint tmp_count = min(tile[tmp_index].PointLightCount, MAX_POINT_LIGHT_COUNT);
	for (uint i = 0; i < tmp_count; ++i)
	{
		vec3 tmp_pointOffset = pointLight[tile[tmp_index].PointLightIndices[i]].lightPos - worldPos;
		vec3 tmp_pointDir = normalize(tmp_pointOffset);
		float tmp_distance = length(tmp_pointOffset);
		// atten = 1 / (a*x*x + b*x + c)
		float tmp_attenuation = 1.0 / (pointLight[i].constant + pointLight[i].linear * tmp_distance + pointLight[i].quadratic * tmp_distance * tmp_distance);
		vec3 tmp_pointColor = pointLight[i].lightColor.rgb * tmp_attenuation;
		tmp_color += PBRLightingImp(albedo, tmp_pointColor, V, N, tmp_pointDir, roughness, metallic);
	}

	// spot light
	vec3 tmp_spotOffset = spotLight.lightPos - worldPos;
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

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 EnvBRDFApprox(vec3 SpecularColor, float Roughness, float NoV)
{
	// [ Lazarov 2013, "Getting More Physical in Call of Duty: Black Ops II" ]
	// Adaptation to fit our G term.
	vec4 c0 = vec4(-1, -0.0275, -0.572, 0.022);
	vec4 c1 = vec4(1, 0.0425, 1.04, -0.04);
	vec4 r = Roughness * c0 + c1;
	float a004 = min( r.x * r.x, exp2( -9.28 * NoV ) ) * r.x + r.y;
	vec2 AB = vec2( -1.04, 1.04 ) * a004 + r.zw;

	// Anything less than 2% is physically impossible and is instead considered to be shadowing
	// Note: this is needed for the 'specular' show flag to work, since it uses a SpecularColor of 0
	AB.y *= clamp(50.0 * SpecularColor.g, 0.0, 1.0);

	return SpecularColor * AB.x + AB.y;
}

vec3 IBLLighting(vec3 albedo, vec3 V, vec3 N, float roughness, float metallic)
{
	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);
	vec3 F = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness);

	vec3 ks = F;
	vec3 kd = 1.0 - ks;
	kd *= 1.0 - metallic;

	vec3 irradiance = texture(prefilterMap, N).rgb;
	vec3 diffuse = irradiance * albedo;

	// const float MAX_REFLECTION_LOD = 4.0;
	// vec3 prefilteredColor = textureLod(prefilterMap, R,  roughness * MAX_REFLECTION_LOD).rgb;
	vec3 R = reflect(-V, N);
	vec3 prefilteredColor = texture(prefilterMap, R).rgb;   
	vec2 envBRDF = texture(brdfLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
	vec3 specular = prefilteredColor * (F * envBRDF.x + envBRDF.y);
	// vec3 approx = EnvBRDFApprox(F, roughness, max(dot(N, V), 0.0));
	// specular = prefilteredColor * approx;
	
	float ao = 1.0;
	vec3 ambient = (kd * diffuse + specular) * ao;

	return ambient;
}

vec4 GetWorldPosFromDepth(float depth)
{
	float tmp_depth = depth * 2.0f - 1.0f;
	vec4 tmp_clipPosition = vec4(Texcoord.xy * 2.0f - 1.0f, tmp_depth, 1.0f);
	vec4 tmp_viewPosition = invProjection * tmp_clipPosition;
	tmp_viewPosition /= tmp_viewPosition.w;
	vec4 tmp_worldPosition = invView * tmp_viewPosition;
	return tmp_worldPosition;
}

void main()
{
	// extract albedo and shadow factor
	vec4 tmp_color = texture(GColor, Texcoord);
	vec3 tmp_albedo = pow(tmp_color.rgb, vec3(2.2));
	float tmp_shadow = tmp_color.a;
	// extract normal
	vec3 tmp_normal = normalize(texture(GNormal, Texcoord).xyz);
	// extract metallic and roughness
	vec4 tmp_mask = texture(GMask, Texcoord);
	float tmp_metallic = tmp_mask.r;
	float tmp_roughness = tmp_mask.g;
	// extract depth
	float tmp_depth = texture(GDepth, Texcoord).r;
	
	// get world position from depth buffer
	vec4 tmp_worldPosition = GetWorldPosFromDepth(tmp_depth);
	vec3 tmp_viewDir = normalize(viewPos.xyz - tmp_worldPosition.xyz);

	// pbr calculation
	vec3 tmp_pbrColor = PBRLighting(tmp_albedo, tmp_worldPosition.xyz, tmp_viewDir, tmp_normal, tmp_roughness, tmp_metallic, tmp_shadow);
	vec3 tmp_iblColor = IBLLighting(tmp_albedo, tmp_viewDir, tmp_normal, tmp_roughness, tmp_metallic);
	vec3 tmp_result = tmp_pbrColor + tmp_iblColor * ambient;

	// uvec2 tmp_tileTexcoord = uvec2((Texcoord.xy - vec2(0.01)) * vec2(80.0, 45.0));
	// tmp_tileTexcoord = clamp(tmp_tileTexcoord, uvec2(0, 0), uvec2(79, 44));
	// uint tmp_index = tmp_tileTexcoord.x + tmp_tileTexcoord.y * 80;
	// float tmp_data = float(tile[tmp_index].PointLightCount);

	// output shading result
	FragColor = vec4(tmp_result, 1.0f);
}
