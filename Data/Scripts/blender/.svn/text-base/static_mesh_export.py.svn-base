#!BPY

import bpy

bl_info = {
    "name": "E4Gamma static_mesh export",
    "description": "E4Gamma static mesh export",
    "author": "PHILLIP VOYLE",
    "version": (1, 1),
    "blender": (2, 61, 0),
    "api": 31236,
    "location": "File > Export",
    "warning": "", # used for warning icon and text in addons panel
    "wiki_url": "",
    "tracker_url": "",
    "category": "Import-Export"}

def write_vertex(f, mesh_verts, face_verts, face_index, face_vert_index, data):
  vert_index = face_verts[face_vert_index]
  vert = mesh_verts[vert_index]
  pos = vert.co
  nrm = vert.normal
  uv = data[face_index].uv
  u = uv[face_vert_index][0]
  v = uv[face_vert_index][1]
  f.write("vrt " + str(vert_index) + "\n")
  f.write(" pos " + str(pos.x) + " " + str(pos.z) + " " + str(pos.y) + "\n")
  f.write(" nrm " + str(nrm.x) + " " + str(nrm.z) + " " + str(nrm.y) + "\n")
  f.write(" uv " + str(u) + " " + str(v) + "\n")


def write_tri(f, mesh_verts, face_verts, face_index, tri_index, data):
  write_vertex(f, mesh_verts, face_verts, face_index, 0, data);
  write_vertex(f, mesh_verts, face_verts, face_index, tri_index + 1, data)
  write_vertex(f, mesh_verts, face_verts, face_index, tri_index + 2, data)

