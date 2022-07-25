#version 330 core
out vec4 FragColor;
 
in vec2 TexCoord;

uniform sampler2D _texture;

void main()
{
    FragColor = texture(_texture, TexCoord);
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);

} 