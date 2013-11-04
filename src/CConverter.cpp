#include "CConverter.h"

CConverter::CConverter() { 

   m_wCharBuffer = new wchar_t[1023]; 

} 

CConverter::~CConverter()  { 

   delete[] m_wCharBuffer; 

} 

const wchar_t* CConverter::strToWchart(std::string sInput) { 

   size_t* sizeOut = new size_t; 
   size_t sizeInWords = 256; 
   
   const char* cStr; 
   cStr = sInput.c_str();
   //mbstowcs_s( sizeOut, m_wCharBuffer, sizeInWords, cStr, strlen(cStr)+1);
   mbstowcs(m_wCharBuffer, cStr, sizeInWords);
    
   delete sizeOut; 
   return m_wCharBuffer; 

}

const std::string CConverter::wchartToStr(const wchar_t* wInput) {
   
   std::string sOutput = ""; 
   size_t* nbOfChar = new size_t; 
   char* cOut = new char[1023]; 
   size_t sizeInBytes = 1023; 
   
   //wcstombs_s( nbOfChar, cOut, sizeInBytes, wInput, 1023);
   wcstombs(cOut,wInput,sizeInBytes); 
   sOutput += cOut; 
   
   delete nbOfChar; 
   delete[] cOut; 
   return sOutput; 
   
}
