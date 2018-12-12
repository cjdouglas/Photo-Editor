// Vertex shader for drawing the standard photo texture.

// The surface coordinate of this vertex.
attribute vec4 a_Position;

// The texture coordinate of this vertex.
attribute vec4 a_TexturePosition;

// The output texture coordinate for the fragment shader.
varying vec4 v_TexturePosition;

void main() {
	v_TexturePosition = a_TexturePosition;
	gl_Position = a_Position;
}
