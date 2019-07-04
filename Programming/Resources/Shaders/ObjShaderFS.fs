precision mediump float;
//texture
uniform sampler2D u_texture0;
varying vec2 v_uv;

//fog
uniform float u_fogLength;
uniform float u_fogStart;
uniform vec4 u_fogColor;
uniform vec3 u_CameraPos;
varying vec3 v_posW;


uniform vec4 u_color;

void main()
{
	//float distanceToCamera= distance(u_CameraPos,v_posW);
	
	vec4 BaseColor = u_color;//texture2D(u_texture0,  v_uv);
	//float fogFactor = clamp(((distanceToCamera - u_fogStart)/u_fogLength), 0.0, 1.0);
	
	//gl_FragColor = mix(u_fogColor,BaseColor,1.0-fogFactor);
	gl_FragColor = BaseColor;
}
