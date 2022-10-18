#ifdef GL_ES
precision highp float;
precision highp sampler2D;
#endif

uniform float screenHeight;
uniform float screenWidth;
uniform sampler2D chalkImg;
uniform sampler2D fbo;
uniform vec2 resolution;

void main() {
    vec2 pos = gl_FragCoord.xy;
    pos.y = screenHeight - pos.y;
    vec2 normalizedPos = pos / vec2(screenWidth, screenHeight);
    
    vec3 chalkColor = texture2D(chalkImg, normalizedPos).rgb;
    vec3 fboColor = texture2D(fbo, normalizedPos).rgb;
    
    gl_FragColor = vec4(fboColor, 1.);
}
