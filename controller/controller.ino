#define BAUD_RATE 115200

#define OK '0'
#define LEFT_END 'E'
#define RIGHT_NED 'e'
#define REPEAT_ 'R' 

constexpr uint16_t make_command(byte c1, byte c2)
{
  return (uint16_t)(c2<<8|c1);
}

constexpr uint16_t PP = make_command('P','P');

//---
constexpr uint16_t AF = make_command('A','F');
constexpr uint16_t AR = make_command('A','R');

constexpr uint16_t BF = make_command('B','F');
constexpr uint16_t BR = make_command('B','R');

//---
constexpr uint16_t AE = make_command('A','E');
constexpr uint16_t Ae = make_command('A','e');

constexpr uint16_t BE = make_command('B','E');
constexpr uint16_t Be = make_command('B','e');

//---
constexpr uint16_t AA = make_command('A','A');
constexpr uint16_t Aa = make_command('A','a');

constexpr uint16_t BB = make_command('B','B');
constexpr uint16_t Bb = make_command('B','b');


uint16_t aPos = 0;
uint16_t bPos = 0;

char commandBuf;

int val;
int led_pin = 13;
byte cmdBuf[2];
byte dataBuf[2];
byte positionBuf[4];

uint16_t new_pos;

void send_position(void)
{

    byte positionBuf[4];
    positionBuf[0] = aPos;
    positionBuf[1] = aPos>>8;
    positionBuf[2] = bPos;
    positionBuf[3] = bPos>>8;
    
    Serial.write(positionBuf, 4);
    Serial.println("");
}

void make_steps(void){}

void make_forward_move(uint16_t* pos, uint16_t steps)
{
  for(uint16_t i=0; i<steps; i++, (*pos)++)
    make_steps();
  Serial.write(OK);
  Serial.println("");
}

void make_revers_move(uint16_t* pos, uint16_t steps)
{
  for(uint16_t i=0; i<steps; i++, (*pos)--)
    make_steps();
  Serial.write(OK);
  Serial.println("");
}

void return_to_origin(uint16_t* pos)
{
  (*pos) = 0;
  Serial.write(LEFT_END);
  Serial.println("");
}

void setup()
{
    Serial.begin (BAUD_RATE);
    pinMode (led_pin, OUTPUT);
}

void loop ()
{
    if (Serial.available() >=2) {
        Serial.readBytes(cmdBuf,2);
        switch (*(int*)cmdBuf)
        {
          case PP:
            send_position();
            break;
          
          case AA:
            return_to_origin(&aPos);
            break;
            
          case BB:
            return_to_origin(&bPos);
            break;
                        
          case AF:
            Serial.readBytes(dataBuf,2);
            make_forward_move(&aPos, *(uint16_t*)dataBuf);
            break;

          case AR:
            Serial.readBytes(dataBuf,2);
            make_revers_move(&aPos, *(uint16_t*)dataBuf);
            break;

          case BF:
            Serial.readBytes(dataBuf,2);
            make_forward_move(&bPos, *(uint16_t*)dataBuf);
            break;

          case BR:
            Serial.readBytes(dataBuf,2);
            make_revers_move(&bPos, *(uint16_t*)dataBuf);
            break;

          default:
            Serial.println("default");
            break;
        }

        Serial.flush();

    }
}
