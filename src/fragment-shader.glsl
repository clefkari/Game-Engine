#version 450 core

in vec4 color;
out vec4 fColor;

void main() {
    //fColor = 0.5 * (color + vec4(0, 0, 1, 1));
    fColor = vec4(1, 1, 0, 1);
}
