#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
String readString;
void setup() {
  //set digital pin 2-9 to be outputs
  for (int i=2; i<10; i++) {
    pinMode(i, OUTPUT);
  }
  //enabling serial ports for bluetooth addon
  Serial.begin(9600); 
  mySerial.begin(9600);
  
}

void loop(){
   manualDna();
}
void bt() {
  while (mySerial.available()) {
    delay(10);  //small delay to allow input buffer to fill

    char c = mySerial.read();  //gets one byte from serial buffer
    if (c == ',') {
      break;
    }  //breaks out of capture loop to print readstring
    readString += c; 
  } //makes the string readString  

  if (readString.length() >0) {
    Serial.println(readString); //prints string to serial port out
    stuff(readString);
    readString=""; //clears variable for new input
  }
}

void stuff(String input) {
  char dna[input.length()]; //create character array for dna sequence
  input.toCharArray(dna, input.length());  //filling array with the characters from the String recieved from bluetooth input

  for (int i=1; i<=sizeof(dna); i++) {
    if (dna[i] == 'A'){
      Serial.println("A");      //forward
      motor(2);
      motor(5);
    } else if(dna[i] == 'T') {
      Serial.println("T");//backward
      motor(3);
      motor(4);
    } else if(dna[i] == 'G') {
      Serial.println("G");
      //left
      motor(5);
    } else if(dna[i] == 'C') {
      Serial.println("C");
      //right
      motor(2);
    } else {
      
    }
    delay(50); //delay between each character
    low();
  }
    delay(1000); //delay after each completion of dna sequence
}


void motor(int pin) {
  digitalWrite(pin, HIGH);
}
void manualDna() {
  char dna[] = "GGTTTCACCATGTTGGCCAGGCTGGCCTCGAACTCCTGACCTCAGGTGATCCGCCTGCCTCAGCCTCCTAAAGTGCTGGGATTACAGGCGTGAGCCACCACACCCGGCCCCAGATCCCTGTCTTGAGACATAACCTACAAGGTGATAGTGTTAAGAGGTGGAGCCCTTTAAGACGTGATGAGGTCATGAGGGTGGGGCCT"; //manually placed dna sequence
  for (int i=0; i<sizeof(dna); i++) {
    if (dna[i] == 'A'){
      //forward
      motor(2);
      motor(5);
      Serial.println("forward");
    } else if(dna[i] == 'T') {
      //backward
      motor(3);
      motor(4);
    } else if(dna[i] == 'G') {
      //left
      motor(5);
    } else if(dna[i] == 'C') {
      //right
      motor(2);
    } else {
      
    }
    delay(50);
    low();
  }
  delay(1000);
}

void low() {
//turn off all pins
  for (int i=2; i<6; i++) {
    digitalWrite(i, LOW);
  }
}
