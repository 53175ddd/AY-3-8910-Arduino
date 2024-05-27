#define  doLL  0
#define dosLL  1
#define  reLL  2
#define resLL  3
#define  miLL  4
#define  faLL  5
#define fasLL  6
#define  soLL  7
#define sosLL  8
#define  raLL  9
#define rasLL 10
#define  siLL 11

#define   doL 12
#define  dosL 13
#define   reL 14
#define  resL 15
#define   miL 16
#define   faL 17
#define  fasL 18
#define   soL 19
#define  sosL 20
#define   raL 21
#define  rasL 22
#define   siL 23

#define   doM 24
#define  dosM 25
#define   reM 26
#define  resM 27
#define   miM 28
#define   faM 29
#define  fasM 30
#define   soM 31
#define  sosM 32
#define   raM 33
#define  rasM 34
#define   siM 35

#define   doH 36
#define  dosH 37
#define   reH 38
#define  resH 39
#define   miH 40
#define   faH 41
#define  fasH 42
#define   soH 43
#define  sosH 44
#define   raH 45
#define  rasH 46
#define   siH 47

#define  doHH 48
#define dosHH 49
#define  reHH 50
#define resHH 51
#define  miHH 52
#define  faHH 53
#define fasHH 54
#define  soHH 55
#define sosHH 56
#define  raHH 57
#define rasHH 58
#define  siHH 59

#define CH_A_R0 0
#define CH_A_R1 1
#define CH_B_R0 2
#define CH_B_R1 3
#define CH_C_R0 4
#define CH_C_R1 5

#define A 'A'
#define B 'B'
#define C 'C'

#define RESET_PIN  8
#define   BC1_PIN A5
#define  BDIR_PIN A4

#define MASTER_CLK_FREQ 2000000

struct tone_t {
  uint8_t ft;
  uint8_t ct : 4;
};

tone_t note[60] = {{119, 7}, { 11, 7}, {166, 6}, { 71, 6}, {236, 5}, {151, 5}, { 71, 5}, {251, 4}, {179, 4}, {112, 4}, { 48, 4}, {244, 3},
                   {187, 3}, {133, 3}, { 83, 3}, { 35, 3}, {246, 2}, {203, 2}, {163, 2}, {125, 2}, { 89, 2}, { 56, 2}, { 24, 2}, {250, 1},
                   {221, 1}, {194, 1}, {169, 1}, {145, 1}, {123, 1}, {101, 1}, { 81, 1}, { 62, 1}, { 44, 1}, { 28, 1}, { 12, 1}, {253, 0},
                   {238, 0}, {225, 0}, {212, 0}, {200, 0}, {189, 0}, {178, 0}, {168, 0}, {159, 0}, {150, 0}, {142, 0}, {134, 0}, {126, 0},
                   {119, 0}, {112, 0}, {106, 0}, {100, 0}, { 94, 0}, { 89, 0}, { 84, 0}, { 79, 0}, { 75, 0}, { 71, 0}, { 67, 0}, { 63, 0}};

const tone_t NOTE_ZERO = {0, 0};

void set_mode_inactive() {
  digitalWrite(BC1_PIN, LOW);
  digitalWrite(BDIR_PIN, LOW);
}

void set_mode_latch() {
  digitalWrite(BC1_PIN, HIGH);
  digitalWrite(BDIR_PIN, HIGH);
}

void set_mode_write() {
  digitalWrite(BC1_PIN, LOW);
  digitalWrite(BDIR_PIN, HIGH);
}

void write_register(char reg, char value) {
  set_mode_latch();  
  PORTD = reg;  
  set_mode_inactive();  
  set_mode_write();  
  PORTD = value;  
  set_mode_inactive();
}

void setup() {
  // Set up Timer 1 to output a 2 MHZ clock signal in Pin 9
  TCCR1A = bit(COM1A0);
  TCCR1B = bit(WGM12) | bit(CS10);
  OCR1A = 3;
  pinMode(9, OUTPUT);

  pinMode(RESET_PIN, OUTPUT);
  pinMode(BC1_PIN, OUTPUT);
  pinMode(BDIR_PIN, OUTPUT);

  // Set pins 0 to 7 to output
  DDRD = 0xFF;
  // Set pins 0 to 7 to output LOW
  PORTD = 0x00;

  set_mode_inactive();

  // Reset the AY-3-8910
  digitalWrite(RESET_PIN, LOW);
  delay(1);
  digitalWrite(RESET_PIN, HIGH);

  // Enable only the Tone Generator on Channel A, B, C
  write_register( 7, 0b00111000);
  
  // Set the amplitude (volume) to each Channel
  write_register( 8, 0b00001000);
  write_register( 9, 0b00000110);
  write_register(10, 0b00000110);

  delay(1000);
}

