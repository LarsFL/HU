// example:
// definition of the functions of a circle class 
// you are not expected to understand how circle::print works

#include "circle.hpp"

void circle::draw(){
    
   // don't draw anything when the size would be 0 
   if( radius < 1 ){
      return;       
   }
   
   // http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
   
   int fx = 1 - radius;
   int ddFx = 1;
   int ddFy = -2 * radius;
   int x = 0;
   int y = radius;
   hwlib::xy midpoint = location;
      
   // top and bottom
   w.write( hwlib::xy( midpoint.x + 0, midpoint.y + radius ) );
   w.write( hwlib::xy( midpoint.x + 0, midpoint.y - radius ) );
      
   // left and right 
   w.write( hwlib::xy( midpoint.x + radius, midpoint.y + 0 ) );
   w.write( hwlib::xy( midpoint.x + radius, midpoint.y - 0 ) );
    
   while( x < y ){
      
      // calculate next outer circle point
      if( fx >= 0 ){
        y--;
        ddFy += 2;
        fx += ddFy;
      }
      x++;
      ddFx += 2;
      fx += ddFx;   
      
      w.write( hwlib::xy( midpoint.x + x, midpoint.y + y ) );
      w.write( hwlib::xy( midpoint.x - x, midpoint.y + y ) );
      w.write( hwlib::xy( midpoint.x + x, midpoint.y - y ) );
      w.write( hwlib::xy( midpoint.x - x, midpoint.y - y ) );
      w.write( hwlib::xy( midpoint.x + y, midpoint.y + x ) );
      w.write( hwlib::xy( midpoint.x - y, midpoint.y + x ) );
      w.write( hwlib::xy( midpoint.x + y, midpoint.y - x ) );
      w.write( hwlib::xy( midpoint.x - y, midpoint.y - x ) );
   }
}