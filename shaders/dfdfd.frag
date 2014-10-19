uniform sampler2D texture;
uniform sampler2D velocityField;

uniform int samples = 10;//how many times should we create the effect(should be an even number)
uniform float strength = 0.01;//how intense should the effect be?

void main()
{
	vec4 pixelSum = texture2D(texture, gl_TexCoord[0].xy);
	vec2 velocity = texture2D(velocityField, gl_TexCoord[0].xy).xy * 2.0 - 1.0;
 
	velocity *= strength;
  
	for(float i = 1; i < samples; ++i)//compute that many samples
	{
		pixelSum += texture2D(texture, gl_TexCoord[0].xy + velocity*i)/2;
		
		pixelSum += texture2D(texture, gl_TexCoord[0].xy - velocity*i)/2;
	}
  
	gl_FragColor = gl_Color*pixelSum/(1);
}


  /*
uniform sampler2D texture;
uniform sampler2D velocityField;

uniform int samples = 10;//how many times should we create the effect(should be an even number)
uniform float strength = 0.01;//how intense should the effect be?

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec2 velocity = texture2D(velocityField, gl_TexCoord[0].st).xy * 2.0 - 1.0;
  

	vec2 offset = vec2(velocity.x*strength, -velocity.y*strength);
	offset /= samples;//we divide so that by the time we have 
	
	for(float i = 1; i < samples; ++i)//compute that many samples
	{
		pixel += texture2D(texture, gl_TexCoord[0].xy + offset*i);
		pixel += texture2D(texture, gl_TexCoord[0].xy - offset*i);
	}
	gl_FragColor = gl_Color*pixel/float(samples*2);
}





void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec2 velocity = texture2D(velocityField, gl_TexCoord[0].xy).xy * 2.0 - 1.0;
  

	vec2 offset = vec2(velocity.x*strength, -velocity.y*strength);
	offset /= samples;//we divide so that by the time we have 
	
	for(float i = 1; i < samples; ++i)//compute that many samples
	{
		pixel += texture2D(texture, gl_TexCoord[0].xy + offset*i);
		pixel += texture2D(texture, gl_TexCoord[0].xy - offset*i);
	}
	gl_FragColor = gl_Color*pixel/float(samples*2);
}
*/