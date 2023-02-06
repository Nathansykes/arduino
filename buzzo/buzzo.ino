#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4Buzzer buzzer;

int NOTE_B0;
int NOTE_C1;
int NOTE_CS1;
int NOTE_D1;
int NOTE_DS1;
int NOTE_E1;
int NOTE_F1;
int NOTE_FS1;
int NOTE_G1;
int NOTE_GS1;
int NOTE_A1;
int NOTE_AS1;
int NOTE_B1;
int NOTE_C2;
int NOTE_CS2;
int NOTE_D2;
int NOTE_DS2;
int NOTE_E2;
int NOTE_F2;
int NOTE_FS2;
int NOTE_G2;
int NOTE_GS2;
int NOTE_A2;
int NOTE_AS2;
int NOTE_B2;
int NOTE_C3;
int NOTE_CS3;
int NOTE_D3;
int NOTE_DS3;
int NOTE_E3;
int NOTE_F3;
int NOTE_FS3;
int NOTE_G3;
int NOTE_GS3;
int NOTE_A3;
int NOTE_AS3;
int NOTE_B3;
int NOTE_C4;
int NOTE_CS4;
int NOTE_D4;
int NOTE_DS4;
int NOTE_E4;
int NOTE_F4;
int NOTE_FS4;
int NOTE_G4;
int NOTE_GS4;
int NOTE_A4;
int NOTE_AS4;
int NOTE_B4;
int NOTE_C5;
int NOTE_CS5;
int NOTE_D5;
int NOTE_DS5;
int NOTE_E5;
int NOTE_F5;
int NOTE_FS5;
int NOTE_G5;
int NOTE_GS5;
int NOTE_A5;
int NOTE_AS5;
int NOTE_B5;
int NOTE_C6;
int NOTE_CS6;
int NOTE_D6;
int NOTE_DS6;
int NOTE_E6;
int NOTE_F6;
int NOTE_FS6;
int NOTE_G6;
int NOTE_GS6;
int NOTE_A6;
int NOTE_AS6;
int NOTE_B6;
int NOTE_C7;
int NOTE_CS7;
int NOTE_D7;
int NOTE_DS7;
int NOTE_E7;
int NOTE_F7;
int NOTE_FS7;
int NOTE_G7;
int NOTE_GS7;
int NOTE_A7;
int NOTE_AS7;
int NOTE_B7;
int NOTE_C8;
int NOTE_CS8;
int NOTE_D8;
int NOTE_DS8;
int REST;

// change this to make the song slower or faster
int tempo;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[175];

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;
int divider;
int noteDuration;

void setNotes()
{
  NOTE_B0 = 31;
  NOTE_C1 = 33;
  NOTE_CS1 = 35;
  NOTE_D1 = 37;
  NOTE_DS1 = 39;
  NOTE_E1 = 41;
  NOTE_F1 = 44;
  NOTE_FS1 = 46;
  NOTE_G1 = 49;
  NOTE_GS1 = 52;
  NOTE_A1 = 55;
  NOTE_AS1 = 58;
  NOTE_B1 = 62;
  NOTE_C2 = 65;
  NOTE_CS2 = 69;
  NOTE_D2 = 73;
  NOTE_DS2 = 78;
  NOTE_E2 = 82;
  NOTE_F2 = 87;
  NOTE_FS2 = 93;
  NOTE_G2 = 98;
  NOTE_GS2 = 104;
  NOTE_A2 = 110;
  NOTE_AS2 = 117;
  NOTE_B2 = 123;
  NOTE_C3 = 131;
  NOTE_CS3 = 139;
  NOTE_D3 = 147;
  NOTE_DS3 = 156;
  NOTE_E3 = 165;
  NOTE_F3 = 175;
  NOTE_FS3 = 185;
  NOTE_G3 = 196;
  NOTE_GS3 = 208;
  NOTE_A3 = 220;
  NOTE_AS3 = 233;
  NOTE_B3 = 247;
  NOTE_C4 = 262;
  NOTE_CS4 = 277;
  NOTE_D4 = 294;
  NOTE_DS4 = 311;
  NOTE_E4 = 330;
  NOTE_F4 = 349;
  NOTE_FS4 = 370;
  NOTE_G4 = 392;
  NOTE_GS4 = 415;
  NOTE_A4 = 440;
  NOTE_AS4 = 466;
  NOTE_B4 = 494;
  NOTE_C5 = 523;
  NOTE_CS5 = 554;
  NOTE_D5 = 587;
  NOTE_DS5 = 622;
  NOTE_E5 = 659;
  NOTE_F5 = 698;
  NOTE_FS5 = 740;
  NOTE_G5 = 784;
  NOTE_GS5 = 831;
  NOTE_A5 = 880;
  NOTE_AS5 = 932;
  NOTE_B5 = 988;
  NOTE_C6 = 1047;
  NOTE_CS6 = 1109;
  NOTE_D6 = 1175;
  NOTE_DS6 = 1245;
  NOTE_E6 = 1319;
  NOTE_F6 = 1397;
  NOTE_FS6 = 1480;
  NOTE_G6 = 1568;
  NOTE_GS6 = 1661;
  NOTE_A6 = 1760;
  NOTE_AS6 = 1865;
  NOTE_B6 = 1976;
  NOTE_C7 = 2093;
  NOTE_CS7 = 2217;
  NOTE_D7 = 2349;
  NOTE_DS7 = 2489;
  NOTE_E7 = 2637;
  NOTE_F7 = 2794;
  NOTE_FS7 = 2960;
  NOTE_G7 = 3136;
  NOTE_GS7 = 3322;
  NOTE_A7 = 3520;
  NOTE_AS7 = 3729;
  NOTE_B7 = 3951;
  NOTE_C8 = 4186;
  NOTE_CS8 = 4435;
  NOTE_D8 = 4699;
  NOTE_DS8 = 4978;
  REST = 0;
}

