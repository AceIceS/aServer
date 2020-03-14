
#include "theDetector.h"

/*
void theDetector::Fuck()
{
    initRe3DX();

    //load models
    ModelSet models;
    //load models, if the data file(*.mdb) is not exist, load the 3D model and precompute for the data file.
    //-models: the name of models, multiple models can be specified
    //-dataFile: the data file of each model, %%s will be replaced by the model name specified with -models
    //-meshFile: the 3D model file of each model

    models.load("list -models xiaoMing_r -dataFile"
                " /home/k/CLionProjects/aServer/%%s.mdb1 -meshFile /home/k/3DTracking/xiaoMing_r.3ds");
//	models.setArgs("-setPose0 -");

    //the precomputed model file
    //std::string models[] = {
    //	"bottle2",
    //"xiaoMing",
    //"HardDisk",
    //"blueMoon",
    //"CLemon"
    //};

    Size imgSize(1280, 720);

    cv::VideoCapture cap;

    //estimate the intrinsic camera parameters. Calibration is required for better accuracy.
    Matx33f K = cvrm::defaultK(imgSize, 1.2f);

//#if 1
    //cap.open(0+CAP_DSHOW);
    cap.set(CAP_PROP_FRAME_WIDTH, imgSize.width);
    cap.set(CAP_PROP_FRAME_HEIGHT, imgSize.height);
//#else
    // cap.open("../TestX/bottle2-3.avi");
//#endif
    imgSize = Size(int(cap.get(CAP_PROP_FRAME_WIDTH) + 0.5), int(cap.get(CAP_PROP_FRAME_HEIGHT) + 0.5));

    printf("image-size=(%d,%d)\n", imgSize.width, imgSize.height);

    auto detector = Detector3D::create();



    auto tracker = Tracker3D::create();

    std::cout<<"Detector Set Models"<<std::endl;
    detector->setModels(&models);
    std::cout<<"Tracker Set Models"<<std::endl;
    tracker->setModels(&models);
    std::cout<<"Tracker Set Detector"<<std::endl;
    tracker->setDetector(detector.get());

    FrameData fd;
    fd.cameraK = K;

    while (1)
    {
        Mat img;
        cap>>img;

        std::cout<<"1";
        time_t beg = clock();

        tracker->pro(img, fd);



        printf("fps=%.2lf       \r", CLOCKS_PER_SEC / double(clock() - beg));

        //draw the object contour if tracking confidence is high
        for (int i = 0; i<fd.objs3DNumbers; ++i)
        {
            auto &r = fd.objs3D[i];

            //get matreix
            Matx44f matrix = cvrm::fromRT(r.rvec,r.tvec);
            std::cout<<matrix<<std::endl;


            //if (r.confidence > 0.5 && r.contourPoints)
            {
                std::vector<std::vector<cv::Point> > cpts(1);
                cpts[0].resize(r.nContourPoints);
                memcpy(&cpts[0][0], r.contourPoints, sizeof(cv::Point)*r.nContourPoints);
                cv::polylines(img, cpts, true, Scalar(255, 0, 0), 2);
            }
        }

        imshow("result", img);

        if (waitKey(2) == 'q')
            break;
    }
}


*/