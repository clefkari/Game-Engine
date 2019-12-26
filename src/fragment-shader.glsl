#version 450 core

in vec4 position;
out vec4 fColor;

void main() {
    fColor = vec4(position.x/position.y, position.y/position.x, .5, 1);
}