void setMelody()
{
  int melody2[] = {

      // Dart Vader theme (Imperial March) - Star wars
      // Score available at https://musescore.com/user/202909/scores/1141521
      // The tenor saxophone part was used

      NOTE_AS4, 8, NOTE_AS4, 8, NOTE_AS4, 8, // 1
      NOTE_F5, 2, NOTE_C6, 2,
      NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F6, 2, NOTE_C6, 4,
      NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F6, 2, NOTE_C6, 4,
      NOTE_AS5, 8, NOTE_A5, 8, NOTE_AS5, 8, NOTE_G5, 2, NOTE_C5, 8, NOTE_C5, 8, NOTE_C5, 8,
      NOTE_F5, 2, NOTE_C6, 2,
      NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F6, 2, NOTE_C6, 4,

      NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F6, 2, NOTE_C6, 4, // 8
      NOTE_AS5, 8, NOTE_A5, 8, NOTE_AS5, 8, NOTE_G5, 2, NOTE_C5, -8, NOTE_C5, 16,
      NOTE_D5, -4, NOTE_D5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
      NOTE_F5, 8, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 4, NOTE_D5, 8, NOTE_E5, 4, NOTE_C5, -8, NOTE_C5, 16,
      NOTE_D5, -4, NOTE_D5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,

      NOTE_C6, -8, NOTE_G5, 16, NOTE_G5, 2, REST, 8, NOTE_C5, 8, // 13
      NOTE_D5, -4, NOTE_D5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
      NOTE_F5, 8, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 4, NOTE_D5, 8, NOTE_E5, 4, NOTE_C6, -8, NOTE_C6, 16,
      NOTE_F6, 4, NOTE_DS6, 8, NOTE_CS6, 4, NOTE_C6, 8, NOTE_AS5, 4, NOTE_GS5, 8, NOTE_G5, 4, NOTE_F5, 8,
      NOTE_C6, 1

  };
  for(int i = 0; i < sizeof(melody2); i++)
  {
    melody[i] = melody2[i];
  }
}

void setup()
{
  Serial.begin(9600);
  setNotes();
  setMelody();
  tempo = 108;

  notes = sizeof(melody) / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  wholenote = (60000 * 4) / tempo;
  divider = 0;
  noteDuration = 0;
}

void loop()
{
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2)
  {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0)
    {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    }
    else if (divider < 0)
    {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
    Serial.write("\r\n");
    Serial.write(melody[thisNote]);
    Serial.write("\t");
    Serial.write(noteDuration);

    // we only play the note for 90% of the duration, leaving 10% as a pause
    buzzer.playFrequency(melody[thisNote], noteDuration, 5);
    delay(noteDuration);
  }
}
