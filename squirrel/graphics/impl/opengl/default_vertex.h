namespace Squirrel::GFX::OpenGL
{
// Vertex Shader source
const char* default_vertex_src = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 viewProjectionMatrix;
uniform mat4 transform;
uniform vec4 color;

out vec4 vertexColor;

void main()
{
    gl_Position = viewProjectionMatrix * transform * vec4(aPos, 1.0);
    vertexColor = color;
}
)glsl";
} // namespace Squirrel::GFX::OpenGL
