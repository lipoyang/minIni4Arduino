#include <SD.h>
#include <minIni.h>

static void assert(bool cond)
{
  if(!cond){
    Serial.println("Error");
    while(true){;}
  }else{
    Serial.println("OK");
  }
}

static void assert(String s1, String s2)
{
  Serial.print("<");
  Serial.print(s1.c_str());
  Serial.print("> <");
  Serial.print(s2.c_str());
  Serial.print(">  ");
  
  assert(s1 == s2);
}

static void assert(int d1, int d2)
{
  Serial.print("(");
  Serial.print(d1);
  Serial.print(") (");
  Serial.print(d2);
  Serial.print(")  ");
  
  assert(d1 == d2);
}

void setup()
{
  Serial.begin(9600);
  while(!Serial.available()); // wait to press key
  Serial.read(); //dummy
   
  if(!SD.begin()){
    Serial.println("Card failed, or not present.");
    while(1);
  }
}

void loop()
{
  minIni ini("test.ini");
  minIni ini2("plain.ini");
  String s;

  /* string reading */
  s = ini.gets( "first", "string" , "aap" );
  assert(s, "noot");
  s = ini.gets( "second", "string" , "aap" );
  assert(s, "mies");
  s = ini.gets( "first", "dummy" , "aap" );
  assert(s, "aap");
  /* ----- */
  s = ini2.gets( "", "string" , "aap" );
  assert(s, "noot");
  /* ----- */
  Serial.println("1. String reading tests passed");

  /* value reading */
  long n;
  n = ini.getl("first", "val", -1 );
  assert(n, 1);
  n = ini.getl("second", "val", -1);
  assert(n, 2);
  n = ini.getl("first", "dummy", -1);
  assert(n, -1);
  /* ----- */
  n = ini2.getl("", "val", -1);
  assert(n, 1);
  /* ----- */
  Serial.println("2. Value reading tests passed");


  /* string writing */
  bool b;
  b = ini.put("first", "alt", "flagged as \"correct\"");
  assert(b);
  s = ini.gets("first", "alt", "aap");
  assert(s, "flagged as \"correct\"");

  b = ini.put("second", "alt", "correct");
  assert(b);
  s = ini.gets("second", "alt", "aap");
  assert(s, "correct");

  b = ini.put("third", "alt", "correct");
  assert(b);
  s = ini.gets("third", "alt", "aap" );
  assert(s, "correct");
  /* ----- */
  b = ini2.put("", "alt", "correct");
  assert(b);
  s = ini2.gets("", "alt", "aap" );
  assert(s, "correct");
  /* ----- */
  Serial.println("3. String writing tests passed");

  /* section/key enumeration */
  Serial.println("4. section/key enumeration; file contents follows");
  String section;
  for (int is = 0; section = ini.getsection(is), section.length() > 0; is++) {
    Serial.print("    [");
    Serial.print(section.c_str());
    Serial.println("]");
    for (int ik = 0; s = ini.getkey(section, ik), s.length() > 0; ik++) {
      Serial.print("\t");
      Serial.println(s.c_str());
    }
  }

  /* string deletion */
  b = ini.del("first", "alt");
  assert(b);
  b = ini.del("second", "alt");
  assert(b);
  b = ini.del("third");
  assert(b);
  /* ----- */
  b = ini2.del("", "alt");
  assert(b);
  /* ----- */
  Serial.println("5. string deletion passed ");
  
  while(true){;}
}
