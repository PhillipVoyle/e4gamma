varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec3 eye_vector;

void main()
{
    // Defining The Material Colors
    const vec4 AmbientColor = vec4(0.2, 0.2, 0.2, 1.0);
    const vec4 DiffuseColor = vec4(0.4, 0.4, 0.4, 1.0);
    const vec4 SpecularColor = vec4(1.0, 1.0, 1.0, 1.0);
 
    // normalize the 'normal' and vertex-to light vector
    vec3 N = normalize(normal);
    vec3 L = normalize(vertex_to_light_vector);
    
    // calculate diffuse term
    float diffuse = clamp(dot(N, L), 0.0, 1.0);
    if(diffuse > 0.0)
    {
      //if there's a specular term, calculate that
      vec3 E = normalize(eye_vector);
      vec3 R = reflect(-L, N);
      float specular = clamp(pow(max(dot(R, E), 0.0), 100.0), 0.0, 1.0);
      
      gl_FragColor = AmbientColor + DiffuseColor * diffuse + SpecularColor * specular;
    }
    else
    {
      gl_FragColor = AmbientColor;
    }
}


