/*
* this file contains all of the information used to design the actual form itself
*/


#pragma once
#include "pch.h"

namespace TesseractWinForms {
    using namespace System;
    using namespace System::Windows::Forms;

    public ref class Form1 : public System::Windows::Forms::Form
    {
    public:
        Form1(void)
        {
            InitializeComponent();
        }

    protected:
        ~Form1()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        // declare controls
        System::Windows::Forms::Button^ btnOCR;
        System::Windows::Forms::RichTextBox^ txtResult;
        System::Windows::Forms::OpenFileDialog^ openFileDialog1;




    private: System::Windows::Forms::Label^ buttonInfo;

        System::ComponentModel::IContainer^ components;

    private:
        // button click event to start OCR
        System::Void btnOCR_Click(System::Object^ sender, System::EventArgs^ e)
        {
            /*
            * open file dialog to select multiple images
            * as well as filtering so only certain images are allowed to be used
            */
            openFileDialog1->Multiselect = true;  
            openFileDialog1->Filter = "Image Files|*.jpg;*.jpeg;*.png;*.bmp;*.tiff;";
            openFileDialog1->Title = "Select Images";

            if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                // allows multiple files to be used
                for (int i = 0; i < openFileDialog1->FileNames->Length; i++)
                {
                    String^ imagepath = openFileDialog1->FileNames[i];

                    // performs OCR on the file
                    String^ result = OCRLogic::OCR::PerformOCR(imagepath);

                    // allows multiple results to append to the ends of each other
                    txtResult->AppendText(result + Environment::NewLine + Environment::NewLine);
                }
            }
        }

    private:
        // code used to initialize the form assets
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
            this->btnOCR = (gcnew System::Windows::Forms::Button());
            this->txtResult = (gcnew System::Windows::Forms::RichTextBox());
            this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
            this->buttonInfo = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // btnOCR

            this->btnOCR->Location = System::Drawing::Point(711, 453);
            this->btnOCR->Name = L"btnOCR";
            this->btnOCR->Size = System::Drawing::Size(107, 41);
            this->btnOCR->TabIndex = 0;
            this->btnOCR->Text = L"Run OCR";
            this->btnOCR->UseVisualStyleBackColor = true;
            this->btnOCR->Click += gcnew System::EventHandler(this, &Form1::btnOCR_Click);
            // txtResult

            this->txtResult->AcceptsTab = true;
            this->txtResult->BackColor = System::Drawing::SystemColors::MenuText;
            this->txtResult->Cursor = System::Windows::Forms::Cursors::Arrow;
            this->txtResult->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->txtResult->Location = System::Drawing::Point(42, 49);
            this->txtResult->Name = L"txtResult";
            this->txtResult->Size = System::Drawing::Size(776, 397);
            this->txtResult->TabIndex = 1;
            this->txtResult->Text = L"";
            // buttonInfo

            this->buttonInfo->AutoSize = true;
            this->buttonInfo->Location = System::Drawing::Point(39, 467);
            this->buttonInfo->Name = L"buttonInfo";
            this->buttonInfo->Size = System::Drawing::Size(429, 26);
            this->buttonInfo->TabIndex = 3;
            this->buttonInfo->Text = L"Press \'Run OCR\' to Attach a File to Translate Image to Text. Results Are Mostly A"
                L"ccurate.\r\nBDO Warscores Are Auto-Cropped When Screenshotting in a 1920x1080 Form"
                L"at.\r\n";
            // Form1

            this->AcceptButton = this->btnOCR;
            this->ClientSize = System::Drawing::Size(859, 520);
            this->Controls->Add(this->buttonInfo);
            this->Controls->Add(this->txtResult);
            this->Controls->Add(this->btnOCR);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Name = L"Form1";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Tesseract OCR with WinForms";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
    };
}
