#define NOTE_B0  31   // B0
#define NOTE_C1  33   // C1
#define NOTE_CS1 35   // C#1/Db1
#define NOTE_D1  37   // D1
#define NOTE_DS1 39   // D#1/Eb1
#define NOTE_E1  41   // E1
#define NOTE_F1  44   // F1
#define NOTE_FS1 46   // F#1/Gb1
#define NOTE_G1  49   // G1
#define NOTE_GS1 52   // G#1/Ab1
#define NOTE_A1  55   // A1
#define NOTE_AS1 58   // A#1/Bb1
#define NOTE_B1  62   // B1
#define NOTE_C2  65   // C2
#define NOTE_CS2 69   // C#2/Db2
#define NOTE_D2  73   // D2
#define NOTE_DS2 78   // D#2/Eb2
#define NOTE_E2  82   // E2
#define NOTE_F2  87   // F2
#define NOTE_FS2 93   // F#2/Gb2
#define NOTE_G2  98   // G2
#define NOTE_GS2 104  // G#2/Ab2
#define NOTE_A2  110  // A2
#define NOTE_AS2 117  // A#2/Bb2
#define NOTE_B2  123  // B2
#define NOTE_C3  131  // C3
#define NOTE_CS3 139  // C#3/Db3
#define NOTE_D3  147  // D3
#define NOTE_DS3 156  // D#3/Eb3
#define NOTE_E3  165  // E3
#define NOTE_F3  175  // F3
#define NOTE_FS3 185  // F#3/Gb3
#define NOTE_G3  196  // G3
#define NOTE_GS3 208  // G#3/Ab3
#define NOTE_A3  220  // A3
#define NOTE_AS3 233  // A#3/Bb3
#define NOTE_B3  247  // B3
#define NOTE_C4  262  // C4 (Middle C)
#define NOTE_CS4 277  // C#4/Db4
#define NOTE_D4  294  // D4
#define NOTE_DS4 311  // D#4/Eb4
#define NOTE_E4  330  // E4
#define NOTE_F4  349  // F4
#define NOTE_FS4 370  // F#4/Gb4
#define NOTE_G4  392  // G4
#define NOTE_GS4 415  // G#4/Ab4
#define NOTE_A4  440  // A4
#define NOTE_AS4 466  // A#4/Bb4
#define NOTE_B4  494  // B4
#define NOTE_C5  523  // C5
#define NOTE_CS5 554  // C#5/Db5
#define NOTE_D5  587  // D5
#define NOTE_DS5 622  // D#5/Eb5
#define NOTE_E5  659  // E5
#define NOTE_F5  698  // F5
#define NOTE_FS5 740  // F#5/Gb5
#define NOTE_G5  784  // G5
#define NOTE_GS5 831  // G#5/Ab5
#define NOTE_A5  880  // A5
#define NOTE_AS5 932  // A#5/Bb5
#define NOTE_B5  988  // B5
#define NOTE_C6  1047 // C6
#define NOTE_CS6 1109 // C#6/Db6
#define NOTE_D6  1175 // D6
#define NOTE_DS6 1245 // D#6/Eb6
#define NOTE_E6  1319 // E6
#define NOTE_F6  1397 // F6
#define NOTE_FS6 1480 // F#6/Gb6
#define NOTE_G6  1568 // G6
#define NOTE_GS6 1661 // G#6/Ab6
#define NOTE_A6  1760 // A6
#define NOTE_AS6 1865 // A#6/Bb6
#define NOTE_B6  1976 // B6
#define NOTE_C7  2093 // C7
#define NOTE_CS7 2217 // C#7/Db7
#define NOTE_D7  2349 // D7
#define NOTE_DS7 2489 // D#7/Eb7
#define NOTE_E7  2637 // E7
#define NOTE_F7  2794 // F7
#define NOTE_FS7 2960 // F#7/Gb7
#define NOTE_G7  3136 // G7
#define NOTE_GS7 3322 // G#7/Ab7
#define NOTE_A7  3520 // A7
#define NOTE_AS7 3729 // A#7/Bb7
#define NOTE_B7  3951 // B7
#define NOTE_C8  4186 // C8
#define NOTE_CS8 4435 // C#8/Db8
#define NOTE_D8  4699 // D8
#define NOTE_DS8 4978 // D#8/Eb8
#define REST      0   // Rest



// change this to make the song slower or faster
int tempo = 120;

// change this to whichever pin you want to use
int buzzer = 11;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

NOTE_C4, 4, NOTE_C4, 8, NOTE_D4, 4, NOTE_C4, 4, NOTE_F4, 4, NOTE_E4, 2,
NOTE_C4, 4, NOTE_C4, 8, NOTE_D4, 4, NOTE_C4, 4, NOTE_G4, 4, NOTE_F4, 2,
NOTE_C4, 4, NOTE_C4, 8, NOTE_C5, 4, NOTE_A4, 4, NOTE_F4, 4, NOTE_E4, 4, NOTE_D4, 2,
NOTE_AS4, 4, NOTE_AS4, 8, NOTE_A4, 4, NOTE_F4, 4, NOTE_G4, 4, NOTE_F4, 2
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

void setup() {
 
}

void loop() {
 // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}
