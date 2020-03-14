cmake_minimum_required(VERSION 3.15)
project(aServer)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

set(INC_DIR /home/k/3DTracking/Re3DX-v100/include/)
set(LINK_DIR /home/k/3DTracking/Re3DX-v100/)
set(LINK_DIR2 /home/k/3DTracking/Re3DX-v100/lib)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})
link_directories(${LINK_DIR2})

add_executable(aServer main.cpp
        Net/NetServer.cpp Net/NetServer.h
        Net/NetClient.cpp Net/NetClient.h
        Net/clientBuffer.cpp Net/clientBuffer.h
        Net/UseEpoll.cpp Net/UseEpoll.h
        Net/TimeWheel.cpp Net/TimeWheel.h
        theDetector.cpp theDetector.h
        MemoryChannel.cpp MemoryChannel.h
        Re3D/base.h
        Re3D/commands.h
        Re3D/cvrender.h
        Re3D/def.h
        Re3D/re3dx.h
        Re3D/tracker.h)

target_link_libraries(aServer ${OpenCV_LIBS})

target_link_libraries(aServer libre3dbase.so)
target_link_libraries(aServer libre3dx.so)

target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libassimp.so.4)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libavcodec.so.54)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libavformat.so.54)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libavutil.so.52)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libboost_filesystem.so.1.54.0)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libboost_system.so.1.54.0)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libcudart.so.8.0)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libglut.so.3)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libgnutls.so.26)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libopenjpeg.so.2)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/librtmp.so.0)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libswscale.so.2)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libx264.so.142)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libpng12.so.0)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libIlmImf.so.6)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libHalf.so.6)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libvpx.so.1)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libschroedinger-1.0.so.0)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libva.so.1)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libgcrypt.so.11)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libIex.so.6)
target_link_libraries(aServer /home/k/3DTracking/Re3DX-v100/lib/libIlmThread.so.6)