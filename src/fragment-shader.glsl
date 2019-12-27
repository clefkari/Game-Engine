#version 450 core

in vec4 position;
out vec4 fColor;

void main() {

    // color = (1,1,1) - (x, y, 1/(x+y+1)^2)

    fColor = vec4(1, 1, 1, 0) 
        - abs(vec4(vec2(position), 1/pow(1 + position.x*position.y, 2), 1));
}
