#LumenOpt

LumenOpt is an optimizer that attempts to find the arrangement of floors
in a building that maximizes sun exposure and floor area. The long term goal is
to optimize building shape and floor placement to maximize the use of natural
lighting in the final design.

###File structure

The source files are contained in `./src`. Within that folder `include` contains
helpful header files, `visual` contains all information for creating the building
visualizers, `vecmath` contains implementations of vectors and matrices for easy
linear algebra, and `model` contains all files that help with modeling of the day lighting.

###Make

To make the visualizers:

* `cd src/visual`
* `make`

To make the modeler:

* `cd src/model`
* `make`

###Run

First, run the modeler to create a building model using `./model`
It takes the following arguments:
* `--template` followed by the file name of a template building (explained
  below)
* `--runs` followed by the number of runs of the optimizer to execute
* `--suns` followed by the number of sun positions to test with
`./model` will output a file ending `.bldg`containing a description of the
result.

Then run a visualizer to see the model you have created:
* copy the `.bldg` file into the src/visual folder and assure it is named
  `best.bldg`
* `./imager` for static images
* `./visualizer` for full 3D models

###Template Files

A template building can be used to provide the shape of the buildable envelope
to optimize floor placement within. The file format must match the building file
format used for exporting lumenopt buildings as text files. Try running the
modeler without a template file and looking at the format of the result to get a
basic understanding. In future, tools should be built in order to provide better
geometry importing.

###TODO list

* Create the sun model - DONE
* Create the Heuristic evaluator - DONE
* Implement full ray tracing for the optimizer
* Implement the use of various materials in the optimizer
* Add shadow mapping to the visualizer and imager
* Add arg parsing to visualizer and imager
* Add additional times of day to the visualizer and imager
* Add a better way to import geometries.
