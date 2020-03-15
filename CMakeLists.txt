cmake_minimum_required(VERSION 3.10)
project(aServer)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

set(INC_DIR /home/ubuntu/GithubFiles/aServer/Re3D)
set(LINK_DIR /home/ubuntu/GithubFiles/aServer/lib)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})

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

target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libre3dbase.so)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libre3dx.so)

target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libassimp.so.4)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libavcodec.so.54)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libavformat.so.54)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libavutil.so.52)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libboost_filesystem.so.1.54.0)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libboost_system.so.1.54.0)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libcudart.so.8.0)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libglut.so.3)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libgnutls.so.26)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libopenjpeg.so.2)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/librtmp.so.0)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libswscale.so.2)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libx264.so.142)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libpng12.so.0)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libIlmImf.so.6)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libHalf.so.6)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libvpx.so.1)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libschroedinger-1.0.so.0)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libva.so.1)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libgcrypt.so.11)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libIex.so.6)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libIlmThread.so.6)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libGLU.so.1)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libjasper.so.1)
target_link_libraries(aServer /home/ubuntu/GithubFiles/aServer/lib/libdc1394.so.22)



