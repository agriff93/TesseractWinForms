#pragma once
#include "pch.h"
#include <string>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

namespace OCRLogic {
    public ref class OCR
    {
    public:
        static System::String^ PerformOCR(System::String^ imagePath);
    };
}
