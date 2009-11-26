This is the source code to my Flash port of Quake.

In order to compile, Adobe Alchemy is needed.

STEP 1: Quake is compiled by Alchemy into a .swc using the quakeswf/makeswc makefile:
alc-on;					(needed 1st time only)
make -f makeswc;

This will create a quakeswf/lib/quake.swc file, which will be linked in to the final QuakeFlash.swf

STEP 2: Before the .swf file is compiled, PAK0.PAK must be copied from quake/id1/ into quakeswf/embed/ The pak is embedded into the .swf

STEP 3: QuakeFlash.swf is created by simply compiling the FlashDevelop project file.

Enjoy!
Michael Rennie.