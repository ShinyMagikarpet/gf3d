#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;
layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(set = 3, binding = 0) uniform Transparency{
	float value;
	vec2 pos;
} transparency;

void main()
{
    vec3 lightVector = vec3(1,0,-1);
    float cosTheta = sin(dot( fragNormal * 2,lightVector )) + 0.7;
    vec3 lightVector2 = vec3(-1, 0, 1);
    float cosTheta2 = sin(dot( fragNormal * 2,lightVector2 )) + 0.7;
    vec4 baseColor = texture(texSampler, fragTexCoord * sin(2));
    outColor = baseColor + cosTheta * cosTheta2;
    vec4 _COLOR = vec4(1, 0, 0.5, 1);
    outColor = _COLOR * outColor;
	//if(transparency.value == 1){
	//	outColor.w = transparency.value;
	//}
    //outColor.w = transparency.value;
}
