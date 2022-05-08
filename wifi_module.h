//JAKUB WOJCIECHOWSKI
//THIS IS MODULE FOF SENDIGT DATA THROUGH THE WI-FI TO THE DATA BASE
//USEING ESP826 WI-FI BUILT IN MODEULE END SSD1306 OLED SCREEN FOR USER INTERACTION
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <ESP8266WiFi.h>


WiFiClient client;

char ssid[] =  "OnePlus 6";                 // Network Name
char pass[] =  "12345678";                 // Network Password
byte mac[6];

IPAddress server_addr(52,29,239,198);          // MySQL server IP
char user[] = "sql7314271";           // MySQL user
char password[] = "iGQhnDbfKa";       // MySQL password

MySQL_Connection conn((Client *)&client);

char INSERT_SQL[] = "USE sql7314271; INSERT INTO D1_data(Steps_Day, BPM) VALUES (%d,%f)";
char query[128];


//--------------------------FUNCTION DRWAING THE PROGRESS BAR-------------------------- 
void ProgressBar(int progress, String state, String message){
  // draw the progress bar
  display.drawProgressBar(0, 37, 120, 10, progress);

  // draw the process name
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 13, state );
  display.drawString(64, 25, message );
}


//--------------------------THE WI-FI CONNECTION FUNCTION--------------------------  
int wi_fi_connect(){
  int counter = 0;    //counter to cancel trying to connect after some time
  
  Serial.println("Initialising connection");
  Serial.println("");
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) { 
    delay(200);
    Serial.print(".");
    counter++;
    
    if(counter == 40){
      Serial.println("Failed to connect to wi-fi");
      return 1;   //returning 1 as bad connection flag
    }
    }

  Serial.println("");
  Serial.println("WiFi Connected");

  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
  Serial.println("");
  Serial.print("Assigned IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");

  return 0;
}



//--------------------------SYNCHRONIZATION THE DATA WITH DATABASE-------------------------- 
int sync_data(int steps, float BPM) {  
    int counter = 0;    //counter to cancel trying to connect after some time
  
  //--------------------------DISPLAYING THE PROGRESS BAR WITH CURENT STATE-------------------------- 
  int progress = 0; //progress %
  display.clear();
  ProgressBar(progress, "Connecting to Wi-Fi", "");
  display.display();
  
  
  //--------------------------INITALIZING THE WI-FI CONNECTION--------------------------  

  if(wi_fi_connect() == 1){
    progress = 100;
    display.clear();
    ProgressBar(progress, "Connecting to Wi-Fi", "Failed");
    display.display();
    delay(2000);
    return 1;   //returning 1 as bad connection flag
    }
  
  //--------------------------DISPLAYING THE PROGRESS BAR WITH CURENT STATE-------------------------- 
  progress = 33;
  display.clear();
  ProgressBar(progress, "Connecting to DataBase", "");
  display.display();


  //--------------------------INITALIZING THE DATABASE CONNECTION--------------------------  
  Serial.println("Connecting to database");

  while (conn.connect(server_addr, 3306, user, password) != true) {
    delay(200);
    Serial.print(".");
    counter++;
    
    if(counter == 20){
      progress = 100;
      display.clear();
      ProgressBar(progress, "Connecting to DataBase", "Failed");
      display.display();
      delay(2000);
      Serial.println("Failed to connect to database");
      return 1; //returning 1 as bad connection flag
    }
    }
  
  Serial.println("");
  Serial.println("Connected to SQL Server!"); 
  

  //--------------------------DISPLAYING THE PROGRESS BAR WITH CURENT STATE-------------------------- 
  progress = 66;
  display.clear();
  ProgressBar(progress, "Sending Data", "");
  display.display();


  //--------------------------SENDIN DATA TO SERVER--------------------------
  delay(10000); //10 sec
  sprintf(query, INSERT_SQL, steps, BPM);
  Serial.println("Recording data.");
  Serial.println(query);
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn); 
  cur_mem->execute(query);
  delete cur_mem;


    //--------------------------DISPLAYING THE PROGRESS BAR WITH CURENT STATE-------------------------- 
  progress = 100;
  display.clear();
  ProgressBar(progress, "Complietd", "");
  display.display();
  delay(2000);


  return 0;     //returning 0 as succes on arduino side
}
