# Maze
The aim of this assessment was to produce a program to walk through and render a three dimensional maze in real time. The program was to be written in C or C++ using the OpenGL library. The pattern of the maze was to be defined by a text file, and movement through the maze, using the cursor keys, was to obey collision detection rules. Spinning objects were to be placed in the maze, and the scene was to be rendered using perspective projection, lighting and smooth shading. All the required features have been implemented. Aerial, player, inset and cross-eyed stereo views, opening and closing solid walls, objects for collection, textures, sounds, monsters, and movement using the mouse, have been added as extra features.  

#2: Program Description
#2.1: Class Architecture
The overall class architecture attempts to divide the design into model, view and control interfaces. The game, scene and control classes provide these interfaces. The design has been implemented as the display, control, game, cell, collision, scene, node, group, label, reference, screen, camera, light, shape, maze, mesh, triangle, cylinder, disc, sphere, plane, polyhedron, transform, material, texture, sound, bitmap, reader, colour and vectors classes.
#2.2: Control Classes
The display and control class provide the interface for user interaction using the mouse and keyboard. The control class delegates responsibility for maintaining the state of the game to the game class, and responsibility for rendering a view of the game to the scene class.
#2.3: Model Classes
The game class maintains an associative container of references to nodes. This allows objects representing cameras, lights, shapes, textures and sounds to be read from data files, and labelled for easy reference. For improved rendering speed this associative container can also reference display lists. The game class dynamically constructs scenes and views at frame-rate, according to the state of the game, and delegates the responsibility of rendering these views to the scene class. The game class maintains the state of the game in an array of cells. The collision class regulates all movements of the player and monsters.
#2.4: View Classes
The node class is the abstract base class, from which all other view classes inherit. This allows objects to be grouped into a hierarchical tree, or labelled and added to an associative container. The node’s interface includes read, update and render operations. The group class provides a hierarchical container of nodes. The label class inherits from the group class and allows labelling of groups of nodes. The reference class allows labelled groups of nodes to be referenced.
The screen class contains the background colour attribute. The camera class contains position, direction, up vector and field of view attributes, and applies these to the projection and view matrices. The light class contains position, ambient, diffuse and specular colour attributes. The shape class contains the material attribute. The maze, mesh, triangle, cylinder, disc, sphere, plane and polyhedron classes all derive from the shape class, and add specialized attributes for their specific shapes. The texture and sound classes read into texture and sound objects from BMP and WAV files respectively.
The transform class contains scale, rotate and translate attributes, which are applied to the model matrix in that order. The effect of a transform is local to a group of nodes, and effective from its point of definition onwards. The material class contains ambient, diffuse, specular, shininess and emissive colour attributes. These attributes assume their default values for a shape unless they are explicitly specified.
#3: Program Features
#3.1: Aerial and Player Views
Aerial and player views are provided by viewing the scene using a fixed aerial camera or a moveable player camera respectively. Inset player and aerial views can be added to the main aerial and player views. This is achieved by clearing the depth buffer, and rendering the inset view into a view port of a reduced size, after having previously rendered the main view.
#3.2: Stereo View
Stereo view is provided by using offset player cameras to render into two view ports, which are separated by a border. Cross-eyed stereoscopy is achieved by rendering the image for the right eye to the left side of the screen, and that for the left eye to the right side of the screen. Moving the camera to the right, and directing it towards the convergence point produces the image for the right eye. The centre of this camera view is rotated to align with the centre of the left view port, and the viewing frustum is offset relative to the camera to cover the left view port. The image for the left eye is produced in a similar manner.
#3.3: Solid Walls
Solid walls are defined in the data file as five planes for the front, back, left, right and top faces. These planes are rotated and resized to create a block with outward facing normals, which allows back-face culling to be enabled for improved rendering speed. The walls are created to produce reasonable results when they overlap with other walls. This is done by making the walls slightly longer than their thickness would imply, and by rotating the walls slightly about their vertical axes.
#3.4: Textures
Texture maps are read from Windows BMP files into texture objects, and the active texture can be changed at any point in the scene by adding a reference to it. Texture coordinates can be specified for each plane to which the texture is to be applied, lighting is applied to the textures, and mipmaps are generated automatically. A further extension would be to apply textures to shapes other than planes.
#3.5: Sounds
Sounds have been added using the OpenAL library. Sounds are read from WAV files into sound objects, and can be added to the scene at frame rate by adding references to them. The OpenAL library works with Windows 98, but not with Windows NT4. Executables with and without links to the sound library have been provided. The executable which has been linked to the sound library requires the use of the OpenAL32 dynamic link library.
#3.6: Collision Detection
The movements of the player and monsters obey collision detection rules. The player can only move over a wall if it is open, and monsters can never move through a wall. Collision detection has been implemented for the special case of a maze by considering each scenario in turn. For simplicity, movement has been restricted to be less than the dimensions of a cell.
If the player moves between orthogonally adjacent cells, then the relevant side of the cell must be tested for an obstructing wall. If that wall is present, then the player’s coordinate is clipped in one dimension to simulate the player sliding along the wall. If the player moves between diagonally adjacent cells, then the corner between the cells must be tested first. This determines the pair of sides of neighbouring cells to be tested for obstructing walls. After the player’s movement has been tested and clipped in one dimension, the side to be tested in the second dimension needs to be chosen appropriately.
After all collisions have been detected and the coordinates clipped, the player is pushed back to simulate the thickness of the solid wall. The player must also be pushed back from the ends and corners of walls in adjacent cells.
#3.7: Artificial Intelligence
The monsters in this game have a very low level of artificial intelligence. They attempt to follow the player by slowly turning towards him and advancing. However, collision detection usually prevents them from doing what they want, and when their limited intelligence does succeed in finding the player, they are killed.
#4: Conclusion
The assessment has been completed successfully. It has demonstrated the use of a collision detection algorithm and OpenGL to model and render an interactive view of a three dimensional maze. Links to this report, source code, executables, and data files will be provided at the following address
Appendix: User Guide
The program is run from the command line as “Maze.exe” or “MazeWithSound.exe”. If the program is run without a command line argument, then it reads the data file from “../Data/Game.txt”. If the program is run with a command line argument, then this specifies the filename of the data file. The following menu is displayed in the console window, and details the use of the mouse and keyboard to play the game.

Escape    	Exit Program
F1		Aerial View
F2		Player View
F3		Aerial View with Inset Player View
F4		Player View with Inset Aerial View
F5		Stereo View
F6		Solid or Wire Frame View
Space		Restart Game
Left and Right  Rotate
Up and Down     Move
Mouse 		Rotate and Move
