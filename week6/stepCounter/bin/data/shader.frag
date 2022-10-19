#ifdef GL_ES
precision highp float;
precision highp sampler2D;
#endif

uniform float screenHeight;
uniform float screenWidth;
uniform sampler2D chalkImg;
uniform sampler2D fbo;
uniform vec2 fboTextureInternal;
uniform vec2 chalkTextureInternal;
uniform float time;

void main() {
    vec2 pos = gl_FragCoord.xy;
    pos.y = screenHeight - pos.y;
    vec2 normalizedPos = pos / vec2(screenWidth, screenHeight);
    vec2 chalkPos = normalizedPos;
    chalkPos *= chalkTextureInternal;
    normalizedPos *= fboTextureInternal;
    
    vec3 chalkColor = texture2D(chalkImg, chalkPos).rgb;
    vec3 fboColor = texture2D(fbo, normalizedPos).rgb;
    fboColor *= chalkColor;
    if (fboColor.x > 0.) {
        fboColor.x += cos(time/100.);
    }
    if (fboColor.y > 0.) {
        fboColor.y += sin(time/100.);
    }
    
    gl_FragColor = vec4(fboColor, 1.);
}
