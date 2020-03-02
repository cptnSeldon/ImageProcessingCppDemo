#include "arrayImage.cpp"

int main()
{
    string original_washington = "Originals/washington.ascii.pbm";
    string original_aligator = "Originals/gator.ascii.pgm";
    string original_blackbuck = "Originals/blackbuck.ascii.ppm";

    string inverse_washington = "Copies/inverse_washington.pbm";

    string inverse_aligator = "Copies/inverse_aligator.pgm";
    string max125_aligator = "Copies/max125_aligator.pgm";
    string min50_aligator = "Copies/min50_aligator.pgm";

    string inverse_blackbuck = "Copies/inverse_blackbuck.ppm";
    string grayscale_blackbuck = "Copies/grayscale_blackbuck.ppm";

    #pragma region WASHINGTON
    //INVERSE
    ArrayImage * image = new ArrayImage(original_washington);

    image->Inverse();
    image->WriteImage(inverse_washington);
    #pragma endregion WASHINGTON

    #pragma region ALIGATOR
    //INVERSE
    image = new ArrayImage(original_aligator);

    image->Inverse();
    image->WriteImage(inverse_aligator);

    //SET MAX
    image = new ArrayImage(original_aligator);

    image->SetMax(125);
    image->WriteImage(max125_aligator);

    //SET MIN
    image = new ArrayImage(original_aligator);

    image->SetMin(50);
    image->WriteImage(min50_aligator);
    #pragma endregion ALIGATOR

    #pragma region BLACKBUCK
    //INVERSE
    image = new ArrayImage(original_blackbuck);

    image->Inverse();
    image->WriteImage(inverse_blackbuck);

    //COLOR -> GRAYSCALE
    image = new ArrayImage(original_blackbuck);

    image->ColorToGrayscale();
    image->WriteImage(grayscale_blackbuck);
    #pragma endregion BLACKBUCK

    delete image;
    image = nullptr;

    return 0;
}