void loop() {
  // play_techno_pop(135);
  // play_ieji(55);
  play_kankinouta(124);

  while(true);
}

void play_techno_pop(uint16_t BPM) {
  uint16_t jurokubu =  15000/BPM;       // 0.5*0.5*60*1000
  uint16_t hachibu =  30000/BPM;        // 0.5*60*1000
  uint16_t huten_hachibu =  45000/BPM;  // 1.5*0.5*60*1000
  uint16_t shibu =  60000/BPM;          // 60*1000
  uint16_t huten_shibu =  90000/BPM;    // 1.5*60*1000
  uint16_t nibu =  120000/BPM;          // 2*60*1000
  uint16_t huten_nibu =  180000/BPM;    // 2*1.5*60*1000
  uint16_t zen =  240000/BPM;           // 4*60*1000
  uint16_t soushoku = 500/BPM;          // 数字は適当

  write_reg_tone(A, note[raM]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[doM]);
  delay(hachibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(hachibu);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[doM]);
  delay(hachibu);
  write_reg_tone(A, note[doHH]);
  delay(hachibu);

  write_reg_tone(A, note[rasM]);
  write_reg_tone(C, note[reM]);
  delay(hachibu);
  write_reg_tone(A, note[reH]);
  delay(hachibu);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(hachibu);
  write_reg_tone(A, note[doHH]);
  delay(hachibu);

  /********************************/

  write_reg_tone(A, note[doH]);
  delay(hachibu);
  write_reg_tone(A, note[raH]);
  write_reg_tone(B, note[soM]);
  write_reg_tone(C, note[doM]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);
  write_reg_tone(A, note[soH]);
  delay(jurokubu);
  write_reg_tone(B, note[soM]);
  write_reg_tone(C, note[doM]);
  delay(jurokubu);
  write_reg_tone(A, note[faH]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);

  write_reg_tone(A, note[reH]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[raL]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);
  write_reg_tone(A, note[soH]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[raL]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);
  write_reg_tone(A, note[raH]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[raL]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[raL]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);

  /********************************/
  
  write_reg_tone(A, note[raM]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[doM]);
  delay(hachibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(hachibu);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[doM]);
  delay(hachibu);
  write_reg_tone(A, note[doHH]);
  delay(hachibu);

  write_reg_tone(A, note[rasM]);
  write_reg_tone(C, note[reM]);
  delay(hachibu);
  write_reg_tone(A, note[reH]);
  delay(hachibu);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(hachibu);
  write_reg_tone(A, note[doHH]);
  delay(hachibu);

  /********************************/

  write_reg_tone(A, note[doH]);
  delay(hachibu);
  write_reg_tone(A, note[raH]);
  write_reg_tone(B, note[soM]);
  write_reg_tone(C, note[doM]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);
  write_reg_tone(A, note[soH]);
  delay(jurokubu);
  write_reg_tone(B, note[soM]);
  write_reg_tone(C, note[doM]);
  delay(jurokubu);
  write_reg_tone(A, note[faH]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);

  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[raL]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[raL]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);
  write_reg_tone(A, note[faH]);
  delay(jurokubu);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[doM]);
  delay(jurokubu);
  write_reg_tone(A, note[doHH]);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(hachibu);

  /********************************/
  write_reg_tone(A, note[raM]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[doM]);
  delay(hachibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(hachibu);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[doM]);
  delay(hachibu);
  write_reg_tone(A, note[doHH]);
  delay(hachibu);

  write_reg_tone(A, note[rasM]);
  write_reg_tone(C, note[reM]);
  delay(hachibu);
  write_reg_tone(A, note[reH]);
  delay(hachibu);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(hachibu);
  write_reg_tone(A, note[doHH]);
  delay(hachibu);

  /********************************/

  write_reg_tone(A, note[doH]);
  delay(hachibu);
  write_reg_tone(A, note[raH]);
  write_reg_tone(B, note[soM]);
  write_reg_tone(C, note[doM]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);
  write_reg_tone(A, note[soH]);
  delay(jurokubu);
  write_reg_tone(B, note[soM]);
  write_reg_tone(C, note[doM]);
  delay(jurokubu);
  write_reg_tone(A, note[faH]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);

  write_reg_tone(A, note[reH]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[raL]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);
  write_reg_tone(A, note[soH]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[raL]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);
  write_reg_tone(A, note[raH]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[raL]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[raL]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);

  /********************************/
  
  write_reg_tone(A, note[raM]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[doM]);
  delay(hachibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(hachibu);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[doM]);
  delay(hachibu);
  write_reg_tone(A, note[doHH]);
  delay(hachibu);

  write_reg_tone(A, note[rasM]);
  write_reg_tone(C, note[reM]);
  delay(hachibu);
  write_reg_tone(A, note[reH]);
  delay(hachibu);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(hachibu);
  write_reg_tone(A, note[doHH]);
  delay(hachibu);

  /********************************/

  write_reg_tone(A, note[doH]);
  delay(hachibu);
  write_reg_tone(A, note[raH]);
  write_reg_tone(B, note[soM]);
  write_reg_tone(C, note[doM]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);
  write_reg_tone(A, note[soH]);
  delay(jurokubu);
  write_reg_tone(B, note[soM]);
  write_reg_tone(C, note[doM]);
  delay(jurokubu);
  write_reg_tone(A, note[faH]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);

  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[raL]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[raL]);
  delay(jurokubu);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(jurokubu);
  delay(jurokubu);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[doM]);
  delay(hachibu);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);

  for(size_t i = 0; i < 4; i++) {
    write_reg_tone(A, note[raH]);
    delay(jurokubu);
    write_reg_tone(A, note[rasH]);
    delay(jurokubu);

    /********************************/

    write_reg_tone(A, note[doHH]);
    write_reg_tone(B, note[faM]);
    write_reg_tone(C, note[doM]);
    delay(hachibu);
    write_reg_tone(A, note[raH]);
    write_reg_tone(B, NOTE_ZERO);
    write_reg_tone(C, NOTE_ZERO);
    delay(jurokubu);
    write_reg_tone(A, note[rasH]);
    delay(jurokubu);
    write_reg_tone(A, note[doHH]);
    write_reg_tone(B, note[faM]);
    write_reg_tone(C, note[doM]);
    delay(hachibu);
    write_reg_tone(A, note[raH]);
    delay(jurokubu);
    write_reg_tone(A, note[rasH]);
    delay(jurokubu);

    write_reg_tone(A, note[doHH]);
    write_reg_tone(C, note[reM]);
    delay(hachibu);
    write_reg_tone(A, note[faH]);
    delay(hachibu);
    write_reg_tone(A, note[faH]);
    write_reg_tone(B, NOTE_ZERO);
    write_reg_tone(C, NOTE_ZERO);
    delay(hachibu);
    write_reg_tone(A, note[faHH]);
    delay(hachibu);

    /********************************/

    write_reg_tone(A, note[miHH]);
    delay(hachibu);
    write_reg_tone(A, note[doHH]);
    write_reg_tone(B, note[soM]);
    write_reg_tone(C, note[doM]);
    delay(jurokubu);
    write_reg_tone(B, NOTE_ZERO);
    write_reg_tone(C, NOTE_ZERO);
    delay(jurokubu);
    write_reg_tone(A, note[raH]);
    delay(jurokubu);
    write_reg_tone(B, note[soM]);
    write_reg_tone(C, note[doM]);
    delay(jurokubu);
    write_reg_tone(A, note[soH]);
    delay(jurokubu);
    write_reg_tone(B, NOTE_ZERO);
    write_reg_tone(C, NOTE_ZERO);
    delay(jurokubu);

    write_reg_tone(A, note[raH]);
    write_reg_tone(B, note[faM]);
    write_reg_tone(C, note[raL]);
    delay(jurokubu);
    write_reg_tone(B, NOTE_ZERO);
    write_reg_tone(C, NOTE_ZERO);
    delay(jurokubu);
    write_reg_tone(A, note[faH]);
    write_reg_tone(B, note[faM]);
    write_reg_tone(C, note[raL]);
    delay(jurokubu);
    write_reg_tone(B, NOTE_ZERO);
    write_reg_tone(C, NOTE_ZERO);
    delay(jurokubu);
    write_reg_tone(A, note[faH]);
    write_reg_tone(B, note[faM]);
    write_reg_tone(C, note[raL]);
    delay(jurokubu);
    write_reg_tone(B, NOTE_ZERO);
    write_reg_tone(C, NOTE_ZERO);
    delay(jurokubu);
    write_reg_tone(A, note[raM]);
    write_reg_tone(B, note[faM]);
    write_reg_tone(C, note[raL]);
    delay(jurokubu);
    write_reg_tone(A, note[rasM]);
    write_reg_tone(B, NOTE_ZERO);
    write_reg_tone(C, NOTE_ZERO);
    delay(jurokubu);

    /********************************/

    write_reg_tone(A, note[doH]);
    write_reg_tone(B, note[faM]);
    write_reg_tone(C, note[doM]);
    delay(hachibu);
    write_reg_tone(A, note[raM]);
    write_reg_tone(B, NOTE_ZERO);
    write_reg_tone(C, NOTE_ZERO);
    delay(jurokubu);
    write_reg_tone(A, note[rasM]);
    delay(jurokubu);
    write_reg_tone(A, note[doH]);
    write_reg_tone(B, note[faM]);
    write_reg_tone(C, note[doM]);
    delay(hachibu);
    write_reg_tone(A, note[raM]);
    delay(jurokubu);
    write_reg_tone(A, note[rasM]);
    delay(jurokubu);

    write_reg_tone(A, note[doH]);
    write_reg_tone(C, note[reM]);
    delay(hachibu);
    write_reg_tone(A, note[faM]);
    delay(hachibu);
    write_reg_tone(A, note[faM]);
    write_reg_tone(B, NOTE_ZERO);
    write_reg_tone(C, NOTE_ZERO);
    delay(hachibu);
    write_reg_tone(A, note[faH]);
    delay(hachibu);

    /********************************/

    write_reg_tone(A, note[doH]);
    delay(hachibu);
    write_reg_tone(A, note[miH]);
    write_reg_tone(B, note[soM]);
    write_reg_tone(C, note[doM]);
    delay(jurokubu);
    write_reg_tone(B, NOTE_ZERO);
    write_reg_tone(C, NOTE_ZERO);
    delay(jurokubu);
    write_reg_tone(A, note[soH]);
    delay(jurokubu);
    write_reg_tone(B, note[soM]);
    write_reg_tone(C, note[doM]);
    delay(jurokubu);
    write_reg_tone(A, note[faH]);
    delay(jurokubu);

    write_reg_tone(B, note[faM]);
    write_reg_tone(C, note[raL]);
    delay(jurokubu);
    write_reg_tone(B, NOTE_ZERO);
    write_reg_tone(C, NOTE_ZERO);
    delay(jurokubu);
    write_reg_tone(B, note[faM]);
    write_reg_tone(C, note[raL]);
    delay(jurokubu);
    write_reg_tone(B, NOTE_ZERO);
    write_reg_tone(C, NOTE_ZERO);
    delay(jurokubu);
    write_reg_tone(A, NOTE_ZERO);
    delay(jurokubu);
    write_reg_tone(B, note[faM]);
    write_reg_tone(C, note[doM]);
    delay(jurokubu);
    write_reg_tone(B, NOTE_ZERO);
    write_reg_tone(C, NOTE_ZERO);
  }

  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(hachibu);
}

