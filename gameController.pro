#-------------------------------------------------
#
# Project created by QtCreator 2016-08-18T19:00:34
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gameController
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mutils.cpp \
    cameradevice.cpp \
    aboutdialog.cpp \
    doctormario.cpp \
    doctormariogame.cpp

HEADERS  += mainwindow.h \
    mutils.h \
    cameradevice.h \
    aboutdialog.h \
    doctormario.h \
    doctormariogame.h

FORMS    += mainwindow.ui

LIBS +=User32.LIB

CONFIG(release,debug | release){
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_calib3d248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_contrib248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_core248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_features2d248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_flann248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_gpu248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_highgui248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_imgproc248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_legacy248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_ml248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_nonfree248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_objdetect248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_ocl248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_photo248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_stitching248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_superres248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_ts248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_video248
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_videostab248
}

CONFIG(debug,debug | release){

win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_calib3d248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_contrib248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_core248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_features2d248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_flann248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_gpu248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_highgui248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_imgproc248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_legacy248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_ml248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_nonfree248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_objdetect248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_ocl248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_photo248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_stitching248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_superres248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_ts248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_video248d
win32: LIBS += -LG:\opencv2.4.8\opencv\build\x64\vc12\lib -lopencv_videostab248d
}

RESOURCES += \
    res.qrc

