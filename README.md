# Stand-alone planar polygon triangulation code

A no-fuss wrapper of Libigl's (http://libigl.github.io/libigl/tutorial/tutorial.html) wrapper of Jonathan Shewchuk's "Triangle" code.

You give a file with a list of points
x1 y1
x2 y2
...
in the plane, and a desired triangle area. You get a Delaunay triangulation of the polygon in .obj format. No questions asked.