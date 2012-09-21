FaceCap
====

####INTRO

FaceCap is realtime motion capture server for Autodesk Maya, developed in 
Xantus S.A. Animation Studio. This software uses OpenCV features to capture,
filter and track markers from camera. Data is send to Maya using external 
server technique. <b>This is more Proof-Of-Concept</b> than usefull tool.

[EXAMPLE USE](http://youtu.be/-cB8vS6rUbY)

####REQUIREMENTS

To build and use this software you need:
* <b>Linux</b> workstation
* Autodesk Maya 2011
* OpenCV 2.3.2
* webcam (or any video caputure device handled by OpenCV)

We've tested it with:
* Maya 2011.5-x64

Running on:
* Ubuntu 10.10 (x64)
* Fedora 14 (x64)

with cameras:
* Logitech HD Webcam C270
* Logitech Webcam Pro 9000

Details on building are in doc/INSTALL.txt file.

###FEATURES

* Tracking color based markers from camera device.
* No need to use helmet for face capturing. All markers positions are relative 
  to "nose" position which is always (0,0) - don't forget about it! It means 
  you can shift head up/down or left/right without messing the markers 
  coordinates. But be ceareful with radial moves :)
* Realtime data flow.

How to use instructions are (will be) in doc/using.html file.


####LIMITATIONS

As mentioned above this is <b>POC</b>. Main goal was to capture a frame, get 
interesting data and send it to Maya in *realtime*. Only one camera device is 
used so tracked markets are 2D without any 3D calculations (based on 
perspective,radial movements etc). FaceCap has never been tested with Microsoft
Windows enviroment.


####PACKAGE CONTENTS
````
AUTHORS.txt		Hall of fame :)
build_all.sh	Small bash script used to compile sources and link binaries.
Changelog.txt	Changelog file.
FC_global.h		Main header file.
FC_marker.c		Markers manipulation code.
FC_marker.h
FC_math.c		Few simple math functions based on Quake 3 Arena code.
FC_math.h
FC_maya.c		Simplified server for Autodesk Maya.
FC_maya.h
FC_opencv.c		OpenCV picture processing.
FC_opencv.h
GPLv3.txt		License.
main.c			Main loop.
README.md		Self-explaining :)
doc/INSTALL.txt		Building instructions.
mel/*			Sample MEL scripts and Maya scenes.
````

####LICENSING

FaceCap is released under GNU General Public License v3. Details in GPLv3.txt 
file.

####EXTRA INFOS AND LINKS

Maya is registered trademark of Autodesk, Inc. Details on product's web page: 
http://usa.autodesk.com/maya/

######2012 Xantus S.A.