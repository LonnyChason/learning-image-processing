//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
//
// FECHA INICIACION: Marzo de 2012
//
// AUTORES:
// Gustavo Adolfo Rodriguez         0932979-3743
// gustalibreros@gmail.com
//
// Edwin Fernando Muñoz             0910398-3743
// edwinfernandomudelgado@gmail.com
//
// Yerminson Doney Gonzalez         0843846-3743
// yermigon@gmail.com
//
// Edgar Andrés Moncada             0832294-3743
// edgarandres29@gmail.com
//
// ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION
// UNIVERSIDAD DEL VALLE
//**********************************************************

#include "maincontroller.h"

MainController::MainController(){
    this->imagen=0;
    this->oldImage=0;

}

MainController::~MainController(){
    delete imagen;
    imagen=0;

    delete oldImage;
    oldImage=0;

}

// LOAD IMAGE
bool MainController::loadImage(QString filename){

    QString fileExtension = filename.section(".",-1);

    if (fileExtension.toUpper() == "PGM") {
        imagen = new ImagenPGM(filename);

        if (imagen->getStatus()) {
            return true;
        }

    } else if (fileExtension.toUpper() == "PPM"){
        imagen = new ImagenPPM(filename);
        if (imagen->getStatus()) {
            return true;
        }
    }

    else{
        imagen = new ImagenDCM(filename.toStdString().c_str());
        if (imagen->getStatus()) {
            return true;
        }
    }
    return false;
}

QImage* MainController::getHistogramImage(){
    return imagen->getHistogramImage();
}

// Image Transfomations
void MainController::changeSize(int density){

    delete oldImage;
    oldImage=0;
    oldImage=imagen;
    imagen=oldImage->changeSize(density);
}

//Contrast
void MainController::gammaCorrection(double r){
    delete oldImage;
    oldImage = 0;
    oldImage = imagen;
    imagen = static_cast<ImagenPGM*>(oldImage)->gammaCorrection(r);
}

void MainController::contrastStretching(){
    delete oldImage;
    oldImage = 0;
    oldImage = imagen;
    imagen = static_cast<ImagenPGM*>(oldImage)->contrastStretching();
}

void MainController::changeColorDepth(int depth){
    QTextStream cout (stdout);

    cout<<"A. Inicio del metodo changeColorDepth en el controlador"<<endl;
    delete oldImage;
    oldImage=0;
    oldImage=imagen;
    cout<<"B. Justo Antes de llamar al metodo changeColorDepth de la clase Imagen"<<endl;
    imagen=oldImage->changeColorDepth(depth);
    imagen->saveImage("temp");
    cout<<"H. Dentro de changeColorDepth - en controlador, despues de exportar "<<endl;
}

void MainController::convertToGrayscale(int method){
    delete oldImage;
    oldImage=imagen;
    imagen=static_cast<ImagenPPM*>(oldImage)->convertToGrayScale(method);
}

bool MainController::average(QString filename, double alpha){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->average(image,alpha);
        return true;
    } else {
        return false;
    }

}

bool MainController::add(QString filename){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->add(image);
        return true;
    } else {
        return false;
    }
}

bool MainController::subtract(QString filename){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->subtract(image);
        return true;
    } else {
        return false;
    }
}

bool MainController::multiply(QString filename){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->multiply(image);
        return true;
    } else {
        return false;
    }

}

bool MainController::divide(QString filename){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->divide(image);
        imagen->saveImage("temp");
        return true;
    } else {
        return false;
    }
}

void MainController::equalizateHistogram(){
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->histogramEqualization(oldImage->getHistogram()->calculateEqualization());
}

bool MainController::bimodalSegmentaion(int T){
    if(imagen!=0){
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->bimodalSegmentaion(T);
        return true;
    }else{
        return false;
    }
}

void MainController::isodataSegmentation(){
    imagen->getHistogram()->ThresholdingByTwoPeaks();
    bimodalSegmentaion(imagen->getHistogram()->ThresholdingByIsodata());
}

void MainController::otsuSegmentation(){
    imagen->getHistogram()->ThresholdingByTwoPeaks();
    bimodalSegmentaion(imagen->getHistogram()->ThresholdingByOtsu());
}

//Filter
void MainController::meanFilter(int size){
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->meanFilter(size);
}

void MainController::convolutionFilter(int **kernel, int size){
    delete oldImage;
    oldImage=imagen;
    imagen=static_cast<ImagenPGM*>(oldImage)->convolutionFilter(kernel,size);
}

void MainController::gaussianaFilter(int size){
    delete oldImage;
    oldImage=imagen;
    imagen=static_cast<ImagenPGM*>(oldImage)->gaussianaFilter(size);
}

void MainController::noiseCleaningLine(double delta){
    delete oldImage;
    oldImage=imagen;
    imagen=static_cast<ImagenPGM*>(oldImage)->noiseCleaningLine(delta);
}

void MainController::noiseCleaningPixel(int delta){
    delete oldImage;
    oldImage=imagen;
    imagen=static_cast<ImagenPGM*>(oldImage)->noiseCleaningPixel(delta);
}

//edge Detection

void MainController::edgeDetectionSobel(int position){
    delete oldImage;
    oldImage=imagen;
    imagen=static_cast<ImagenPGM*>(oldImage)->edgeDetectionSobel(position);
}

void MainController::edgeDetectorCanny(int thresholdHigh, int thresholdDown){
    delete oldImage;
    oldImage=imagen;
    EdgeDetector ed;
    imagen=ed.edgeDetectorCanny(oldImage,thresholdHigh,thresholdDown);
}

//segmentation

void MainController::segmentationK_Means(int cluster)
{
    delete oldImage;
    oldImage=imagen;
    Segmentation sg;
    if(static_cast<ImagenPGM*>(oldImage)->getImageType()=="PGM"){
        imagen=sg.kmeansPGM(oldImage,cluster);
    }else{
        imagen=sg.kmeansPPM(oldImage,cluster);
    }

}


// DICOM
void MainController::applyWindowLevel(int window, int level){

    static_cast<ImagenDCM*>(imagen)->applyWindowLevel(window,level);
}

// Getters
Image* MainController::getImage(){
    return imagen;
}

QImage* MainController::getQImage(){
    return imagen->getQImage();
}

// Other Methods
bool MainController::undo(){
    if (oldImage!=0) {
        imagen=oldImage;
        oldImage=0;
        return true;
    }else{
        return false;
    }
}

bool MainController::isThereAnUploadedImage(){
    if(imagen!=0){
        return true;
    }else{
        return false;
    }
}

void MainController::saveImage(QString filename){
    imagen->saveImage(filename);
}


