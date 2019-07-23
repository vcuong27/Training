attribute vec3 a_posL;
attribute vec2 a_uv;
uniform mat4 u_matMVP;
uniform mat4  u_matWorld;
uniform float u_alpha;

varying vec2 v_uv;
varying vec3 v_posW;

void main()
{
	vec4 pos = vec4(a_posL,u_alpha);
	vec4 position = u_matMVP * pos;
	
	gl_Position = position;
	
	v_uv = a_uv;
	v_posW = (u_matWorld * pos).xyz;
	
}   