#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

#ifndef MATRIX_IMAGE_H
#define MATRIX_IMAGE_H
class MatrixImage
{
    private:
        //PRIVATE ATTRIBUTES
        string code;
        int columns, rows;
        int dataSize;
        int whiteMaxValue;
        unsigned int *** matrix;

        //PRIVATE METHODS
        void Clear();
        void Initialize();
        void LoadImage(string & filename);

    public:
        //CONSTRUCTOR
        MatrixImage(string filename);
        //DESTRUCTOR
        ~MatrixImage();

        //PUBLIC METHODS
        ///write image
        void WriteImage(string & filename);

        ///operations
        void Inverse();
        void ColorToGrayscale();
        void SetMax(unsigned int max);
        void SetMin(unsigned int min);

        //TODO
        void StandardBlur(int width, int weight, int radius);
        void Histogram();

        //OPERATOR OVERLOAD
        MatrixImage & operator=(const MatrixImage & other);
};
#endif MATRIX_IMAGE_H