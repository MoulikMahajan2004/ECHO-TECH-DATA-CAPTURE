#include <DHT.h>
#include <DHT_U.h>

//SD card
#include <SD.h>
#include <SPI.h>
//#include "DHT.h"


#define DHTPIN 2 
#define DHTTYPE DHT22

File myFile;

const int chipSelect = 10;

DHT dht(DHTPIN , DHTTYPE);

void setup() {
  pinMode(10, OUTPUT); // change this to 53 if you are using arduino mega
//digitalWrite(10, HIGH); // Add this line


   
  Serial.begin(9600);
 
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
 
  // Create/Open file
  myFile = SD.open("myfile1.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Writing to file...");
    // Write to file
    myFile.println("Testing text 1, 2 ,3...");
    myFile.close(); // close the file
    Serial.println("Done.");
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening myfile1.txt");
  }

  // Reading the file
  myFile = SD.open("myfile1.txt");
  if (myFile) {
    Serial.println("Read:");
    // Reading the whole file
    while (myFile.available()) {
      Serial.write(myFile.read());
   }
    myFile.close();
  }
  else {
    Serial.println("error opening myfile1.txt");
  }
  Serial.println(F("DHTxx test!"));

  dht.begin();
 
}
void loop() {
  delay(1000);
   float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F(" Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));



  myFile.println(F("Humidity: "));
  myFile.println(h);
  myFile.println(F("Temperature: "));
  myFile.println(t);
  myFile.println(F("°C "));
  myFile.println(f);
  myFile.println(F("°F  Heat index: "));
  myFile.println(hic);
  myFile.println(F("°C "));
  myFile.println(hif);
  myFile.println(F("°F"));

 
  // if (myFile) {
  //   //Serial.println("Read:");
  //   // Reading the whole file
  //   Serial.println("Writing to file...");
  //   // Write to file
  //   myFile.println("Testing text 1, 2 ,3...");

   
  //   //Serial.println("Done.");
  //   while (myFile.available()) {
  //     Serial.write(myFile.read());
  //  }
  //   myFile.close();
  // }
  //  if (myFile) {
  //   Serial.println("Writing to file...");
  //   // Write to file
  //   myFile.println("Testing text 1, 2 ,3...");
  //   myFile.close(); // close the file
  //   Serial.println("Done.");
  // }
  //  myFile.close(); // close the file
}
