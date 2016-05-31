#-------------------------------------------------
#
# Project created by QtCreator 2016-05-26T15:52:08
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PTZSTREAMINANDCONTROL
TEMPLATE = app

INCLUDEPATH +=/usr/local/include/opencv
INCLUDEPATH +=/usr/local/include
LIBS +=-L/usr/local/lib -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn -lopencv_dpm -lopencv_fuzzy -lopencv_line_descriptor -lopencv_optflow -lopencv_plot -lopencv_reg -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_rgbd -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_face -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_xobjdetect -lopencv_objdetect -lopencv_ml -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core

INCLUDEPATH +=/usr/local/include/gstreamer-1.0
INCLUDEPATH +=/usr/include/gstreamer-1.0
INCLUDEPATH +=/usr/lib/x86_64-linux-gnu/gstreamer-1.0/include
INCLUDEPATH +=/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
LIBS +=-L/usr/local/lib -lgstrtspserver-1.0 -lgstbase-1.0 -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0
INCLUDEPATH +=/usr/include/gstreamer-1.0
INCLUDEPATH +=/usr/lib/x86_64-linux-gnu/gstreamer-1.0/include
INCLUDEPATH +=/usr/include/glib-2.0
INCLUDEPATH +=/usr/lib/x86_64-linux-gnu/glib-2.0/include
LIBS +=-L/usr/local/lib-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0

SOURCES += main.cpp\
    mainwindow.cpp \
    bgModelAndTrack.cpp \
    TargetObject.cpp \
    myserver.cpp \
    mythread.cpp \
    startStream.cpp \
    startRecord.cpp \
    threatDetection.cpp \
    displayThread.cpp \
    globalVariables.cpp

HEADERS  += mainwindow.h \
    bgModelAndTrack.h \
    TargetObject.h \
    myserver.h \
    mythread.h \
    startStream.h \
    startRecord.h \
    threatDetection.h \
    displayThread.h \
    globalVariables.h

FORMS    += mainwindow.ui

RESOURCES +=
