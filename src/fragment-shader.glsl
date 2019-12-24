#version 450 core

in vec4 color;
out vec4 fColor;

void main() {
    fColor = 0.5 * (color + vec4(1, 1, 1, 1));
}