void play_ieji(uint16_t BPM) {
  uint16_t jurokubu =  15000/BPM;       // 0.5*0.5*60*1000
  uint16_t hachibu =  30000/BPM;        // 0.5*60*1000
  uint16_t huten_hachibu =  45000/BPM;  // 1.5*0.5*60*1000
  uint16_t shibu =  60000/BPM;          // 60*1000
  uint16_t huten_shibu =  90000/BPM;    // 1.5*60*1000
  uint16_t nibu =  120000/BPM;          // 2*60*1000
  uint16_t huten_nibu =  180000/BPM;    // 2*1.5*60*1000
  uint16_t zen =  240000/BPM;           // 4*60*1000
  uint16_t soushoku = 500/BPM;          // 数字は適当

  write_reg_tone(A, note[raM]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[faL]);
  delay(huten_hachibu);
  write_reg_tone(A, note[doH]);
  delay(jurokubu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(A, note[doH]);
  delay(shibu);

  write_reg_tone(A, note[raM]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[faL]);
  delay(huten_hachibu);
  write_reg_tone(A, note[soM]);
  delay(jurokubu);
  write_reg_tone(A, note[faM]);
  delay(shibu);

  /********************************/

  write_reg_tone(A, note[soM]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[doL]);
  delay(huten_hachibu);
  write_reg_tone(A, note[raM]);
  delay(jurokubu);
  write_reg_tone(A, note[doH]);
  delay(huten_hachibu);
  write_reg_tone(A, note[raM]);
  delay(jurokubu);

  write_reg_tone(A, note[soM]);
  write_reg_tone(B, note[miM]);
  write_reg_tone(C, note[doM]);
  delay(hachibu);
  write_reg_tone(C, note[rasL]);
  delay(hachibu);
  write_reg_tone(C, note[raL]);
  delay(hachibu);
  write_reg_tone(C, note[soL]);
  delay(hachibu);

  /********************************/

  write_reg_tone(A, note[raM]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[faL]);
  delay(huten_hachibu);
  write_reg_tone(A, note[doH]);
  delay(jurokubu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(A, note[doH]);
  delay(shibu);

  write_reg_tone(A, note[raM]);
  write_reg_tone(B, note[dosM]);
  write_reg_tone(C, note[raL]);
  delay(huten_hachibu);
  write_reg_tone(A, note[soM]);
  delay(jurokubu);
  write_reg_tone(A, note[faM]);
  delay(shibu);

  /********************************/

  write_reg_tone(A, note[soM]);
  write_reg_tone(B, note[reM]);
  write_reg_tone(C, note[rasL]);
  delay(hachibu);
  write_reg_tone(A, note[raM]);
  delay(hachibu);
  write_reg_tone(A, note[soM]);
  write_reg_tone(B, note[miM]);
  write_reg_tone(C, note[doM]);
  delay(huten_hachibu);
  write_reg_tone(A, note[faM]);
  write_reg_tone(B, NOTE_ZERO);
  delay(jurokubu);

  write_reg_tone(A, note[faM]);
  write_reg_tone(B, note[raL]);
  write_reg_tone(C, note[faL]);
  delay(nibu);

  /********************************/

  write_reg_tone(A, note[reH]);
  write_reg_tone(B, note[rasL]);
  write_reg_tone(C, note[faL]);
  delay(huten_hachibu);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[reM]);
  delay(jurokubu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[reM]);
  delay(shibu);

  write_reg_tone(A, note[miH]);
  write_reg_tone(B, note[doM]);
  delay(hachibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[raL]);
  delay(hachibu);
  write_reg_tone(A, note[reH]);
  write_reg_tone(B, note[rasL]);
  write_reg_tone(C, note[faL]);
  delay(shibu - soushoku);

  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(soushoku);

  /********************************/

  write_reg_tone(A, note[reH]);
  write_reg_tone(B, note[rasL]);
  write_reg_tone(C, note[faL]);
  delay(hachibu);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[reM]);
  delay(hachibu);
  write_reg_tone(A, note[miH]);
  write_reg_tone(B, note[doM]);
  delay(hachibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[raL]);
  delay(hachibu);

  write_reg_tone(A, note[reH]);
  write_reg_tone(B, note[rasL]);
  write_reg_tone(C, note[faL]);
  delay(nibu - soushoku);

  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(soushoku);

  /********************************/

  write_reg_tone(A, note[reH]);
  write_reg_tone(B, note[rasM]);
  write_reg_tone(C, note[rasLL]);
  delay(huten_hachibu);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[reH]);
  delay(jurokubu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[reH]);
  delay(shibu);

  write_reg_tone(A, note[miH]);
  write_reg_tone(B, note[doH]);
  write_reg_tone(C, note[raLL]);
  delay(hachibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[raM]);
  delay(hachibu);
  write_reg_tone(A, note[reH]);
  write_reg_tone(B, note[rasM]);
  write_reg_tone(C, note[rasLL]);
  delay(shibu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  delay(soushoku);
  
  /********************************/

  write_reg_tone(A, note[reH]);
  write_reg_tone(B, note[rasM]);
  write_reg_tone(C, note[rasLL]);
  delay(hachibu);
  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[reH]);
  delay(hachibu);
  write_reg_tone(A, note[miH]);
  write_reg_tone(B, note[doH]);
  delay(hachibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[raM]);
  delay(hachibu);

  write_reg_tone(A, note[reH]);
  write_reg_tone(B, note[rasM]);
  delay(hachibu);
  write_reg_tone(C, note[faM]);
  delay(jurokubu);
  write_reg_tone(C, note[resM]);
  delay(jurokubu);
  write_reg_tone(C, note[reM]);
  delay(hachibu);
  write_reg_tone(C, note[rasM]);
  delay(hachibu);

  /********************************/

  write_reg_tone(A, note[raM]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[faL]);
  delay(huten_hachibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[raM]);
  delay(jurokubu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[raM]);
  delay(shibu);

  write_reg_tone(A, note[raM]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[faL]);
  delay(huten_hachibu);
  write_reg_tone(A, note[soM]);
  write_reg_tone(B, note[doM]);
  delay(jurokubu);
  write_reg_tone(A, note[faM]);
  write_reg_tone(B, note[raL]);
  delay(shibu);
  
  /********************************/

  write_reg_tone(A, note[soM]);
  write_reg_tone(B, note[miM]);
  write_reg_tone(C, note[doL]);
  delay(huten_hachibu);
  write_reg_tone(A, note[raM]);
  write_reg_tone(B, note[faM]);
  delay(jurokubu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[soM]);
  delay(huten_hachibu);
  write_reg_tone(A, note[raM]);
  write_reg_tone(B, note[faM]);
  delay(jurokubu);

  write_reg_tone(A, note[soM]);
  write_reg_tone(B, note[miM]);
  write_reg_tone(C, note[doM]);
  delay(shibu);
  write_reg_tone(A, note[sosM]);
  delay(shibu);

  /********************************/
  
  write_reg_tone(A, note[raM]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[faL]);
  delay(huten_hachibu);
  write_reg_tone(A, note[doH]);
  delay(jurokubu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(A, note[doH]);
  write_reg_tone(C, note[miL]); 
  delay(shibu);

  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[raM]);
  write_reg_tone(C, note[reL]);
  delay(huten_hachibu);
  write_reg_tone(A, note[soH]);
  write_reg_tone(B, note[doH]);
  delay(jurokubu - soushoku);
  write_reg_tone(B, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(A, note[raH]);
  write_reg_tone(B, note[doH]);
  write_reg_tone(C, note[doL]);
  delay(shibu);

  /********************************/

  write_reg_tone(A, note[soH]);
  write_reg_tone(B, note[reH]);
  write_reg_tone(C, note[rasLL]);
  delay(huten_hachibu);
  write_reg_tone(A, note[faH]);
  delay(jurokubu);
  write_reg_tone(A, note[soH]);
  delay(hachibu);
  write_reg_tone(A, note[reH]);
  write_reg_tone(B, note[rasM]);
  write_reg_tone(C, note[rasL]);
  delay(hachibu);

  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[raM]);
  write_reg_tone(C, note[faL]);
  delay(hachibu);
  write_reg_tone(B, note[faM]);
  delay(hachibu);
  write_reg_tone(B, note[raM]);
  delay(hachibu);
  write_reg_tone(B, note[doH]);
  delay(hachibu);

  /********************************/

  write_reg_tone(A, note[soH]);
  write_reg_tone(B, note[reH]);
  write_reg_tone(C, note[rasLL]);
  delay(huten_hachibu);
  write_reg_tone(A, note[faH]);
  delay(jurokubu);
  write_reg_tone(A, note[soH]);
  delay(hachibu);
  write_reg_tone(A, note[reH]);
  write_reg_tone(B, note[rasM]);
  write_reg_tone(C, note[rasL]);
  delay(hachibu);

  write_reg_tone(A, note[faH]);
  write_reg_tone(B, note[raM]);
  write_reg_tone(C, note[faL]);
  delay(nibu);

  /********************************/
  
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
}

