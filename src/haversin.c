#include "haversin.h"

double haversin (double lat1, double lon1, double lat2, double lon2){
  lat1 *= mult;
  lat2 *= mult;
  lon1 *= mult;
  lon2 *= mult;
 
  double delta1 = (lat2 - lat1)/2;
  double delta2 = (lon2 - lon1)/2;
  double d = sin(delta1)*sin(delta1) + cos(lat1)*cos(lat2)*sin(delta2)*sin(delta2);

  return R*asin(sqrt(d))*1000;
}
