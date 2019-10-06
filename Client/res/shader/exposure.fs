#version 330 core

in vec2 Texcoord;

out vec4 FragColor;

uniform sampler2D Tex0;

// ACES Filmic Tone Mapping Curve
//
// Adapted from code by Krzysztof Narkowicz
// https://knarkowicz.wordpress.com/2016/01/06/
// aces-filmic-tone-mapping-curve/
vec3 ACESFilm(vec3 x)
{
    float tA = 2.51f;
    float tB = 0.03f;
    float tC = 2.43f;
    float tD = 0.59f;
    float tE = 0.14f;
    return clamp((x * (tA * x + tB)) / (x * (tC * x + tD) + tE), 0.0, 1.0);
}

void main()
{
	vec3 tmp_color = texture(Tex0, Texcoord).rgb;
	vec3 tmp_result = ACESFilm(tmp_color);
	tmp_result = pow(tmp_result, vec3(1.0 / 2.2));
	FragColor = vec4(tmp_result, 0.0);
}
