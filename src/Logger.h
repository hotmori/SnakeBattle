#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "config.h"

#define LOG Logger::PrintLog

class Logger {
  public:

     static FILE* pFile;
     static void ResetLog() {
         if (pFile == NULL)
         {
            pFile = fopen (LOG_FILE_NAME,"w");
            fclose(pFile);
         }

     }
     static void PrintLog(const char* format, ...)
     {

      pFile = fopen(LOG_FILE_NAME,"a");

      char buffer[256];
      va_list args;
      va_start (args, format);
      vsnprintf (buffer,256,format, args);
      fprintf (pFile, strcat (buffer, "\n"));
      va_end (args);
      fclose (pFile);
    };

    static void StopLog() {
      fclose (pFile);
    };

};
