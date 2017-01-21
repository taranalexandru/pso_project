#include "FaceDetector.h"


FaceDetector :: FaceDetector()
{
    haarCascadeClassifier = new CascadeClassifier();
    if(!(haarCascadeClassifier->load("/home/alex/opencv/data/haarcascades/haarcascade_frontalface_default.xml")))
    {
        fprintf(stderr, "Error loading Haar Cascade Classifier!\n");
        exit(EXIT_FAILURE);
    }
    facesNumber = 0;
}

FaceDetector :: ~FaceDetector()
{

}

void FaceDetector :: detectFaces(Mat &img)
{
    //Mat grey;
    //cvtColor(img, grey, COLOR_RGB2GRAY);
    haarCascadeClassifier->detectMultiScale(img, faces, 1.1, 3, 0,
                                            Size (img.rows/5, img.rows/5),
                                            Size (img.rows *2/3, img.rows*2/3));
    facesNumber = faces.size();
}

bool FaceDetector :: processFrame(Mat &img)
{
    detectFaces(img);
    for(int i = 0; i < facesNumber; i++)
    {
        rectangle(img, faces[i], CV_RGB(0, 255, 0), 1);        
    }
    return true;
}