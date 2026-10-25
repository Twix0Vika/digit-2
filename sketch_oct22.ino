const int PIN_temp = A0;
const int redPin = 5;
const int greenPin = 6;
const int bluePin = 9;
const int fireDanger = 4;
const int highTemp = 3;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(fireDanger, INPUT);
  pinMode(PIN_temp, INPUT);
  pinMode(highTemp, OUTPUT);
}

void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void LED(bool danger, bool warning, bool nodanger) {
  Serial.println(danger);
  Serial.println(warning);
  Serial.println(safe);
  if (danger) {
    setColor(255, 0, 0);
    delay(1000);
    setColor(0, 0, 0);
    delay(1000);
  }
  if (warning) {
    setColor(255, 50, 0);
    delay(1000);
    setColor(0, 0, 0);
    delay(1000);
  }
  if (nodanger) {
    setColor(255, 255, 255);
    delay(1000);
    setColor(0, 0, 0);
    delay(1000);
  }
}
float ReadNtcTemperature()
{
  const int   ADC_MAX   = 1023;          
  const float RSER_OHM  = 4700.0;         
  const float R0_OHM    = 10000.0;       
  const float BETA      = 3950.0;         
  const float T0_K      = 25.0 + 273.15;  

  int adc = analogRead(PIN_NTC);
  if (adc < 1)
  {
    adc = 1; 
  }

  float Rntc = RSER_OHM * ( (float)ADC_MAX / (float)adc - 1.0 );

  float invT  = (1.0 / T0_K) + (1.0 / BETA) * log(Rntc / R0_OHM);

  float tempK = 1.0 / invT;
  float tempC = tempK - 273.15;
  return tempC;
}

void loop()
{
noDanger = false;
isWarning = false;
isDanger = false;
int state = digitalRead(readDanger);
float temp = ReadNtcTemperature();
Serial.println(temp);

if(temp > 40) 
{
  digitalWrite(highTemp, HIGH);
}
else 
{
  digitalWrite(highTemp,LOW);
}

if(state == HIGH)
 {
  isDanger = true;
}

else if(temp <  35)
 {
  noDanger = true;
} 

else if(temp < 40 && temp > 35)
 {
  isWarning = true;
}
LED(isDanger, isWarning, noDanger);
}

