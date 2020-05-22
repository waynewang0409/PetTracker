
class Button_c {
  
  int x;        
  int y;
  int diameter; 
  

  Button_c( int set_x, int set_y, int set_d ) {
    
    
    x = set_x;
    y = set_y;
    diameter = set_d;
    
  }
  
  void draw() {
     stroke( 0, 0, 0 );      
     strokeWeight( 2 );      
     noFill();  
     
     
     ellipse( x, y, diameter, diameter );
  }
  


  boolean checkClick() {
     float distance;
     

     distance = dist( mouseX, mouseY, x, y );
     
     distance = abs( distance );
     

     if( distance < ( diameter / 2 ) ) {
        return true; 
     } 
     
     return false;
  }
  
}
