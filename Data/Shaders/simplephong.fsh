varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec3 view_vector;

void main()
{
    // Defining The Material Colors
    vec4 surfaceColor = vec4(0.5, 0.5, 0.2, 1.0);
    vec4 specularColor = vec4(0.3, 0.3, 0.3, 1.0);
    
    float ambientTerm = 0.2;
    float fShininess = 50.0;
 
    // normalize the 'normal' and vertex-to light vector
    vec3 N = normalize(normal);
    vec3 L = normalize(vertex_to_light_vector);
    
    float falloff = 1.0 - dot(L, vertex_to_light_vector)/5.0;
    
    //if there's a specular term, calculate that
    vec3 V = normalize(view_vector);

    // calculate diffuse term
    float diffuseTerm = clamp(dot(N, L), 0.0, 1.0) * falloff;
    
    if(diffuseTerm > 0.0)
    {
      vec3 R = reflect(L, N);
      
      float specular = clamp(pow(max(dot(R, V), 0.0), fShininess), 0.0, 1.0) * falloff;
      
      
      gl_FragColor = (ambientTerm + diffuseTerm) * surfaceColor + specularColor * specular;
    }
    else
    {
      gl_FragColor = ambientTerm * surfaceColor;
    }
}


