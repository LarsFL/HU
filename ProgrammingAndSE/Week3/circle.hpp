#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "hwlib.hpp"

class circle{
protected:
   hwlib::glcd_oled_i2c_128x64_direct& w;
   const hwlib::xy& location;
   int radius;
public:
   circle( hwlib::glcd_oled_i2c_128x64_direct & w, const hwlib::xy & midpoint, int radius ):
      w(w),
      location(midpoint),
      radius( radius )
   {}
   
   void draw();
};

#endif // CIRCLE_HPP