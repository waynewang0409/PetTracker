Button_c button_back;  
Button_c button_forgetpass;
Button_c button_regis;
Button_c button_term;
Button_c button_login;
Button_c button_login2;
Button_c button_pet;
Button_c button_newpet;
Button_c button_save_change;
Button_c button_health;
Button_c button_GPS;
Button_c button_Society;
Button_c button_Condition;
Button_c button_Positure;
Button_c button_Hosiptal;
Button_c button_Hosiptal1;

Database db = new Database();
PImage my_img;
int state;
String machinecode;
AllData api = new AllData();

void setup() {
      surface.setTitle("Pet Tracker");
  
      size( 375, 667 );
      
    
      button_back = new Button_c( 24, 41, 30 );
      button_forgetpass = new Button_c( 250, 333, 30 );
      button_regis = new Button_c( 240,435,30);
      button_term = new Button_c( 100,597,100);
      button_login = new Button_c( 150,380,100);
      button_login2 = new Button_c( 180,570,100);
      button_pet = new Button_c( 220,212,47);
      button_newpet = new Button_c(350,643,47);
      button_save_change = new Button_c(180,620,75);
      button_health = new Button_c(77,324,95);
      button_GPS = new Button_c(187,327,95);
      button_Society = new Button_c(300,327,95);
      button_Condition = new Button_c(310,256,45);
      button_Positure = new Button_c(314,416,45);
      button_Hosiptal = new Button_c(314,489,45);
      button_Hosiptal1 = new Button_c(218,178,30);
      
      state = 1;
      refreshData();
    }
    
    void draw() {
      
      String img;
      switch(state){
        case 1:
            img = Login;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_forgetpass.draw();
            button_regis.draw();
            button_term.draw();
            button_login.draw();  
            break;
            
        case 10:
            img = Forget_password;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_term.draw();
            button_back.draw();
            button_login.draw();
            break;
        case 11:
            img = Register;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_back.draw();
            button_login2.draw();
            break;
        case 12:
            img = Term_and_condition;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_back.draw();
            break;
        case 2:
            img = My_pets;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_back.draw();
            button_pet.draw();
            button_newpet.draw();
            break;
        case 21:
            img = New_pets;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_save_change.draw();
            button_back.draw();
            break;
        case 3:
            img = Main;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_back.draw();
            button_health.draw();
            button_GPS.draw();
            button_Society.draw();
            break;
        case 31:
            img = GPS;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_back.draw();
            break;
        case 32:
            img = Society;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_back.draw();
            break;
        case 4:
            img = Health;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_back.draw();
            button_Condition.draw();
            button_Positure.draw();
            button_Hosiptal.draw();
            break;
        case 41:
            img = Pet_condition;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_back.draw();
            button_save_change.draw();
            break;
        case 42:
            img = Posture;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_back.draw();
            break;
        case 5:
            img = Hosiptal;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_back.draw();
            button_Hosiptal1.draw();
            break;
        case 51:
            img = Hosiptal1;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_back.draw();
            break;
        default:
            img = Login;
            my_img = loadImage(img);
            image( my_img, 0, 0 );
            button_forgetpass.draw();
            button_regis.draw();
            button_term.draw();
            button_login.draw(); 
            break;
      }
      
    }
    
    // Check the status of our buttons
    void mouseReleased() {
      
      if( button_back.checkClick() ) {
        if(state<10){
          state--;
        }
        if(state>=10){
          state = state/10;
        }
        if(state < 0){
          state = 0;
        }
        
      }
      if( button_forgetpass.checkClick() ){
        state = 10;
        }
        
      if( button_regis.checkClick() ){
        state = 11;
        }
        
      if( button_term.checkClick() ){
        state = 12;
        }
        
      if( button_login.checkClick()||  button_login2.checkClick()){
        state = 2;
        }
        
       if( button_pet.checkClick()){
        state ++;
        }
        
       if( button_newpet.checkClick()){
        state = 21;
        }
        
       if( button_save_change.checkClick()){
         if(state == 21){
            state = 2;
         }
          if(state == 41){
            state = 4;
         }
        }
        
       if(button_health.checkClick()){
         state = 4;
       }
       
       if(button_GPS.checkClick()){
         state = 31;
       }  
       
       if(button_Society.checkClick()){
         state = 32;
       }   
       
       if(button_Condition.checkClick()){
         state = 41;
       }   
       
       if(button_Positure.checkClick()){
         state = 42;
       }   
       
       if(button_Hosiptal.checkClick()){
         state = 5;
       }   
       
       if(button_Hosiptal1.checkClick()){
         state = 51;
       }
       
    
      
    }
