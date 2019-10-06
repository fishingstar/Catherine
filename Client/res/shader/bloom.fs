#version 330 core

in vec2 Texcoord;

out vec4 FragColor;

uniform int stage;
uniform sampler2D Tex0;
uniform sampler2D Origin;

uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{
	if (stage == 0)
	{
		vec3 tmp_src = texture(Tex0, Texcoord).rgb;
		float tmp_grayscale = dot(tmp_src, vec3(0.2126, 0.7152, 0.0722));
		FragColor = vec4(step(1.0, tmp_grayscale) * (tmp_src / tmp_grayscale), 1.0);
	}
	else if (stage == 1)
	{
		vec2 tex_offset = 1.0 / textureSize(Tex0, 0); // gets size of single texel
	    vec3 result = texture(Tex0, Texcoord).rgb * weight[0]; // current fragment's contribution
        for(int i = 1; i < 5; ++i)
        {
            result += texture(Tex0, Texcoord + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(Tex0, Texcoord - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
	    FragColor = vec4(result, 1.0);
	}
	else if (stage == 2)
	{
		vec2 tex_offset = 1.0 / textureSize(Tex0, 0); // gets size of single texel
	    vec3 result = texture(Tex0, Texcoord).rgb * weight[0]; // current fragment's contribution
        for(int i = 1; i < 5; ++i)
        {
            result += texture(Tex0, Texcoord + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(Tex0, Texcoord - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
	    FragColor = vec4(result, 1.0);
	}
	else if (stage == 3)
	{
		vec3 tmp_bloom = texture(Tex0, Texcoord).rgb;
		vec3 tmp_origin = texture(Origin, Texcoord).rgb;
		vec3 tmp_result = tmp_origin + tmp_bloom;
		FragColor = vec4(tmp_result, 1.0);
	}
	else
	{
		FragColor = vec4(0.0, 0.0, 0.0, 0.0);
	}
}
