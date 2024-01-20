void setup() {
  Serial.begin(115200);
  Serial.printf("XTAL Frequency: %i MHz", getXtalFrequencyMhz());
  Serial.printf("APB Frequency: %i MHz", getApbFrequency());
}
 
void loop() {
  Serial.printf("CPU Frequency: %i MHz", getCpuFrequencyMhz());

  setCpuFrequencyMhz(160);
  delay(2000);
  Serial.printf("CPU Frequency: %i MHz", getCpuFrequencyMhz());

  setCpuFrequencyMhz(80);
  delay(2000);
}
