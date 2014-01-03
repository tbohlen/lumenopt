Compiling:

To compile, simply run the command "make" when in this assignment's root directory. This will create a new executable called "a4".

Running:

To run, type the following, replacing "[arguments]" with any arguments listed below:

./a4 [arguments]

Required Arguments:

"-input <input-file>" - specifies "<input-file>" as the file that describes the scene to be rendered.
"-output <output-file>" - specifies "<output-file" as the file to write the rendered image to.
"-size <width> <height>" -specifies "<width>" as the width of the rendered image and "<height>" as its height. Both should be integers.

Optional Aruments:

"-intersect" - causes the rendering to show white if an intersection with the scene was found for that pixel, and black otherwise.
"-depth <min-depth> <max-depth>" - causes the rendering to visualize the distance from the camera to the objects as a gray value coloration of the objects. Objects closer than "<min-depth>" will be rendered as white, and those more distant than "<max-depth>" will be rendered as black. Those in between will be rendered as a gray-scale color linearly increasing from white at "<min-depth>" to black at "<max-depth>".
"-normal <normal-file>" - causes the production of a second rendering of the scene using the RGB color space to render the direction of the normals visible in the scene. Red represents the x component, blue the y, and green the z. This image will be saved to "<normal-file>".

Of intersect and depth, the last argument sent will describe the rendering. If neither are specified a shaded image of the model will be generated.

Collaboration:

I talked very briefly with Zach Segal. It is hardly worth commenting on. I mentioned my idea on how to compute he reflected ray for specular highlights, and he said he thought it sounded reasonable.

References:

As always, I used cplusplus.com, stackoverflow.com, and the lecture notes, but not much else.

Problems:

There are no known problems with my code. All parts should be implemented correctly.

Extra Credit:

I did not do any extra credit.
