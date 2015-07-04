  #include<Servo.h>

Servo rshoulder, lshoulder, relbow, lelbow, rleg1, rleg2, lleg1, lleg2, rknee1, rknee2, lknee1, lknee2;

int first;          //Boolean for detecting scode
int scode;          //Determines which joint to move
int degree;         //Degrees by which to move servo

//Vars to hold current position of servo
int rlegprev;       
int llegprev;

int rkneeprev;
int lkneeprev;

void setup(){
	//Initialize Seial Baud Rate
	Serial.begin(9600);



        //Attach and map servos to pins
	lshoulder.attach(13);   //Person's left shoulder mapped to right shoulder of bot
	rshoulder.attach(12);   //Person's right shoulder mapped to left shoulder of bot
        lelbow.attach(11);      //Person's left elbow mapped to right elbow of bot
	relbow.attach(10);      //Person's right elbow mapped to left elbow of bot

        rleg1.attach(9);        //Person's left leg mapped to right leg of bot
        rleg2.attach(8);
        lleg1.attach(7);        //Person's right leg mapped to left lef of bot
        lleg2.attach(6);       
        rknee1.attach(5);       //Person's left knee mapped to right knee of bot
        rknee2.attach(4);
        lknee1.attach(3);       //Person's right knee mapped to left knee of bot 
        lknee2.attach(2);
        

        //Set initial position of servos acc. to joint
	lshoulder.write(0);
	rshoulder.write(180);

	lelbow.write(10);
	relbow.write(190);

        rleg1.write(0);
        rleg2.write(180);
        
        lleg1.write(0);
        lleg2.write(180);
        
        rknee1.write(0);
        rknee2.write(100);
        
        lknee1.write(10);
        lknee2.write(100);

        //Initialize other vars
	degree=0;
	first=0;
        rlegprev=0;
        llegprev=0;
        rkneeprev=10;
        lkneeprev=10;

}


//Function to move servo
void moveServo(int code, int n){
        int i,j;
         
        //Switch case to determine joint by scode
	switch(code){
		case 1 : rshoulder.write(n);
		break;
		case 2 : relbow.write(n);
		break;
		case 3 : lshoulder.write(n);
		break;
		case 4 : lelbow.write(n);
                break;
                //Legs and knees use 2 servos each. Hence, moved with for loop using last known position of servo 
                case 5 : 
                         for(i=180-(rlegprev); i!=n;){
                           rleg2.write(i);
                           //rleg2.write(j);
                           
                           if(i<n){
                             i++;
                           }
                           else{
                             i--;
                           }
                           
                           /*
                           if(j<180-rlegprev){
                             j++;
                           }
                           else{
                             j--;
                           }
                           */
                         }
                         rlegprev=n;
                break;
                case 6 : 
                         for(i=190-(rkneeprev+10); i!=n;){
                           rknee1.write(i);
                           //rknee2.write(j);
                           
                           if(i<n){
                             i++;
                           }
                           else{
                             i--;
                           }
                           /*
                           if(j<100-(rkneeprev-10)){
                             j++;
                           }
                           else{
                             j--;
                           }
                           */
                         }
                         rkneeprev=n;
                break;
                case 7 : 
                          for(i=llegprev,j=180-llegprev; i!=n;){
                           lleg1.write(i);
                           lleg2.write(j);
                           
                           if(i<n){
                             i++;
                           }
                           else{
                             i--;
                           }
                           
                           if(j<180-llegprev){
                             j++;
                           }
                           else{
                             j--;
                           }
                         }
                         llegprev=n;
                break;
                case 8 : 
                         for(i=lkneeprev,j=90-(lkneeprev-10); i!=n;){
                           rleg1.write(i);
                           rleg2.write(j);
                           
                           if(i<n){
                             i++;
                           }
                           else{
                             i--;
                           }
                           
                           if(j<90-(lkneeprev-10)){
                             j++;
                           }
                           else{
                             j--;
                           }
                         }
                         lkneeprev=n;
                break;
                          
	}
}


void loop(){

	if(Serial.available()>0){                                                      //Check if serial input is available. 
		int x;
		char inChar = (char)Serial.read();                                     //Read character from serial buffer

		if(first==0){                                                          //Getting scode
		      int x;
		      switch(int(inChar)){
		        case 48: x=0;
		          break;
		        case 49: x=1;
		          break;
		        case 50: x=2;
		          break;
		        case 51: x=3;
		          break;
		        case 52: x=4;
		          break;
		        case 53: x=5;
		          break;
		        case 54: x=6;
		          break;
		        case 55: x=7;
		          break;
		        case 56: x=8;
		          break;
		        case 57: x=9;
		          break;
		      }
                        scode=x;
			first=1;
		}
		else{

		      if((int)inChar>=48 && (int)inChar<=57){                            //Getting degree 
		      int x;
		      switch(int(inChar)){
		        case 48: x=0;
		          break;
		        case 49: x=1;
		          break;
		        case 50: x=2;
		          break;
		        case 51: x=3;
		          break;
		        case 52: x=4;
		          break;
		        case 53: x=5;
		          break;
		        case 54: x=6;
		          break;
		        case 55: x=7;
		          break;
		        case 56: x=8;
		          break;
		        case 57: x=9;
		          break;
		      }
      
      		degree = (degree*10) + x;
   			}
		}

		if (inChar == '\n') {                                                        //On encountering a new line character

		    if(degree>=0 && degree<=190){
			    moveServo(scode, degree);                                        //Call moveServo with the aquired arguments
		    }

		    degree=0;                                                                //Reset first and degree for next run
		    first=0;
    	} 

	}

}
