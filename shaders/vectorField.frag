uniform vec2 velocity;
 
uniform sampler2D texture;
 
void main()
{
	gl_FragColor = vec4(velocity.x*0.5+0.5, velocity.y*0.5+0.5, 0.5, gl_Color.a * texture2D(texture, gl_TexCoord[0].xy).a);
}