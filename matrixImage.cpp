#include "matrixImage.h"

#define PI 3.14159

//CONSTRUCTOR
MatrixImage::MatrixImage(string filename)
{
    cout << "NEW IMAGE..." << endl;
    LoadImage(filename);
}
//DESTRUCTOR
MatrixImage::~MatrixImage()
{
    cout << "DESTROY IMAGE..." << endl;
    Clear();
}

//PRIVATE METHODS
void MatrixImage::Clear()
{
    //clear matrix
    for(int i = 0; i < columns; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            delete matrix[i][j];
            matrix[i][j] = nullptr;
        }
        delete matrix[i];
        matrix[i] = nullptr;
    }
    delete []matrix;
    matrix = nullptr;

    columns = 0;
    rows = 0;
    whiteMaxValue = -1;
}

void MatrixImage::Initialize()
{
    cout << "INITIALIZE IMAGE MATRIX" << endl;

    matrix = new unsigned int **[columns];

    for(int i = 0; i < columns; i++)
    {
        matrix[i] = new unsigned int *[rows];

        for(int j = 0; j < rows; j++)
        {
            matrix[i][j] = new unsigned int[dataSize];

            for(int k = 0; k < dataSize; k++)
            {
                matrix[i][j][k] = 0;
            }
        }
    }
}


void MatrixImage::LoadImage(string & filename)
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

        //Populate matrix
        for(int i = 0; i < columns; i++)
        {
            for(int j = 0; j < rows; j++)
            {
                for(int k = 0; k < dataSize; k++)
                {
                    unsigned int s;
                    inputfile >> s;
                    matrix[i][j][k] = s;
                }
            }
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
void MatrixImage::WriteImage(string & filename)
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
        for(int i = 0; i < columns; i++)
        {
            for(int j = 0; j < rows; j++)
            {
                for(int k = 0; k < dataSize; k++)
                {
                    outputFile << matrix[i][j][k];
                    if(j < rows - 1 || k != dataSize -1) outputFile << " ";
                }
            }
            outputFile << "\n";
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
void MatrixImage::Inverse()
{
    cout << "INVERSE IMAGE..." << endl;

    if(matrix == nullptr) cout << "INVERSE: matrix is null." << endl;
    else
    {
        for(int i = 0; i < columns; i++)
        {
            for(int j = 0; j < rows; j++)
            {
                for(int k = 0; k < dataSize; k++)
                {
                    if(code == "P1" || code == "P4") matrix[i][j][k] = (matrix[i][j][k] == 0) ? 1 : 0;
                    else matrix[i][j][k] = ~matrix[i][j][k]%256;
                }
            }
        }
    }
}
void MatrixImage::ColorToGrayscale()
{
    if(code == "P3" || code =="P6")
    {
        cout << "RGB TO GRAYSCALE..." << endl;

        for(int i = 0; i < columns; i++)
        {
            for(int j = 0; j < rows; j++)
            {
                unsigned int r = matrix[i][j][0];
                unsigned int g = matrix[i][j][1];
                unsigned int b = matrix[i][j][2];

                unsigned int linearIntensity = (0.2126f * r + 0.7152f * g + 0.0722 * b);

                matrix[i][j][0] = linearIntensity;
                matrix[i][j][1] = linearIntensity;
                matrix[i][j][2] = linearIntensity;
            }
        }
    }
    else
    {
        cout << "Warning : this is not a ppm image (rgb)." << endl;
    }
}
void MatrixImage::SetMax(unsigned int max)
{
    if(code == "P1" || code == "P4") cout << "SET MAX : black and white image.." << endl;
    else
    {
        if(matrix == nullptr) cout << "SET MAX: matrix is null." << endl;
        else
        {
            cout << "SET MAXIMUM SHADE TO : " << max << endl;

            whiteMaxValue = max;

            for(int i = 0; i < columns; i++)
            {
                for(int j = 0; j < rows; j++)
                {
                    for(int k = 0; k < dataSize; k++)
                    {
                        matrix[i][j][k] = (matrix[i][j][k] > max) ? max : matrix[i][j][k];
                    }
                }
            }
        }
    }
}
void MatrixImage::SetMin(unsigned int min)
{
    if(code == "P1" || code == "P4") cout << "SET MAX : black and white image.." << endl;
    else
    {
        if(matrix == nullptr) cout << "SET MIN: matrix is null." << endl;
        else
        {
            cout << "SET MINIMUM SHADE TO : " << min << endl;

            for(int i = 0; i < columns; i++)
            {
                for(int j = 0; j < rows; j++)
                {
                    for(int k = 0; k < dataSize; k++)
                    {
                        matrix[i][j][k] = (matrix[i][j][k] < min) ? min : matrix[i][j][k];
                    }
                }
            }
        }
    }
}

MatrixImage & MatrixImage::operator=(const MatrixImage & other)
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

        Initialize();

        //copy to matrix
        for(int i = 0; i < columns; i++)
        {
            for(int j = 0; j < rows; j++)
            {
                for(int k = 0; k < dataSize; k++)
                {
                    matrix[i][j][k] = other.matrix[i][j][k];
                }
            }
        }
    }
}