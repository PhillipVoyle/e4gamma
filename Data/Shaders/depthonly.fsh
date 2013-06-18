
void main()
{
  vec4 surfaceColor = vec4(0.5, 0.5, 0.2, 1.0);
  
  float ambientTerm = 0.2;
  gl_FragColor = surfaceColor * ambientTerm;
}
