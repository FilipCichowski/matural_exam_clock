/*
 * Matural Exam Countdown Clock
 * By Filip Cichowski
 * CC 2020
 */

// counter button definition
#define dayplus A1
#define dayminus A0
#define hourplus A3
#define hourminus A2
#define yearplus A4
#define yearminus A5

// shift register pin definitions
#define clockPin 13 // clock pin
#define dataPin 12  // data pin

// common pins of the four digits definitions
#define Dig1 5
#define Dig2 4
#define Dig3 3
#define Dig4 2
#define Dig5 6
#define Dig6 7
#define Dig7 8
#define Dig8 9
#define Dig9 10

// variable declarations
byte current_digit;
long hours = 6000;
int days = hours / 24;
void disp(byte number, bool dec_point = 0);

unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;

void setup()
{
    pinMode(dayplus, INPUT_PULLUP);
    pinMode(dayminus, INPUT_PULLUP);
    pinMode(hourplus, INPUT_PULLUP);
    pinMode(hourminus, INPUT_PULLUP);
    pinMode(yearplus, INPUT_PULLUP);
    pinMode(yearminus, INPUT_PULLUP);
    pinMode(Dig1, OUTPUT);
    pinMode(Dig2, OUTPUT);
    pinMode(Dig3, OUTPUT);
    pinMode(Dig4, OUTPUT);
    pinMode(Dig5, OUTPUT);
    pinMode(Dig6, OUTPUT);
    pinMode(Dig7, OUTPUT);
    pinMode(Dig8, OUTPUT);
    pinMode(Dig9, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    disp_off(); // turn off the display

    // Timer1 module overflow interrupt configuration
    TCCR1A = 0;
    TCCR1B = 1;
    TCNT1 = 50000; // What the fuck ?
    TIMSK1 = 1;
}

ISR(TIMER1_OVF_vect) // Timer1 interrupt service routine (ISR)
{
    disp_off(); // turn off the display
    TCNT1 = 50000;

    switch (current_digit)
    {
    case 1:
        disp(days / 1000);       // prepare to display digit 1 (most left)
        digitalWrite(Dig1, LOW); // turn on digit 1

        break;

    case 2:
        disp((days / 100) % 10); // prepare to display digit 2
        digitalWrite(Dig2, LOW); // turn on digit 2

        break;

    case 3:
        disp((days / 10) % 10);  // prepare to display digit 3
        digitalWrite(Dig3, LOW); // turn on digit 3

        break;

    case 4:
        disp(days % 10);         // prepare to display digit 4
        digitalWrite(Dig4, LOW); // turn on digit 4

        break;

    case 5:
        disp(hours / 10000);     // prepare to display digit 5
        digitalWrite(Dig5, LOW); // turn on digit 5

        break;

    case 6:
        disp((hours / 1000) % 10); // prepare to display digit 6
        digitalWrite(Dig6, LOW);   // turn on digit 6

        break;

    case 7:
        disp((hours / 100) % 10); // prepare to display digit 7
        digitalWrite(Dig7, LOW);  // turn on digit 7

        break;

    case 8:
        disp((hours / 10) % 10); // prepare to display digit 8
        digitalWrite(Dig8, LOW); // turn on digit 8

        break;

    case 9:
        disp(hours % 10);        // prepare to display digit 9 (most right)
        digitalWrite(Dig9, LOW); // turn on digit 9
    }

    current_digit = (current_digit % 9) + 1;
}

void loop()
{
    days = hours / 24;

    currentMillis = millis();                  //get the actually the number of milliseconds since the program started
    if (currentMillis - startMillis >= period) //test whether the period has elapsed
    {
        hours--;
        startMillis = currentMillis;
    }

    if (digitalRead(dayplus) == 0)
    {
        hours += 24;
    }
    else if (digitalRead(dayminus) == 0)
    {
        hours -= 24;
    }

    else if (digitalRead(hourplus) == 0)
    {
        hours++;
    }
    else if (digitalRead(hourminus) == 0)
    {
        hours--;
    }

    else if (digitalRead(yearplus) == 0)
    {
        hours += 8760;
        delay(150);
    }
    else if (digitalRead(yearminus) == 0)
    {
        hours -= 8760;
        delay(150);
    } delay(250);
}

void disp(byte number, bool dec_point)
{
    switch (number)
    {
    case 0: // print 0
        shiftOut(dataPin, clockPin, MSBFIRST, 0x02 | !dec_point);
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
        break;

    case 1: // print 1
        shiftOut(dataPin, clockPin, MSBFIRST, 0x9E | !dec_point);
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
        break;

    case 2: // print 2
        shiftOut(dataPin, clockPin, MSBFIRST, 0x24 | !dec_point);
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
        break;

    case 3: // print 3
        shiftOut(dataPin, clockPin, MSBFIRST, 0x0C | !dec_point);
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
        break;

    case 4: // print 4
        shiftOut(dataPin, clockPin, MSBFIRST, 0x98 | !dec_point);
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
        break;

    case 5: // print 5
        shiftOut(dataPin, clockPin, MSBFIRST, 0x48 | !dec_point);
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
        break;

    case 6: // print 6
        shiftOut(dataPin, clockPin, MSBFIRST, 0x40 | !dec_point);
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
        break;

    case 7: // print 7
        shiftOut(dataPin, clockPin, MSBFIRST, 0x1E | !dec_point);
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
        break;

    case 8: // print 8
        shiftOut(dataPin, clockPin, MSBFIRST, !dec_point);
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
        break;

    case 9: // print 9
        shiftOut(dataPin, clockPin, MSBFIRST, 0x08 | !dec_point);
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void disp_off()
{
    digitalWrite(Dig1, HIGH);
    digitalWrite(Dig2, HIGH);
    digitalWrite(Dig3, HIGH);
    digitalWrite(Dig4, HIGH);
    digitalWrite(Dig5, HIGH);
    digitalWrite(Dig6, HIGH);
    digitalWrite(Dig7, HIGH);
    digitalWrite(Dig8, HIGH);
    digitalWrite(Dig9, HIGH);
}