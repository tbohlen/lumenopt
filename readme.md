#LumenOpt

LumenOpt is an optimizer that attempts to find the arrangement of floors
in a building that maximizes sun exposure and floor area. The long term goal is
to optimize building shape and floor placement to maximize the use of natural
lighting in the final design.

###File structure

The source files are contained in `./src`. Within that folder `include` contains
helpful header files, `visual` contains all information for creating the building
visualizers, and `vecmath` contains implementations of vectors and matrices for easy
linear algebra.

###Make

Currently, only the visualizers are functional. To test them:

* `cd src/visual`
* `make`
* `./imager` for static images
* `./visualizer` for full 3D models

###TODO list

* Create a sampler
* Create the sun model
* Create the building model
* Create the Heuristic evaluator
* Save out models for visualization
* Implement full ray tracing for the optimizer
* Implement the use of various materials in the optimizer
* Add shadow mapping to the visualizer and imager
* Add arg parsing to visualizer and imager
* Add additional times of day to the visualizer and imager
