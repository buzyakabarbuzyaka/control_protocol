#define BODE_RATE 115200

int val;
int led_pin = 13;
void setup ()
{
    Serial.begin (BODE_RATE);
    pinMode (led_pin, OUTPUT);
}

void loop ()
{
    val = Serial.read();
    if (val == 'R')
    {
        digitalWrite (led_pin, HIGH);
        delay (2000);
        digitalWrite (led_pin, LOW);
        Serial.println ("Hello World!");
    }
}
