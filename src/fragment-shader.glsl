#version 450 core

in vec4 position;
out vec4 fColor;

void main() {
    fColor = vec4(vec2(position), 1 / pow(position.x+position.y + 1, 2), 1);
}
