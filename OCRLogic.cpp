/*
* this file contains all of the information used to perform tesseract on a file
* there are minor adjustments to the program for my personal use, specifically the 1920x1080 cropping
* the actual processing used (grayscale, resize, cropping) allowed for tesseract to more accurately read text from the image
* i tried other types of processing, but this allowed for the most accurate results
*/

#include "pch.h"

namespace fs = std::filesystem;
using namespace OCRLogic;

System::String^ OCR::PerformOCR(System::String^ imagePath)
{
    // gets the path of where it'll be executing from
    fs::path exePath = fs::current_path();
    fs::path tessdataPath = exePath / "tessdata";  

    // sets TESSDATA_PREFIX environment variable
    _putenv(("TESSDATA_PREFIX=" + tessdataPath.string()).c_str());
    // gets image path
    std::string image_path = msclr::interop::marshal_as<std::string>(imagePath);

    // initializes tesseract
    tesseract::TessBaseAPI tess;

    // tells tesseract to use engBest (more training than just eng)
    if (tess.Init(NULL, "engBest")) {
        return "Tesseract failed at initialization. Make sure engBest is in tessdata folder" + 
            msclr::interop::marshal_as<System::String^>(tessdataPath.string());;
    }

    // tells tesseract what characters there are so it's not getting confused
    tess.SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_");
    // one of the possible options for tesseract to identify text, this specifically (6) is for uniform blocks of text
    tess.SetVariable("tessedit_pageseg_mode", "6");


    // loads the image using leptonica
    Pix* image = pixRead(image_path.c_str());
    if (image == NULL) {
        return "Failed to read image!";
    }

    // if the image is exactly 1920x1080, it will automatically crop it down so the useless text will be trimmed off
    int imageY = pixGetHeight(image);
    int imageX = pixGetWidth(image);
    if (imageY == 1080 && imageX == 1920) {
        BOX* cropBox = boxCreate(600, 350, 850, 536);
        PIX* croppedImage = pixClipRectangle(image, cropBox, NULL);
        pixDestroy(&image);
        image = croppedImage;
    }

    // convert the image to grayscale
    Pix* grayImage = pixConvertTo8(image, 0);
    if (grayImage == NULL) {
        pixDestroy(&image);
        return "Failure when converting image to grayscale";
    }

    // resize the image
    Pix* resizedImage = pixScale(grayImage, 2.5, 2.5);
    if (resizedImage == NULL) {
        pixDestroy(&image);
        pixDestroy(&grayImage);
        return "Failure when resizing the image";
    }


    // set the processed image for OCR
    tess.SetImage(resizedImage);


    // perform OCR and output the result
    std::string outText = tess.GetUTF8Text();
    if (outText.empty()) {
        return "No text found";
    }


    // clean up resources
    pixDestroy(&image);
    pixDestroy(&grayImage);
    pixDestroy(&resizedImage);

    // return result
    return msclr::interop::marshal_as<System::String^>(outText);
}