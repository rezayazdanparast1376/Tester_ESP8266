#include "nsr_str.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "defs.h"


Float nsr_atof(Char* str) {
    if (str == NULL) {
        return 0;
    }

    Float   int_value   = 0;
    double float_value = 0.0;
    Char* ch  = strchr(str, '.');
    int_value = atoi(str);

    Int32 factor = strlen(str) - ((ch + 1) - str);
    factor = pow(10, factor);
    if ((ch + 1) != NULL) {
        float_value = atoi(ch + 1);
        float_value = float_value;
        float_value = float_value * (1.0f / factor);
        // float_value = float_value - 0.000000001;
    }
    Float test = (Float) float_value;
    test = test + int_value;
    test = roundl(test*10) / 10;

    float_value = (double)int_value + float_value;
    float_value = ((Int32)(float_value*10)) / (10.0);
//    float_value = roundl(float_value);
    return (Float)float_value;
}



Float stof(const Char* s){
  Float rez = 0, fact = 1;
  if (*s == '-'){
    s++;
    fact = -1;
  };
  for (Int32 point_seen = 0; *s; s++){
    if (*s == '.'){
      point_seen = 1; 
      continue;
    };
    Int32 d = *s - '0';
    if (d >= 0 && d <= 9){
      if (point_seen) fact /= 10.0f;
      rez = rez * 10.0f + (Float)d;
    };
  };
  return rez * fact;
};












