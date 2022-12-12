
#define W_CLK 8
#define FQ_UD 9
#define DATA 10
#define RESET 11
#define SIGNAL_gen 2
#define SIGNAL_IN 3

int val[1];

int freq = 5; //Установить частоту в Гц

void pin_tick(byte pin)
{
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}

void write_byte(byte x)
{
  for(int i = 0; i <= 7; i++)
  {
    digitalWrite(DATA, x & 0x01);
    x >>= 1;
    pin_tick(W_CLK);
  }
}

void set_frequency(uint32_t f)
{
  for(int i = 0; i <= 3; i++)
  {
    write_byte(f & 0xFF);
    f >>= 8;
  }
  write_byte(0x00);
  pin_tick(FQ_UD);
}

void AD9850_Init()
{
  pinMode(FQ_UD, OUTPUT);
  pinMode(W_CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(RESET, OUTPUT);
  pin_tick(RESET);
  pin_tick(W_CLK);
  pin_tick(FQ_UD);
}

void setup()
{
  pinMode(SIGNAL_gen, INPUT);
  pinMode(SIGNAL_IN, INPUT);
  AD9850_Init();
  set_frequency(round(freq*pow(2, 16)/125*pow(2, 16)/1000000)); //3436 - 100 Гц, 17180  - 500 Гц, 6872 - 200 Гц, 344 - 10 Гц, 1718 - 50 Гц, 412 - 12 Гц
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available () != 0)
  {
      val[0] = analogRead (SIGNAL_gen);
      val[1] = analogRead (SIGNAL_IN);
      Serial.println (val[0]);
     // Serial.println (0);
      Serial.println (val[1]);
      
      //Serial.println (round(freq*pow(256, 4)/0.000125));
     // Serial.println (round(freq*pow(2, 16)/125*pow(2, 16)/1000000));
  }
 // delay(100);
  //delayMicroseconds(100);
}
