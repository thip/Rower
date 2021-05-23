unsigned long pulses[512];
int pulse_count;

void IRAM_ATTR isr() {
  if (millis()-pulses[pulse_count] < 25){
      return;
  }
  pulse_count++;
  pulses[pulse_count] = millis();
}

void setup() {
    Serial.begin(115200);
    pinMode(21, INPUT_PULLUP);
    attachInterrupt(21, isr, RISING);
}

void loop() {
    if(pulse_count > 128){
        detachInterrupt(21);

        for (int i = 4; i < 128; i+=4){
            unsigned long val = (pulses[i-4]+pulses[i-3]+pulses[i-2]+pulses[i-1])/4;
            Serial.println(val);
        }

        pulse_count = 0;
    }
}
