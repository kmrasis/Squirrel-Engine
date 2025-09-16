namespace Squirrel::GFX::OpenGL
{
// Vertex Shader source
const char* default_vertex_src = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 viewProjectionMatrix;
out vec3 vertexColor;

void main()
{
    gl_Position = viewProjectionMatrix * vec4(aPos, 1.0);
    vertexColor = aColor;
}
)glsl";
} // namespace Squirrel::GFX::OpenGL
