#define x_input A0
#define y_input A1
#define z_input A2

const int x_print =B00000001;
const int y_print =B00000010;
const int z_print =B00000100;

const int PRINT_MODE = x_print | z_print;

int x_val;//x-axis accelercation 
int y_val;//y-axis accelercation 
int z_val;//z-axis accelercation 

void setup() {
  Serial.begin(9600);//Baud rate set as 9600.
  Serial.println(PRINT_MODE);
}

void loop() {
  x_val = analogRead(x_input);
  y_val = analogRead(y_input);
  z_val = analogRead(z_input);

  if(PRINT_MODE & x_print){
    Serial.print("x = ");
    Serial.print(x_val);
    Serial.print("\t");
  }
  
  if(PRINT_MODE & z_print){
    Serial.print("z = ");
    Serial.print(z_val);
    Serial.print("\t");
  }
  if(PRINT_MODE & y_print){
    Serial.print("y = ");
    Serial.print(y_val);
    Serial.print("\t");
  }
  
  Serial.print("\n");
  
  delay(50);
}
