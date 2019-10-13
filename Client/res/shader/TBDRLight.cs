#version 430 core

#define LOCAL_SIZE_X 16
#define LOCAL_SIZE_Y 16
#define LOCAL_SIZE_Z 1

layout(local_size_x = LOCAL_SIZE_X, local_size_y = LOCAL_SIZE_Y, local_size_z = LOCAL_SIZE_Z) in;

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

struct PointLight
{
	vec3 lightPos;
	vec4 lightColor;

	float constant;
	float linear;
	float quadratic;
};

#define POINT_LIGHT_COUNT 4
uniform PointLight pointLight[POINT_LIGHT_COUNT];

uniform sampler2D GDepth;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 invProjection;

shared uint min_depth;
shared uint max_depth;

float GetViewDepth(float depth)
{
	vec4 tmp_position = invProjection * vec4(0.0, 0.0, depth * 2.0 - 1.0, 1.0);
	tmp_position /= tmp_position.w;
	return -tmp_position.z;
}

bool CheckIntersect(vec3 sphereCenter, float sphereRadius)
{
	vec2 tmp_origin = vec2(gl_WorkGroupID.xy) / vec2(gl_NumWorkGroups.xy);
	vec2 tmp_step = vec2(1.0) / vec2(gl_NumWorkGroups.xy);

	vec4 tmp_clipMin = projection * vec4(0.0, 0.0, -float(min_depth), 1.0);
	tmp_clipMin /= tmp_clipMin.w;
	vec4 tmp_clipMax = projection * vec4(0.0, 0.0, -float(max_depth), 1.0);
	tmp_clipMax /= tmp_clipMax.w;

	// 8 screen space point
	vec3 tmp_point[8];
	tmp_point[0] = vec3(tmp_origin, (tmp_clipMin.z + 1.0) / 2.0);
	tmp_point[1] = vec3(tmp_origin + vec2(tmp_step.x, 0.0), (tmp_clipMin.z + 1.0) / 2.0);
	tmp_point[2] = vec3(tmp_origin + tmp_step.xy, (tmp_clipMin.z + 1.0) / 2.0);
	tmp_point[3] = vec3(tmp_origin + vec2(0.0, tmp_step.y), (tmp_clipMin.z + 1.0) / 2.0);
	tmp_point[4] = vec3(tmp_origin, (tmp_clipMax.z + 1.0) / 2.0);
	tmp_point[5] = vec3(tmp_origin + vec2(tmp_step.x, 0.0), (tmp_clipMax.z + 1.0) / 2.0);
	tmp_point[6] = vec3(tmp_origin + tmp_step.xy, (tmp_clipMax.z + 1.0) / 2.0);
	tmp_point[7] = vec3(tmp_origin + vec2(0.0, tmp_step.y), (tmp_clipMax.z + 1.0) / 2.0);

	// 8 view space point
	for (int i = 0; i < 8; ++i)
	{
		vec4 tmp_viewPos = invProjection * vec4(tmp_point[i] * 2.0 - 1.0, 1.0);
		tmp_viewPos /= tmp_viewPos.w;
		tmp_point[i] = tmp_viewPos.xyz;
	}

	// aabb box
	vec3 tmp_min = tmp_point[0];
	vec3 tmp_max = tmp_point[0];
	for (int i = 1; i < 8; ++i)
	{
		tmp_min = min(tmp_min, tmp_point[i]);
		tmp_max = max(tmp_max, tmp_point[i]);
	}
	vec3 tmp_center = (tmp_min + tmp_max) / 2.0;
	vec3 tmp_half = abs(tmp_max - tmp_min) / 2.0;

	// intersect test
	vec4 tmp_viewLightCenter = view * vec4(sphereCenter, 1.0);
	tmp_viewLightCenter /= tmp_viewLightCenter.w;
	vec3 tmp_delta = max(vec3(0.0), abs(tmp_center - tmp_viewLightCenter.xyz) - tmp_half);
	float tmp_distSq = dot(tmp_delta, tmp_delta);

	return tmp_distSq <= sphereRadius * sphereRadius;
}

void main()
{
	uint tmp_groupID = gl_WorkGroupID.x + gl_WorkGroupID.y * gl_NumWorkGroups.x;
	if (gl_LocalInvocationIndex == 0)
	{
		min_depth = 0x7f7fffff;
		max_depth = 0;

		tile[tmp_groupID].PointLightCount = 0;
	}

	groupMemoryBarrier();

	float tmp_depth = texture(GDepth, vec2(gl_GlobalInvocationID.x, gl_GlobalInvocationID.y) / vec2(1280, 720)).r;
	float tmp_viewDepth = GetViewDepth(tmp_depth);

	atomicMin(min_depth, uint(tmp_viewDepth));
	atomicMax(max_depth, uint(tmp_viewDepth));

	groupMemoryBarrier();

	
	uint tmp_totalThreads = gl_WorkGroupSize.x * gl_WorkGroupSize.y;

	for (uint i = gl_LocalInvocationIndex; i < POINT_LIGHT_COUNT; i += tmp_totalThreads)
	{
		bool tmp_intersect = CheckIntersect(pointLight[i].lightPos, 10.0);

		if (tmp_intersect)
		{
			uint tmp_origin = atomicAdd(tile[tmp_groupID].PointLightCount, 1);
			if (tmp_origin < MAX_POINT_LIGHT_COUNT)
			{
				tile[tmp_groupID].PointLightIndices[tmp_origin] = i;
			}
		}
	}
}
