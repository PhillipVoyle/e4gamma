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

def write_vertex(f, pos, nrm, u, v):
  f.write("pos ")
  f.write(str(pos.x))
  f.write(" ")
  f.write(str(pos.z))
  f.write(" ")
  f.write(str(pos.y))
  f.write(" ")
  f.write("nrm ")
  f.write(str(nrm.x))
  f.write(" ")
  f.write(str(nrm.z))
  f.write(" ")
  f.write(str(nrm.y))
  f.write(" ")
  f.write("uv ")
  f.write(str(u))
  f.write(" ")
  f.write(str(v))
  f.write("\n")

def write_some_data(context, filepath, use_some_setting):
  f = open(filepath, 'w')
  for obj in bpy.context.selected_objects:
    if (obj.type == 'MESH'):
      f.write("mesh\n")
      b = bpy.data.meshes[obj.name]
      count = 0
      for countFace in b.faces:
        nLen = len(countFace.vertices)
        count = count + ((nLen - 2) * 3)
        
      f.write("verts ")
      f.write(str(count))
      f.write("\n")
      for face in b.faces:
        nIndex = 0
        while nIndex < len(face.vertices) - 2:
          v = b.vertices[face.vertices[0]]
          write_vertex(f, v.co, v.normal, b.uv_textures[0].data[face.index].uv[0][0], b.uv_textures[0].data[face.index].uv[0][1])
          v = b.vertices[face.vertices[nIndex + 1]]
          write_vertex(f, v.co, v.normal, b.uv_textures[0].data[face.index].uv[nIndex + 1][0], b.uv_textures[0].data[face.index].uv[nIndex + 1][1])
          v = b.vertices[face.vertices[nIndex + 2]]
          write_vertex(f, v.co, v.normal, b.uv_textures[0].data[face.index].uv[nIndex + 2][0], b.uv_textures[0].data[face.index].uv[nIndex + 2][1])
          nIndex = nIndex + 1
               
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
