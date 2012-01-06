varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec3 eye_vector;

uniform sampler2D tex;

mat3 computeTangentFrame(vec3 normal, vec3 position, vec2 texCoord)
{
    vec3 dpx = dFdx(position);
    vec3 dpy = dFdy(position);
    vec2 dtx = dFdx(texCoord);
    vec2 dty = dFdy(texCoord);
    
    vec3 tangent = normalize(dpx * dty.t - dpy * dtx.t);
    vec3 binormal = normalize(-dpx * dty.s + dpy * dtx.s);
   
    return mat3(tangent, binormal, normal);
}

void main()
{
    // Defining The Material Colors
    vec4 AlbedoColor = vec4(1.0, 1.0, 1.0, 1.0);//texture2D(tex, gl_TexCoord[0].st);
    vec4 AmbientColor = 0.2 * AlbedoColor;
    vec4 DiffuseColor = AlbedoColor;
    vec4 SpecularColor = vec4(1.0, 1.0, 1.0, 1.0);
    
    float fShininess = 255.0;
 
    // normalize the 'normal' and vertex-to light vector
    vec3 N = normalize(normal);
    vec3 L = normalize(vertex_to_light_vector);

    //if there's a specular term, calculate that
    vec3 E = normalize(eye_vector);

    vec3 bump = normalize(texture2D(tex, gl_TexCoord[0].st).xyz * 2.0 - 1.0);
    mat3 tangentFrame = computeTangentFrame(N, -E, gl_TexCoord[0].st);
    vec3 perturbed_normal = normalize(tangentFrame * bump);
    
    // calculate diffuse term
    float diffuse = clamp(dot(perturbed_normal, L), 0.0, 1.0);
    if(diffuse > 0.0)
    {
      
      vec3 R = reflect(L, perturbed_normal);
      
      float specular = clamp(pow(max(dot(R, -E), 0.0), fShininess), 0.0, 1.0);
      
      
      gl_FragColor = AmbientColor + DiffuseColor * diffuse + SpecularColor * specular;
    }
    else
    {
      gl_FragColor = AmbientColor;
    }
}


