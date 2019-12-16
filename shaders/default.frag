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
layout(location = 10) in float ldistance;
layout(location = 11) in float cosAlpha;

layout(location = 0) out vec4 outColor;

void main()
{
	float distance = 1.3;
	//float cosTheta = clamp(dot(normalize(fragNormal), normalize(lightdir)), 0, 1);
    vec4 baseColor = texture(texSampler, fragTexCoord);
	vec4 lightcolor = cosTheta * _LIGHTCOLOR;
	vec4 MaterialAmbientColor = vec4(0.1,0.1,0.1, 1) * baseColor;
    outColor = MaterialAmbientColor + baseColor * lightcolor * intensity  / (ldistance*ldistance);
	//outColor +=  baseColor * lightcolor * intensity * pow(cosAlpha,5) / (distance*distance);
	outColor.x += red;
	outColor.y += green;
	outColor.z += blue;
}