void play_kankinouta(uint16_t BPM) {
  uint16_t jurokubu =  15000/BPM;       // 0.5*0.5*60*1000
  uint16_t hachibu =  30000/BPM;        // 0.5*60*1000
  uint16_t huten_hachibu =  45000/BPM;  // 1.5*0.5*60*1000
  uint16_t shibu =  60000/BPM;          // 60*1000
  uint16_t huten_shibu =  90000/BPM;    // 1.5*60*1000
  uint16_t nibu =  120000/BPM;          // 2*60*1000
  uint16_t huten_nibu =  180000/BPM;    // 2*1.5*60*1000
  uint16_t zen =  240000/BPM;           // 4*60*1000
  uint16_t soushoku = 500/BPM;          // 数字は適当
  
  /********************************
  write_reg_tone(CH, note[NOTE]);
   ********************************/

  write_reg_tone(A, note[doH]);
  write_reg_tone(C, note[sosLL]);
  delay(shibu);
  write_reg_tone(B, note[sosL]);
  delay(shibu);
  write_reg_tone(A, note[dosH]);
  write_reg_tone(B, note[rasL]);
  write_reg_tone(C, note[sosL]);
  delay(shibu);
  write_reg_tone(A, note[resH]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[sosLL]);
  delay(shibu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  delay(soushoku);

  /********************************/

  write_reg_tone(A, note[resH]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[resL]);
  delay(shibu);
  write_reg_tone(A, note[dosH]);
  write_reg_tone(B, note[rasL]);
  delay(hachibu);
  write_reg_tone(C, note[resLL]);
  delay(hachibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[sosL]);
  write_reg_tone(C, note[resLL]);
  delay(shibu);
  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[resM]);
  write_reg_tone(C, note[soLL]);
  delay(hachibu - soushoku);
  write_reg_tone(C, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(C, note[resLL]);
  delay(hachibu);

  /********************************/
  
  write_reg_tone(A, note[sosM]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[sosLL]);
  delay(shibu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(A, note[sosM]);
  write_reg_tone(B, note[doM]);
  delay(hachibu - soushoku);
  write_reg_tone(C, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(C, note[sosLL]);
  delay(hachibu);
  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[soL]);
  write_reg_tone(C, note[resL]);
  delay(shibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[sosL]);
  write_reg_tone(C, note[sosLL]);
  delay(shibu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  delay(soushoku);

  /********************************/

  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[sosL]);
  write_reg_tone(C, note[resL]);
  delay(shibu);
  write_reg_tone(C, note[resLL]);
  delay(hachibu);
  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[soL]);
  delay(hachibu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[soL]);
  write_reg_tone(C, note[resLL]);
  delay(nibu);
  write_reg_tone(B, NOTE_ZERO);

  /********************************/

  write_reg_tone(A, note[doH]);
  write_reg_tone(C, note[sosLL]);
  delay(shibu);
  write_reg_tone(B, note[sosL]);
  delay(shibu);
  write_reg_tone(A, note[dosH]);
  write_reg_tone(B, note[rasL]);
  write_reg_tone(C, note[sosL]);
  delay(shibu);
  write_reg_tone(A, note[resH]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[sosLL]);
  delay(shibu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  delay(soushoku);

  /********************************/

  write_reg_tone(A, note[resH]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[resL]);
  delay(shibu);
  write_reg_tone(A, note[dosH]);
  write_reg_tone(B, note[rasL]);
  delay(hachibu);
  write_reg_tone(C, note[resLL]);
  delay(hachibu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[sosL]);
  write_reg_tone(C, note[resLL]);
  delay(shibu);
  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[resM]);
  write_reg_tone(C, note[soLL]);
  delay(hachibu);
  write_reg_tone(C, note[resLL]);
  delay(hachibu);

  /********************************/

  write_reg_tone(A, note[sosM]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[sosLL]);
  delay(shibu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(A, note[sosM]);
  write_reg_tone(B, note[doM]);
  delay(hachibu - soushoku);
  write_reg_tone(C, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(C, note[sosLL]);
  delay(hachibu);
  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[soL]);
  write_reg_tone(C, note[resL]);
  delay(shibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[sosL]);
  write_reg_tone(C, note[sosLL]);
  delay(shibu);

  /********************************/

  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[dosM]);
  write_reg_tone(C, note[resL]);
  delay(shibu);
  write_reg_tone(C, note[reLL]);
  delay(hachibu);
  write_reg_tone(A, note[sosM]);
  write_reg_tone(B, note[doM]);
  delay(hachibu);
  write_reg_tone(A, note[sosM]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[sosLL]);
  delay(nibu);

  /********************************/

  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[soM]);
  write_reg_tone(C, note[resLL]);
  delay(shibu);
  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[soM]);
  delay(hachibu - soushoku);
  write_reg_tone(C, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(C, note[resLL]);
  delay(hachibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[sosM]);
  write_reg_tone(C, note[resL]);
  delay(shibu);
  write_reg_tone(A, note[sosM]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[sosLL]);
  delay(shibu);

  /********************************/

  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[soM]);
  write_reg_tone(C, note[resLL]);
  delay(shibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[sosM]);
  delay(hachibu - soushoku);
  write_reg_tone(C, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(A, note[dosH]);
  write_reg_tone(B, note[rasM]);
  write_reg_tone(C, note[resLL]);
  delay(hachibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[sosM]);
  write_reg_tone(C, note[resL]);
  delay(shibu);
  write_reg_tone(A, note[sosM]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[sosLL]);
  delay(shibu);

  /********************************/

  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[soM]);
  write_reg_tone(C, note[resLL]);
  delay(shibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[sosM]);
  write_reg_tone(C, note[resL]);
  delay(hachibu);
  write_reg_tone(A, note[dosH]);
  write_reg_tone(B, note[rasM]);
  delay(hachibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[soM]);
  write_reg_tone(C, note[miL]);
  delay(shibu);
  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[soM]);
  write_reg_tone(C, note[doL]);
  delay(shibu);

  /********************************/

  write_reg_tone(A, note[sosM]);
  write_reg_tone(B, note[faM]);
  write_reg_tone(C, note[faL]);
  delay(shibu);
  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[reM]);
  write_reg_tone(C, note[rasLL]);
  delay(shibu);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, note[resM]);
  write_reg_tone(C, note[resL]);
  delay(shibu);

  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[sosM]);
  write_reg_tone(C, NOTE_ZERO);
  delay(shibu);

  /********************************/

  delay(shibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[sosL]);
  delay(shibu);
  write_reg_tone(A, note[dosH]);
  write_reg_tone(B, note[rasL]);
  write_reg_tone(C, note[sosL]);
  delay(shibu);
  write_reg_tone(A, note[resH]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[sosLL]);
  delay(shibu);

  /********************************/

  write_reg_tone(A, note[resH]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[resL]);
  delay(shibu);
  write_reg_tone(A, note[dosH]);
  write_reg_tone(B, note[rasL]);
  delay(hachibu);
  write_reg_tone(C, note[resLL]);
  delay(hachibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[sosL]);
  write_reg_tone(C, note[resLL]);
  delay(shibu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(A, note[dosH]);
  write_reg_tone(B, note[soL]);
  write_reg_tone(C, note[resLL]);
  delay(hachibu);
  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[dosH]);
  delay(hachibu);

  /********************************/

  write_reg_tone(A, note[sosM]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[sosLL]);
  delay(shibu);
  write_reg_tone(A, note[sosM]);
  write_reg_tone(B, note[doM]);
  delay(hachibu - soushoku);
  write_reg_tone(C, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(C, note[sosLL]);
  delay(hachibu);
  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[soL]);
  write_reg_tone(C, note[resLL]);
  delay(shibu);
  write_reg_tone(A, note[doH]);
  write_reg_tone(B, note[sosL]);
  write_reg_tone(C, note[sosLL]);
  delay(shibu);

  /********************************/

  write_reg_tone(A, note[rasM]);
  write_reg_tone(B, note[dosM]);
  write_reg_tone(C, note[resL]);
  delay(shibu);
  write_reg_tone(C, note[resLL]);
  delay(hachibu);
  write_reg_tone(A, note[sosM]);
  write_reg_tone(B, note[doM]);
  delay(hachibu - soushoku);
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  delay(soushoku);
  write_reg_tone(A, note[sosM]);
  write_reg_tone(B, note[doM]);
  write_reg_tone(C, note[sosLL]);
  delay(nibu);

  /********************************/

  delay(shibu);

  /********************************/
  
  write_reg_tone(A, NOTE_ZERO);
  write_reg_tone(B, NOTE_ZERO);
  write_reg_tone(C, NOTE_ZERO);
}

