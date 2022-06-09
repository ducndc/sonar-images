import open3d

pcd = open3d.io.read_point_cloud('../map/xyz.txt', format='xyz')

open3d.visualization.draw_geometries([pcd])

alpha = 1
print(f"alpha={alpha:.3f}")
mesh = open3d.geometry.TriangleMesh.create_from_point_cloud_alpha_shape(pcd, alpha)
mesh.compute_vertex_normals()
open3d.visualization.draw_geometries([mesh], mesh_show_back_face=True)
