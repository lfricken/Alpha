uniform sampler2D texture;

uniform vec2 velocity;//the direction of travel and magnitude
uniform float angle;

void main()
{
	float strength = 0.005;//how intense should the effect be?
	int samples = 10;//how many times should we create the effect(should be less than 30)
	
	vec4 pixelSum = vec4(0,0,0,0);
	vec4 pixel = vec4(0,0,0,0);
	vec2 copy = velocity;

	float clamp = 30;
	float magnitude = sqrt(copy.x*copy.x+copy.y*copy.y);
	if(magnitude > clamp)
	{
		copy.x *= clamp/magnitude;
		copy.y *= clamp/magnitude;
	}
	vec2 anotherCopy = copy;
	
	copy.x = cos(-angle)*anotherCopy.x + sin(-angle)*anotherCopy.y;
	copy.y = -sin(-angle)*anotherCopy.x + cos(-angle)*anotherCopy.y;
  
	vec2 offset = vec2(copy.x*strength, -copy.y*strength);
	offset /= samples;//we divide so that by the time we have 
	
	for(float i = 0; i < samples; ++i)//compute that many samples
	{
		pixel = texture2D(texture, gl_TexCoord[0].xy + offset*i);
		pixel *= pixel.a;
		pixelSum += pixel;
	}
	for(float i = 0; i < samples; ++i)//compute that many samples
	{
		pixel = texture2D(texture, gl_TexCoord[0].xy - offset*i);
		pixel *= pixel.a;
		pixelSum += pixel;
	}
	
	gl_FragColor = gl_Color*pixelSum/float(samples*2);
}