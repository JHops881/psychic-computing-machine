#version 460 core

in vec2 tex_coord;

uniform sampler2D the_texture;

out vec4 frag_color;


void main() {
  frag_color = texture(the_texture, tex_coord);
}