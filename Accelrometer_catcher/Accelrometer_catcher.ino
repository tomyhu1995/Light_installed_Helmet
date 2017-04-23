#define x_input A0
#define y_input A1
#define z_input A2

#define window_size 8

#define threshold -20

const int x_print =B00000001;
const int y_print =B00000010;
const int z_print =B00000100;

const int PRINT_MODE = x_print | z_print;

int x_val[window_size];//x-axis accelercation 
int y_val[window_size];//y-axis accelercation 
int z_val[window_size];//z-axis accelercation

int window_counter = 0;

const int left = 13;
const int right = 11;
const int red = 12;

int red_count = 0;
int right_count = 0;
int left_count = 0;

int GetMean(int *input, int Length){
  int mean = 0;
  for(int i = 0; i < Length; i++){
    mean += input[i];
  }
  return mean / Length;
}

void setup() {
  Serial.begin(9600);//Baud rate set as 9600.
  Serial.println(PRINT_MODE);

  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(red, OUTPUT);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
}

void loop() {
  x_val[window_counter] = analogRead(x_input);
  y_val[window_counter] = analogRead(y_input);
  z_val[window_counter] = analogRead(z_input);
  

  if(PRINT_MODE & x_print){
    Serial.print("x = ");
    Serial.print(x_val[window_counter]);
    Serial.print("\t");
  }
  
  if(PRINT_MODE & z_print){
    Serial.print("z = ");
    Serial.print(z_val[window_counter]);
    Serial.print("\t");
  }
  if(PRINT_MODE & y_print){
    Serial.print("y = ");
    Serial.print(y_val[window_counter]);
    Serial.print("\t");
  }

  if(x_val[window_counter] - GetMean(x_val, window_size) < threshold){
    Serial.print("mean of x = ");
    Serial.print(GetMean(x_val, window_size));
    Serial.print("\t");
    digitalWrite(red, HIGH);
    red_count = 50;
  }

  if(y_val[window_counter] - GetMean(y_val, window_size) < threshold){
    Serial.print("mean of y = ");
    Serial.print(GetMean(y_val, window_size));
    Serial.print("\t");
    digitalWrite(left, HIGH);
    left_count = 50;
  }

  if(y_val[window_counter] - GetMean(y_val, window_size) > -1 * threshold){
    Serial.print("mean of y = ");
    Serial.print(GetMean(y_val, window_size));
    Serial.print("\t");
    digitalWrite(right, HIGH);
    right_count = 50;
  }
  
  Serial.print("\n");
  
  window_counter = (window_counter + 1) % window_size;
  delay(50);
  red_count--;
  left_count--;
  right_count--;
  
  if(red_count <= 0){
    red_count = 0;
    digitalWrite(red, LOW);
  }
  if(left_count <= 0){
    left_count = 0;
    digitalWrite(left, LOW);
  }
  if(right_count <= 0){
    right_count = 0;
    digitalWrite(right, LOW);
  }
}
