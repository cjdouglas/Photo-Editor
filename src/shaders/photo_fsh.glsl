// Fragment shader for drawing the standard photo texture.

// The photo texture we are drawing.
uniform sampler2D u_Texture;

// The brightness modifier of the texture.
uniform float u_Brightness;

// The texture coordinate we are rendering.
varying vec4 v_TexturePosition;

void main() {
	gl_FragColor = texture2D(u_Texture, v_TexturePosition.xy) * u_Brightness;
}
