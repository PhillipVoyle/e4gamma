varying vec3 vertex_to_light_vector;
varying vec3 view_vector;

varying vec3 normal;
varying vec3 tangent;
varying vec3 binormal;

uniform sampler2D tex0;
uniform sampler2D tex1;

void main()
{
    // Defining The Material Colors
    vec4 surfaceColor = texture2D(tex1, gl_TexCoord[0].st);
    vec4 specularColor = vec4(0.3, 0.3, 0.3, 1.0);
    
    float ambientTerm = 0.0;
    float fShininess = 50.0;
 
    // normalize the 'normal' and vertex-to light vector
    vec3 N = normalize(normal);
    vec3 T = normalize(tangent);
    vec3 B = normalize(binormal);
    
    vec3 L = normalize(vertex_to_light_vector);

    //if there's a specular term, calculate that
    vec3 V = normalize(view_vector);
    
    float falloff = 1.0 - dot(L, vertex_to_light_vector)/8.0;

    vec3 bump = normalize(texture2D(tex0, gl_TexCoord[0].st).xyz * 2.0 - 1.0);
    mat3 tangentFrame = mat3(T, B, N);
    vec3 perturbed_normal = normalize(tangentFrame * bump);
    
    // calculate diffuse term
    float diffuseTerm = clamp(dot(perturbed_normal, L), 0.0, 1.0) * falloff;
    
    if(diffuseTerm > 0.0)
    {
      
      vec3 R = reflect(L, perturbed_normal);
      float specular = clamp(pow(max(dot(R, V), 0.0), fShininess), 0.0, 1.0) * falloff;
      
      gl_FragColor = gl_FragColor + (ambientTerm + diffuseTerm) * surfaceColor + specularColor * specular;
    }
    else
    {
      gl_FragColor = gl_FragColor + ambientTerm * surfaceColor;
    }
}


