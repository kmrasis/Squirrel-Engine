namespace Squirrel::GFX::OpenGL
{
// Fragment Shader source
const char* default_fragment_src = R"glsl(
#version 330 core
in vec3 vertexColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(vertexColor, 1.0);
}
)glsl";
} // namespace Squirrel::GFX::OpenGL
