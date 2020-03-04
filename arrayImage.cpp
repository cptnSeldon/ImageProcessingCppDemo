#include "arrayImage.h"

//CONSTRUCTOR
ArrayImage::ArrayImage(string filename)
{
    cout << "NEW IMAGE..." << endl;
    LoadImage(filename);
}

//DESTRUCTOR
ArrayImage::~ArrayImage()
{
    cout << "DESTROY IMAGE..." << endl;
    Clear();
}

//PRIVATE METHODS
void ArrayImage::Clear()
{
    columns = 0;
    rows = 0;
    whiteMaxValue = -1;

    delete []array;
    array = nullptr;
}

void ArrayImage::Initialize()
{
    unsigned int size = columns * rows * dataSize;

    array = new unsigned int[size];

    for(int i = 0; i < size; i++)
    {
        array[i] = 0;
    }
}

void ArrayImage::LoadImage(string & filename)
{
    whiteMaxValue = -1;
    dataSize = 1;

    fstream inputfile;

    inputfile.open(filename.c_str(), fstream::in | fstream::binary);

    try
    {
        cout << "OPENING : "<< filename <<endl;

        inputfile >> code;
        inputfile >> columns >> rows;

        //black and white
        if(!(code == "P1" || code == "P4")) inputfile >> whiteMaxValue;
        //color : rgb
        if(code == "P3" ||code == "P6") dataSize = 3;

        Initialize();

        //Populate array
        for(int i = 0; i < columns * rows * dataSize; i++)
        {
            unsigned int s;
            inputfile >> s;
            array[i] = s;
        }

        inputfile.close();
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << "Exception opening/reading/closing file\n";
    }
}

//PUBLIC METHODS
///write image
void ArrayImage::WriteImage(string & filename)
{
    cout << "WRITE IMAGE : " << filename << endl;

    fstream outputFile;

    try
    {
        //clear file
        outputFile.open(filename.c_str(), fstream::out | fstream::trunc);

        //header
        outputFile << code << "\n";
        outputFile << columns << " " << rows << "\n";
        if(!(code == "P1" || code == "P4")) outputFile << whiteMaxValue<< "\n";

        //matrix
        for(int i = 0; i < columns * rows * dataSize; i++)
        {
            outputFile << array[i];
            outputFile << " ";
        }

        outputFile.close();
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    catch(std::exception const& e)
    {
        cout << "There was an error: " << e.what() << endl;
    }
}

///operations
void ArrayImage::Inverse()
{
    cout << "INVERSE IMAGE..." << endl;

    if(array == nullptr) cout << "INVERSE: array is null." << endl;
    else
    {
        for(int i = 0; i < columns * rows * dataSize; i++)
        {
            if(code == "P1" || code == "P4") array[i] = (array[i] == 0) ? 1 : 0;
            else array[i] = ~array[i]%256;
        }
    }
}

void ArrayImage::ColorToGrayscale()
{
    for(int i = 0; i < columns; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            unsigned int r = array[(i * rows + j) * dataSize + 0];
            unsigned int g = array[(i * rows + j) * dataSize + 1];
            unsigned int b = array[(i * rows + j) * dataSize + 2];

            unsigned int linearIntensity = (0.2126f * r + 0.7152f * g + 0.0722 * b);

            array[(i * rows + j) * dataSize + 0] = linearIntensity;
            array[(i * rows + j) * dataSize + 1] = linearIntensity;
            array[(i * rows + j) * dataSize + 2] = linearIntensity;
        }
    }
}

void ArrayImage::SetMax(unsigned int max)
{
    if(code == "P1" || code == "P4") cout << "SET MAX : black and white image.." << endl;
    else
    {
        if(array == nullptr) cout << "SET MAX: array is null." << endl;
        else
        {
            cout << "SET MAXIMUM SHADE TO : " << max << endl;

            whiteMaxValue = max;

            for(int i = 0; i < columns * rows * dataSize; i++)
            {
                array[i] = (array[i] > max) ? max : array[i];
            }
        }
    }
}

void ArrayImage::SetMin(unsigned int min)
{
    if(code == "P1" || code == "P4") cout << "SET MAX : black and white image.." << endl;
    else
    {
        if(array == nullptr) cout << "SET MIN: array is null." << endl;
        else
        {
            cout << "SET MINIMUM SHADE TO : " << min << endl;

            for(int i = 0; i < columns * rows * dataSize; i++)
            {
                array[i] = (array[i] < min) ? min : array[i];
            }
        }
    }
}

ArrayImage & ArrayImage::operator=(const ArrayImage & other)
{
    if(&other == this)
    {
        cout << "These images are the same !" << endl;
        return *this;
    }
    else if(code != other.code)
    {
        cout << "The images don't have the same format !" << endl;
    }
    else
    {
        cout << "Overload = !" << endl;

        Clear();

        columns = other.columns;
        rows = other.rows;
        whiteMaxValue = other.whiteMaxValue;

        //copy to array
        Initialize();

        for(int i = 0; i < columns * rows * dataSize; i++)
        {
            array[i] = other.array[i];
        }
    }
}