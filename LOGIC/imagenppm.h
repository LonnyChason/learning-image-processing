//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: imagenppm.h
//
// FECHA INICIACION: Marzo de 2012
//
// AUTORES:
// Gustavo Adolfo Rodriguez         0932979-3743
// gustalibreros@hotmail.com
//
// Edwin Fernando Muñoz             0910398-3743
// edwinfernandomudelgado@hotmail.com
//
// ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION
// UNIVERSIDAD DEL VALLE
//**********************************************************

#ifndef IMAGENPPM_H
#define IMAGENPPM_H

#include "imagenpgm.h"
#include "image.h"
#include <QImage>
#include <QRgb>

class ImagenPPM: public Image
{
    int ***matrixRp, ***matrixGp, ***matrixBp;
    int *lutR, *lutG, *lutB;

    void generateHistogram();
    void generateQImage();
public:

    //Constructors
    ImagenPPM(QString filename);

    ImagenPPM(QString id,
              int h,
              int w,
              int depth,
              int **matrizR,
              int **matrizG,
              int **matrizB);

    ImagenPPM(QString id,
              int h,
              int w,
              int colorD,
              int ***matrizR,
              int *lutR,
              int ***matrizG,
              int *lutG,
              int ***matrizB,
              int *lutB);

    ~ImagenPPM();

    //Image processing
    Image* changeSize(int factor);
    Image* changeColorDepth(int bits);
    ImagenPGM* convertToGrayScale(int method);
    //   Image *equalizateHistogram(int *newlut);

    // Getters

    // Export
    void saveImage(QString filename);
};

#endif // IMAGENPPGM_H
