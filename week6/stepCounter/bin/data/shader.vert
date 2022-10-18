attribute vec4 position;
attribute vec4 color;
attribute vec4 normal;
attribute vec2 texcoord;
uniform mat4 modelViewProjectionMatrix;
void main(){
    vec4 pos = modelViewProjectionMatrix * position;
    gl_Position = pos;
}
