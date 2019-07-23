precision mediump float;

uniform sampler2D u_texture0;
varying vec2 v_uv;

varying vec3 v_posW;


uniform vec4 u_color;

void main()
{
	
	
	vec4 BaseColor = u_color;//texture2D(u_texture0,  v_uv);
	gl_FragColor = BaseColor;
}
