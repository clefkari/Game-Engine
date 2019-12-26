#version 450 core

in vec4 position;
out vec4 fColor;

void main() {
    fColor = vec4(tan(position.x*position.y*90), tan(position.x*position.y*20), sin(30*position.y*position.x), 1);
}
