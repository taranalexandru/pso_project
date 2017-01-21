#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H
#include <objdetect.hpp>
#include <core.hpp>
#include <highgui.hpp>
#include <face/facerec.hpp>
#include <face.hpp>
#include <vector>
#include <fstream>
#include <imgproc.hpp>
using namespace std;
using namespace cv;
using namespace face;

#define HAARCLASSIFIER "/home/alex/opencv/data/haarcascades/haarcascade_frontalface_default.xml"
#define DEBUGOK printf("ok\n");

class FaceDetector{
private:
    CascadeClassifier* haarCascadeClassifier;
    vector<Rect>    faces;
    int facesNumber;

    void detectFaces(Mat &img);
public:
    FaceDetector();
    ~FaceDetector();

    bool processFrame(Mat &img);
};

#endif //FACEDETECTOR_H