def write_some_data(context, filepath, use_some_setting):
  f = open(filepath, 'w')
  for obj in bpy.context.selected_objects:
    if (obj.type == 'MESH'):
      f.write("mesh\n")
      b = bpy.data.meshes[obj.name]
      countTris = 0
      for countFace in b.faces:
        nLen = len(countFace.vertices)
        countTris = countTris + (nLen - 2)
        
      tri_vert = [[0 for i in range(3)] for j in range(countTris)]
      tri_uv = [[[0.0 for i in range(2)] for j in range(3)] for k in range(countTris)]
      tri_face = [0 for i in range(countTris)]
      
      #organise triangles
      tri_index = 0
      for face in b.faces:
        for face_tri_index in range(len(face.vertices) - 2):
          tri_vert[tri_index][0] = face.vertices[0]
          tri_vert[tri_index][1] = face.vertices[face_tri_index + 1]
          tri_vert[tri_index][2] = face.vertices[face_tri_index + 2]
          tri_uv[tri_index][0][0] = b.uv_textures[0].data[face.index].uv[0][0]
          tri_uv[tri_index][0][1] = b.uv_textures[0].data[face.index].uv[0][1]
          tri_uv[tri_index][1][0] = b.uv_textures[0].data[face.index].uv[face_tri_index + 1][0]
          tri_uv[tri_index][1][1] = b.uv_textures[0].data[face.index].uv[face_tri_index + 1][1]
          tri_uv[tri_index][2][0] = b.uv_textures[0].data[face.index].uv[face_tri_index + 2][0]
          tri_uv[tri_index][2][1] = b.uv_textures[0].data[face.index].uv[face_tri_index + 2][1]
          tri_face[tri_index] = face.index
          tri_index = tri_index + 1
      
      #calclulate triangle adjacency
      tri_adj = [[-1 for i in range(3)] for j in range(countTris)]
      for first_tri in range(countTris):
        for second_tri in range(first_tri + 1, countTris):
          for first_edge in range(3):
            for second_edge in range(3):  #should we explicitly expect winding to be correct here?
              if((tri_vert[first_tri][first_edge] == tri_vert[second_tri][second_edge] and
                tri_vert[first_tri][(first_edge + 1) % 3] == tri_vert[second_tri][(second_edge + 1) % 3]) or
                (tri_vert[first_tri][(first_edge + 1) % 3] == tri_vert[second_tri][second_edge] and
                tri_vert[first_tri][first_edge] == tri_vert[second_tri][(second_edge + 1) % 3])):
                  tri_adj[first_tri][first_edge] = second_tri
                  tri_adj[second_tri][second_edge] = first_tri #include twice (but we will only export once later)
      
      #write vertices
      f.write("verts " + str(len(b.vertices)) + "\n")
      for vert in b.vertices:
        f.write("pos " + str(vert.co.x) + " " + str(vert.co.z) + " " + str(vert.co.y) + " ")
        f.write("nrm " + str(vert.normal.x) + " " + str(vert.normal.z) + " " + str(vert.normal.y) + "\n")
      
      #write tris      
      f.write("triangle_list " + str(countTris) + "\n")
      for tri_id in range(countTris):
        normal = b.faces[tri_face[tri_id]].normal
        p0 = b.vertices[tri_vert[tri_id][0]].co
        c = normal.x * p0.x + normal.y * p0.y + normal.z * p0.z
        f.write("eq " + str(normal.x) + " " + str(normal.z) + " " + str(normal.y) + " " + str(c) + "\n")
        f.write("v " + str(tri_vert[tri_id][0]) + " uv " + str(tri_uv[tri_id][0][0]) + " " + str(tri_uv[tri_id][0][1]) + "\n")
        f.write("v " + str(tri_vert[tri_id][1]) + " uv " + str(tri_uv[tri_id][1][0]) + " " + str(tri_uv[tri_id][1][1]) + "\n")
        f.write("v " + str(tri_vert[tri_id][2]) + " uv " + str(tri_uv[tri_id][2][0]) + " " + str(tri_uv[tri_id][2][1]) + "\n")
      
      #count edges
      edge_count = 0
      for tri in range(countTris):
        if tri_adj[tri][0] > tri or tri_adj[tri][0] == -1:
          edge_count = edge_count + 1
        if tri_adj[tri][1] > tri or tri_adj[tri][1] == -1:
          edge_count = edge_count + 1
        if tri_adj[tri][2] > tri or tri_adj[tri][2] == -1:
          edge_count = edge_count + 1
          
      #write adjacency info
      f.write("edges " + str(edge_count) + "\n");
      for tri in range(countTris):
        if tri_adj[tri][0] > tri or tri_adj[tri][0] == -1:
          f.write("e " + str(tri) + " " + str(tri_adj[tri][0]) + " v " + str(tri_vert[tri][0]) + " " + str(tri_vert[tri][1]) + "\n")
        if tri_adj[tri][1] > tri or tri_adj[tri][1] == -1:
          f.write("e " + str(tri) + " " + str(tri_adj[tri][1]) + " v " + str(tri_vert[tri][1]) + " " + str(tri_vert[tri][2]) + "\n")
        if tri_adj[tri][2] > tri or tri_adj[tri][2] == -1:
          f.write("e " + str(tri) + " " + str(tri_adj[tri][2]) + " v " + str(tri_vert[tri][2]) + " " + str(tri_vert[tri][0]) + "\n")
        
  f.close()
  return {'FINISHED'}


# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty


class ExportSomeData(bpy.types.Operator, ExportHelper):
  '''This appears in the tooltip of the operator and in the generated docs.'''
  bl_idname = "export.some_data"  # this is important since its how bpy.ops.export.some_data is constructed
  bl_label = "Export Some Data"
  
  # ExportHelper mixin class uses this
  filename_ext = ".mesh"
  
  filter_glob = StringProperty(
                               default="*.mesh",
                               options={'HIDDEN'},
                               )
  
  # List of operator properties, the attributes will be assigned
  # to the class instance from the operator settings before calling.
  use_setting = BoolProperty(
                             name="Example Boolean",
                             description="Example Tooltip",
                             default=True,
                             )
  
  type = EnumProperty(
                      name="Example Enum",
                      description="Choose between two items",
                      items=(('OPT_A', "First Option", "Description one"),
                             ('OPT_B', "Second Option", "Description two")),
                      default='OPT_A',
                      )
  
  @classmethod
  def poll(cls, context):
    return context.active_object is not None
  
  def execute(self, context):
    return write_some_data(context, self.filepath, self.use_setting)


# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
  self.layout.operator(ExportSomeData.bl_idname, text="E4Gamma Static Mesh Export")

def register():
  bpy.utils.register_class(ExportSomeData)
  bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
  bpy.utils.unregister_class(ExportSomeData)
  bpy.types.INFO_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
  register()

# test call
#bpy.ops.export.some_data('INVOKE_DEFAULT')
