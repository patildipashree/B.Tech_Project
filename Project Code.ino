#include <OneWire.h>
#include <DallasTemperature.h>

const int pH_Sensor_Pin = A0;
const int Turbidity_Sensor_Pin = A1;
const int TDS_Sensor_Pin = A2;
const int Temp_Sensor_Pin = 2;

OneWire oneWire(Temp_Sensor_Pin);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  // Read and calculate pH value
  int pH_analog = analogRead(pH_Sensor_Pin);
  float pH_voltage = pH_analog * (5.0 / 1023.0);
  float pH_value = 3.5 * pH_voltage + Offset;

  // Read and calculate turbidity value
  int turbidity_analog = analogRead(Turbidity_Sensor_Pin);
  float turbidity_voltage = turbidity_analog * (5.0 / 1023.0);
  float turbidity_value = map(turbidity_analog, 0, 1023, 0, 3000);

  // Read and calculate TDS value
  int TDS_analog = analogRead(TDS_Sensor_Pin);
  float tds_voltage = TDS_analog * (5.0 / 1023.0);
  float tds_value = (133.42 * tds_voltage * tds_voltage * tds_voltage
                     - 255.86 * tds_voltage * tds_voltage
                     + 857.39 * tds_voltage) * 0.5;

  // Read temperature value
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  // Print values with attractive formatting
  Serial.println();
  Serial.println("***************************************");
  Serial.println("*            SENSOR READINGS          *");
  Serial.println("***************************************");
  Serial.println();

  Serial.println("pH Sensor:");
  Serial.print("  Analog Reading: ");
  Serial.println(pH_analog);
  Serial.print("  Voltage: ");
  Serial.print(pH_voltage);
  Serial.println(" V");
  Serial.print("  pH Value: ");
  Serial.println(pH_value);
  Serial.println();

  Serial.println("Turbidity Sensor:");
  Serial.print("  Analog Reading: ");
  Serial.println(turbidity_analog);
  Serial.print("  Voltage: ");
  Serial.print(turbidity_voltage);
  Serial.println(" V");
  Serial.print("  Turbidity Value: ");
  Serial.print(turbidity_value);
  Serial.println(" NTU");
  Serial.println();

  Serial.println("TDS Sensor:");
  Serial.print("  Analog Reading: ");
  Serial.println(TDS_analog);
  Serial.print("  Voltage: ");
  Serial.print(tds_voltage);
  Serial.println(" V");
  Serial.print("  TDS Value: ");
  Serial.print(tds_value);
  Serial.println(" ppm");
  Serial.println();

  Serial.println("Temperature Sensor:");
  Serial.print("  Temperature: ");
  Serial.print(tempC);
  Serial.println(" °C");
  Serial.println();

  Serial.println("***************************************");
  Serial.println();

  delay(2000);
}
