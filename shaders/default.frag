#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;
layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in float time;
layout(location = 3) in float red;
layout(location = 4) in float green;
layout(location = 5) in float blue;

layout(location = 0) out vec4 outColor;

void main()
{
    vec3 lightVector = vec3(1, 0, 1);
    float cosTheta = dot(fragNormal, lightVector);
	vec4 lightCol = vec4(1, 1, 1, 1);
    vec3 lightVector2 = vec3(-1, 0, -1);
    float cosTheta2 = dot( fragNormal,lightVector2);
    vec4 baseColor = texture(texSampler, fragTexCoord);
	//baseColor = vec4(abs(sin(0.5)), 0.0, 0.0, 1.0);
    outColor = baseColor  + baseColor * cosTheta;// * cosTheta2;
	//outColor.x *= red;
	//outColor.y *= green;
	//outColor.z *= blue;
    //outColor = _COLOR * outColor;
}
