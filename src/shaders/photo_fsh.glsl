// Fragment shader for drawing the standard photo texture.

// The photo texture we are drawing.
uniform sampler2D u_Texture;

// The resolution of the current texture.
uniform ivec2 u_TextureResolution;

// The brightness modifier of the texture.
uniform float u_Brightness;

// Vignette parameters
uniform float u_VignetteIntensity;
uniform float u_VignetteRadius;

// The texture coordinate we are rendering.
varying vec4 v_TexturePosition;

const float VIGNETTE_SOFTNESS = 0.45;

void main() {
	vec4 texColor = texture2D(u_Texture, v_TexturePosition.xy);

	// Apply brightness
	texColor.rgb *= u_Brightness;

	// Vignette calculation
	vec2 position = vec2(0.5) - vec2(v_TexturePosition.xy);
	position.x *=  (u_TextureResolution.x / u_TextureResolution.y);
	float len = length(position);
	float vignette = 
		smoothstep(u_VignetteRadius, u_VignetteRadius - VIGNETTE_SOFTNESS, len);
	texColor.rgb = mix(texColor.rgb, texColor.rgb * vignette, u_VignetteIntensity);
	
	// Output
	gl_FragColor = texColor;
}
