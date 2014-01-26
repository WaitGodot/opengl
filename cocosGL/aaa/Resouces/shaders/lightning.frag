#version 140


in vec3 iResolution;
in float iGlobalTime;

float min_dist(vec2 v, vec2 w, vec2 p)
{
    float t = ((p.x - v.x) * (w.x - v.x) + (p.y - v.y) * (w.y - v.y)) /
                    ((w.x - v.x) * (w.x - v.x) + (w.y - v.y) * (w.y - v.y));
    if (t < 0.0)
        return distance(p, v);
    else if (t > 1.0)
        return distance(p, w);
    vec2 op = v + t * (w - v);
    return distance(p, op);
}

float rand(float _seed)
{
    return fract(sin(_seed+137.0) * 43758.5453);
}

float ll3(vec2 p1, vec2 p2, vec2 uv)
{
	vec2 plast;
		
	float mind = 1000000.0;
	
	plast = p1;
	
	float seed = rand(floor(iGlobalTime*40.0));
	
	for (int i=0; i < 2; i++)
	{
		float tt = float(i+1) / 3.0;
		
		vec2 pt = p1 + ((p2 - p1) * tt);
		float a = rand(seed) * 3.141592 * 2.0;
		vec2 pn = pt + vec2(cos(a), sin(a)) * rand(seed) / ((abs(tt-0.5)+1.0)*90.0);
		
		float d = min_dist(plast, pn, uv);
		if (d < mind)
			mind = d;
		
		plast = pn;
		seed = rand(seed);
	}
	
	float d = min_dist(plast, p2, uv);
	if (d < mind)
		return d * 3.0;
	else
		return mind * 5.0;
}


float ll2(vec2 p1, vec2 p2, vec2 uv)
{
	vec2 plast;
		
	float mind = 1000000.0;
	
	plast = p1;
	
	float seed = rand(floor(iGlobalTime*15.0));
	
	for (int i=0; i < 3; i++)
	{
		float tt = float(i+1) / 4.0;
		
		vec2 pt = p1 + ((p2 - p1) * tt);
		float a = rand(seed) * 3.141592 * 2.0;
		vec2 pn = pt + vec2(cos(a), sin(a)) * rand(seed) / ((abs(tt-0.5)+1.0)*30.0);
		
		float d = min_dist(plast, pn, uv);
		if (d < mind)
			mind = d;

		vec2 pn2 = pn + vec2(cos(a), sin(a)) * rand(seed) / ((abs(tt-0.5)+1.0)*rand(seed)*30.0);
		d = ll3(pn, pn2, uv);
		if (d < mind)
			mind = d;
		
		plast = pn;
		seed = rand(seed);
	}
	
	float d = min_dist(plast, p2, uv);
	if (d < mind)
		return d * 3.0;
	else
		return mind * 3.0;
}

out vec4 gl_FragColor;
//in vec4 varyingFragColor;

void main(void)
{
	vec2 uv = gl_FragCoord.xy / max(iResolution.x, iResolution.y);
	vec2 p1 = vec2(0.1, 0.3),
		 plast,
		 p2 = vec2(0.9, 0.3);
		
	float mind = 1000000.0;
	
	plast = p1;
	
	float seed = rand(floor(iGlobalTime*10.0));
	
	for (int i=0; i < 14; i++)
	{
		float tt = float(i+1) / 15.0;
		
		vec2 pt = p1 + ((p2 - p1) * tt);
		float a = rand(seed) * 3.141592 * 2.0;
		vec2 pn = pt + vec2(cos(a), sin(a)) * rand(seed) / ((abs(tt-0.5)+1.0)*9.0);
		
		float d = min_dist(plast, pn, uv);
		if (d < mind)
			mind = d;
		
		vec2 pn2 = pn + vec2(cos(a), sin(a)) * rand(seed) / ((abs(tt-0.5)+1.0)*rand(seed)*6.0);
		d = ll2(pn, pn2, uv);
		if (d < mind)
			mind = d;
		
		plast = pn;
		seed = rand(seed);
	}
	
	float d = min_dist(plast, p2, uv);
	if (d < mind)
		mind = d;
	
	mind *= 10.0;
	mind += 1.0;
	mind = 1.0 / (mind*mind*mind*mind);

	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0) * mind;
	gl_FragColor.r *= mind;
	gl_FragColor.g *= mind;
	
}