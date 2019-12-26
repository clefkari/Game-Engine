#version 450 core

in vec4 position;
out vec4 fColor;

void main() {
    fColor = vec4(sin(position.x), cos(position.y), 1);
}
