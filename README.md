# miniRT

Introduction to graphics with a basic raytracer working for spheres, squares, cylinder, triangles and planes. 

![miniRT](https://github.com/fredrikalindh/miniRT/blob/master/spheres.png)

### Prerequisites

This project is using the ``Minilibx`` using the Metal framework and therefore should work only on macOS 10.13+.<br>
You should follow [this guide](https://github.com/ilkou/minilibx) if you want to compile it on Linux.

### Usage

```
$ make (or make bonus for multithreaded faster rendering)

$ ./miniRT <path-to-file.rt> [--save]
```

save is optional and will save the scene as a bitmap.

#### Syntax .rt file (all upper letter descriptions are to be entered max one time):
```

R  [x] [y] #resolution 
A  [0-1] [R, G, B] #ambient light
c  [x, y, z] [-1-1, -1-1, -1-1] [0-180] #camera
l  [x, y, z] [0-1] [R, G, B] #point light
dl [-1-1, -1-1, -1-1] [0-1] [R, G, B] #directional light

sp [x, y, z] [radius] [R, G, B] + [check] #sphere
sq [x, y, z] [normal: -1, 0, 1] [side] [R, G, B] + [check] #square
tr [c1: x, y, z] [c2: x, y, z] [c3: x, y, z] [R, G, B] + [check] #triangle
pl [x, y, z] [normal: -1, 0, 1] [R, G, B] + [check] #plane
cy [x, y, z] [dir: -1, 0, 1] [radius] [height] [R, B, G] + [check] #cylinder

```
(See examples in /scenes/ folder)

![wolf](https://github.com/fredrikalindh/miniRT/blob/master/wolf2.png)
(wolf.rt by [@tharchen](https://github.com/Bressack))
