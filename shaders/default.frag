#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;
layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in float time;
layout(location = 3) in float red;
layout(location = 4) in float green;
layout(location = 5) in float blue;
layout(location = 6) in vec3 lightdir;
layout(location = 7) in float intensity;
layout(location = 8) in vec4 _LIGHTCOLOR;
layout(location = 9) in float cosTheta;

layout(location = 0) out vec4 outColor;

void main()
{
	float distance = 1.3;
	//float cosTheta = clamp(dot(normalize(fragNormal), normalize(lightdir)), 0, 1);
    vec4 baseColor = texture(texSampler, fragTexCoord);
	vec4 lightcolor = cosTheta * _LIGHTCOLOR;
    outColor = baseColor * lightcolor * intensity;// * cosTheta; * cosTheta2;
	//outColor.x *= red;
	//outColor.y *= green;
	//outColor.z *= blue;
}