void play_temp(uint16_t BPM) {
  uint16_t jurokubu =  15000/BPM;       // 0.5*0.5*60*1000
  uint16_t hachibu =  30000/BPM;        // 0.5*60*1000
  uint16_t huten_hachibu =  45000/BPM;  // 1.5*0.5*60*1000
  uint16_t shibu =  60000/BPM;          // 60*1000
  uint16_t huten_shibu =  90000/BPM;    // 1.5*60*1000
  uint16_t nibu =  120000/BPM;          // 2*60*1000
  uint16_t huten_nibu =  180000/BPM;    // 2*1.5*60*1000
  uint16_t zen =  240000/BPM;           // 4*60*1000
  uint16_t soushoku = 500/BPM;          // 数字は適当
  
  /********************************
  write_reg_tone(CH, note[NOTE]);
   ********************************/
}

void write_reg_tone(char ch, tone_t tone_period) {
  switch(ch) {
    case A:
      write_register(CH_A_R0, tone_period.ft);
      write_register(CH_A_R1, tone_period.ct);
      break;

    case B:
      write_register(CH_B_R0, tone_period.ft);
      write_register(CH_B_R1, tone_period.ct);
      break;

    case C:
      write_register(CH_C_R0, tone_period.ft);
      write_register(CH_C_R1, tone_period.ct);
      break;
  }
}
