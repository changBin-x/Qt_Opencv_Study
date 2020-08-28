TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

INCLUDEPATH+=../../opencv430ForQtBuild_win64/include/opencv2 \
        ../../opencv430ForQtBuild_win64/install/include

INCLUDEPATH += ../../opencv430ForQtBuild_win64/include

LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_aruco430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_bgsegm430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_bioinspired430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_calib3d430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_ccalib430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_core430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_cvv430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_datasets430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_dnn_objdetect430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_dnn_superres430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_dnn430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_dpm430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_face430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_features2d430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_flann430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_fuzzy430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_gapi430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_hfs430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_highgui430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_img_hash430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_imgcodecs430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_imgproc430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_intensity_transform430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_line_descriptor430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_ml430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_objdetect430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_optflow430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_phase_unwrapping430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_photo430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_plot430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_quality430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_rapid430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_reg430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_saliency430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_shape430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_stereo430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_stitching430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_structured_light430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_superres430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_surface_matching430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_text430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_tracking430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_video430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_videoio430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_videostab430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_xfeatures2d430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_ximgproc430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_xobjdetect430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/libopencv_xphoto430.dll
LIBS +=../../opencv430ForQtBuild_win64/bin/opencv_videoio_ffmpeg430_64.dll
