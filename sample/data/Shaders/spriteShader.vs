attribute vec3 a_posL;

attribute vec2 a_uv;
varying vec2 v_uv;

uniform mat4 u_world;
uniform vec2 u_data;
uniform vec2 u_pos;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_world * posL;
	
	// int row = u_data.x;
	// int cloumn = u_data.y;
	// int posR = u_pos.x;
	// int posC = u_pos.y;
	
	float disX = (1.0 / u_data.y);
	float disY = (1.0 / u_data.x);
	float xx=a_uv.x/u_data.y + disX * u_pos.y;
	float yy=a_uv.y/u_data.x + disY * u_pos.x;
	v_uv = vec2(xx,yy); 
	// v_uv = m_uv;
}
   