#ifndef CCONVERTER_H
#define CCONVERTER_H

#include <string>
#include <stdlib.h>

class CConverter {
   
   public:
   
      CConverter();
      ~CConverter();

      const wchar_t* strToWchart(std::string sInput);
      const std::string wchartToStr(const wchar_t* wInput);
   
      wchar_t *m_wCharBuffer;
      
};

#endif
