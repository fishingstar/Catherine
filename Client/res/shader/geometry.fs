#version 330 core

in vec2 Texcoord;

out vec4 FragColor;

struct DirectionalLight
{
	vec3 lightDir;
	vec4 lightColor;
};

uniform DirectionalLight dirLight;

uniform float ambient;
uniform vec3 viewPos;

uniform sampler2D GColor;
uniform sampler2D GNormal;
uniform sampler2D GMask;
uniform sampler2D GDepth;

uniform mat4 invProjection;
uniform mat4 invView;

vec4 GetWorldPosFromDepth(float depth)
{
	float tmp_depth = depth * 2.0f - 1.0f;
	vec4 tmp_clipPosition = vec4(Texcoord.xy * 2.0f - 1.0f, tmp_depth, 1.0f);
	vec4 tmp_viewPosition = invProjection * tmp_clipPosition;
	tmp_viewPosition /= tmp_viewPosition.w;
	vec4 tmp_worldPosition = invView * tmp_viewPosition;
	return tmp_worldPosition;
}

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
	vec4 tmp_color = texture(GColor, Texcoord);
	vec3 tmp_diffuse = pow(tmp_color.rgb, vec3(2.2));
	float tmp_shadow = tmp_color.a;
	vec3 tmp_normal = normalize(texture(GNormal, Texcoord).xyz);
	vec4 tmp_mask = texture(GMask, Texcoord);
	float tmp_depth = texture(GDepth, Texcoord).r;
	
	// get world position from depth buffer
	vec4 tmp_worldPosition = GetWorldPosFromDepth(tmp_depth);
	vec3 tmp_viewDir = normalize(viewPos.xyz - tmp_worldPosition.xyz);

	vec3 tmp_dirColor = calculateDirLight(dirLight, tmp_viewDir, tmp_normal.xyz, tmp_diffuse.rgb, tmp_mask);

	vec3 tmp_result = ambient * tmp_diffuse.rgb + tmp_dirColor * tmp_shadow * 2.0f;
	tmp_result.rgb = pow(tmp_result.rgb, vec3(1.0 / 2.2));

	FragColor = vec4(tmp_result, 1.0f);
}
