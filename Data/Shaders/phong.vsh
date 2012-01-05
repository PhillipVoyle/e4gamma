varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec3 eye_vector;

void main()
{
   // Transforming The Vertex
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
   gl_TexCoord[0] = gl_MultiTexCoord0;
   // Transforming The Normal To ModelView-Space
   normal.xyz = gl_NormalMatrix * gl_Normal;
 
   // Transforming The Vertex Position To ModelView-Space
   vec3 vertex_in_modelview_space = vec3(gl_ModelViewMatrix * gl_Vertex);
   eye_vector = -vertex_in_modelview_space;
 
   // Calculating The Vector From The Vertex Position To The Light Position
   vertex_to_light_vector = vec3(gl_ModelViewMatrix* gl_LightSource[0].position) - vertex_in_modelview_space;
}
