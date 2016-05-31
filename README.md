# SSAC
Surveillance Streaming and Control SSAC

HOME SERVER

the home server application have 12 files plus header file for each file
1.bgModelAndTrack file.cpp 
 -For background modeling and tracking 
2.displayThread.cpp
 -To display the video and to call the tracking and record class
3.globalVariables.cpp
 - To declare a global variables. Used by shared class 
4.main.cpp
 - Main function to call initiate main window and establish connection
5.mainwindow.cpp
 - provides the interface of the runing server and camera
6.myserver.cpp
 - To create and intialise the server
7.mythread.cpp
 - To accept the message from node server and to create Tcp socket for each connection
8.startRecord.cpp
 - To start video recording
9.startStream.cpp
 - To start the RTSP,TCP and HLS streaming
10.TargetObject.cpp
 - To keep track of the detected object
11.threatDetection.cpp
 - To Detected and Recognise the Interuder
12.model_2.yml
 - amodel for face recogniser


WEB SERVER

the web server application have serve.js file and index.html files together
1.server.js
 -To forward incomming data between mobile and home server
2.index.html
 -To provide web interface

MOBILE

This cliet application have 5 main java source files and a .xml file for layout
to import the project it needs android studio 2.0 
1. Main activity.java
- provides the first interface to login and starts the process
2. HlsViewFragment.java
- to display video from HTTP stream
3. RtspViewFragment
- to display video from RTSP stream
4. SetOptionFragment.java
- help to set parametrs as users need
5. TcpViewFragment.java
- to display video from TCP stream

INSTALLIATION 

The Home server needs opencv3.0,GStreamer-1.8.1,GStreamer RTSP Server-1.8.1 and Nodejs 4.4.5
-GStreamer-1.8.1 use this link: http://www.linuxfromscratch.org/blfs/view/cvs/multimedia/gstreamer10.html
-GStreamer RTSP Server-1.8.1 use this link:https://cgit.freedesktop.org/gstreamer/gst-rtsp-server
-opencv 3.0 with opencv_contrib use this link: https://github.com/Itseez
-Node js 4.4.5 use: https://nodejs.org/en/download/
