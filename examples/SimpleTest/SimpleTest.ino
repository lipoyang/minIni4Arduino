#include <string>
#include <SD.h>
#include <minIni.h>

void setup()
{
  Serial.begin(9600);
  delay(500);
  Serial.println("Press any key.");
  while(!Serial.available()); // wait to press key
  Serial.read(); //dummy
   
  if(!SD.begin()){
    Serial.println("Card failed, or not present.");
    while(1);
  }
  Serial.println("INI file test start");
}

void loop()
{
  minIni ini("setting.ini");
  
  // read INI file
  std::string ip = ini.gets( "network", "ip address" , "none" );
  Serial.print("IP Address: ");
  Serial.println(ip.c_str());
  
  std::string name = ini.gets( "user", "name" , "none" );
  Serial.print("Name: ");
  Serial.println(name.c_str());
  
  int id = ini.geti( "user", "id" , -1 );
  Serial.print("ID: ");
  Serial.println(id);
  
  bool righthanded = ini.getbool( "user", "righthanded" , false );
  Serial.print("Handedness: ");
  Serial.println(righthanded ? "Right" : "Left");
  
  float k1 = ini.getf( "calibration", "k1" , 0.0 );
  Serial.print("k1: ");
  Serial.println(k1);
  
  float k2 = ini.getf( "calibration", "k2" , 0.0 );
  Serial.print("k2: ");
  Serial.println(k2);
  
  // write INI file
  Serial.println("New ID...");
  
  if(id == 1234){
    name = "Kida Taro";
    id = 4321;
  }else{
    name = "Isaac Asimov";
    id = 1234;
  }
  ini.put( "user", "name" , name );
  ini.put( "user", "ID" , id );
  
  name = ini.gets( "user", "name" , "none" );
  Serial.print("Name: ");
  Serial.println(name.c_str());
  
  id = ini.geti( "user", "id" , -1 );
  Serial.print("ID: ");
  Serial.println(id);
  
  Serial.println("INI file test end");
  
  while(true){;}
}
