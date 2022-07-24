uniform sampler2D diffuse;
uniform vec4 ambientColor;
void main()
{
  vec4 surfaceColor = texture2D(diffuse, gl_TexCoord[0].st);
  gl_FragColor = surfaceColor * ambientColor;
}
