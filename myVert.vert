#version 130

in vec3 vs_in_pos;
in vec3 vs_in_col;

out vec3 vs_out_col;

uniform mat4 MVP;
uniform float r;
uniform float R;

void main()
{

	vec3 vs_out_pos = vs_in_pos;
	vs_out_col = vs_in_col;

	if(vs_in_col[0] > 0.9f && vs_in_col[1] < 0.1f && vs_in_col[2] < 0.1f){
		vs_out_pos[2] = vs_in_pos[2] + sin(vs_in_pos[0]*R)*r;
		vs_out_col[0] = 0.8f;
	}

	gl_Position = MVP * vec4( vs_out_pos, 1 );

	
}