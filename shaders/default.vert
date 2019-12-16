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
	vec4 lightcolor;
	vec3 lightdir;
	float intensity;
	vec3 lightpos;
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
layout(location = 6) out vec3 lightdir;
layout(location = 7) out float intensity;
layout(location = 8) out vec4 lightcolor;
layout(location = 9) out float cosTheta;
layout(location = 10) out float ldistance;
layout(location = 11) out float cosAlpha;

void main()
{
	//position of vertex in clip space
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
	//gl_Position.x *= sin(ubo.time * 0.9) + 1.2;
	//World position of vertex
	vec3 Position_worldspace = (ubo.model * vec4(inPosition, 1.0)).xyz;

	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPosition_cameraspace = ( ubo.view * ubo.model * vec4(inPosition, 1.0)).xyz;
	vec3 EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
	vec3 LightPosition_cameraspace = ( ubo.view * vec4(ubo.lightpos, 1)).xyz;
	vec3 LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

	// Normal of the the vertex, in camera space
	vec3 Normal_cameraspace = ( ubo.view * ubo.model * vec4(inNormal, 0)).xyz;

	vec3 n = normalize(Normal_cameraspace);
	vec3 l = normalize(LightDirection_cameraspace);

	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	cosAlpha = max(dot( E,R ), 0.0 );

    fragNormal = inNormal;
	//fragNormal.y *= sin(ubo.time * 0.9) + 1.2;
    fragTexCoord = inTexCoord;
	time = ubo.time;
	red = ubo.red;
	green = ubo.green;
	blue = ubo.blue;
	lightdir = ubo.lightdir;
	intensity = ubo.intensity;
	lightcolor = ubo.lightcolor;
	cosTheta = clamp(dot(n, l), 0, 1);
	ldistance = distance(LightPosition_cameraspace, vertexPosition_cameraspace);
}
