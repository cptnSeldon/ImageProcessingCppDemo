#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

#ifndef ARRAY_IMAGE_H
#define ARRAY_IMAGE_H

class ArrayImage
{
    private:
        //PRIVATE ATTRIBUTES
        string code;
        int columns, rows;
        int dataSize;
        int whiteMaxValue;
        unsigned int * array;

        //PRIVATE METHODS
        void Clear();
        void Initialize();
        void LoadImage(string & filename);

    public:
        //CONSTRUCTOR
        ArrayImage(string filename);
        //DESTRUCTOR
        ~ArrayImage();

        //PUBLIC METHODS
        ///write image
        void WriteImage(string & filename);

        ///operations
        void Inverse();
        void ColorToGrayscale();
        void SetMax(unsigned int max);
        void SetMin(unsigned int min);

        ArrayImage & operator=(const ArrayImage & other);
};

#endif ARRAY_IMAGE_H