#version 450 core

in vec4 position;
out vec4 fColor;

void main() {
    fColor = abs(vec4(vec2(position), 1/pow(1 + position.x*position.y, 2), 1));
}
