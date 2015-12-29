#include <SPI.h>
#include <WiFiUdp.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <SLFS.h>
#include <WiFiServer.h>


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.println("CC3200/CC3100 SLFS Serial Flash demo.");
  
  SerFlash.begin();
  
  Serial.println("Writing some text to /storage/mine.txt-");
  // Create a file "/storage/mine.txt"  
  SerFlash.open("/storage/mine.txt",
    FS_MODE_OPEN_CREATE(512, _FS_FILE_OPEN_FLAG_COMMIT));
  SerFlash.println("Hi there, this is my file!");
  SerFlash.close();
}

void loop()
{
  // Open "/storage/mine.txt" and read its contents, print to serial monitor-
  SerFlash.open("/storage/mine.txt", FS_MODE_OPEN_READ);
  char buf[1024];
  
  size_t read_length = SerFlash.readBytes(buf, 1023);
  Serial.print("Read ");
  Serial.print(read_length);
  Serial.println(" bytes from /storage/mine.txt - contents:");
  Serial.println(buf);
  SerFlash.close();
  
  delay(10000);  // Pause 10 seconds
  // ... then do it all again :-)
}
