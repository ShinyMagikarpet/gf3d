#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
	float time;
	float red;
	float green;
	float blue;
} ubo;

out gl_PerVertex
{
    vec4 gl_Position;
};

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 0) out vec3 fragNormal;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out float time;
layout(location = 3) out float red;
layout(location = 4) out float green;
layout(location = 5) out float blue;

void main()
{
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    fragNormal = inNormal;
	fragNormal.x *= sin(ubo.time * fragNormal.z);
    fragTexCoord = inTexCoord;
	time = ubo.time;
	red = ubo.red;
	green = ubo.green;
	blue = ubo.blue;
}
