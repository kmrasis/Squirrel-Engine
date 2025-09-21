namespace Squirrel::GFX::OpenGL
{
// Fragment Shader source
const char* default_fragment_src = R"glsl(
#version 330 core
in vec4 vertexColor;
out vec4 FragColor;

void main()
{
    FragColor = vertexColor;
}
)glsl";
} // namespace Squirrel::GFX::OpenGL
