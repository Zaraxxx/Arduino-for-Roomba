#include <SoftwareSerial.h>
#include <Roomba.h>


#define UseArduinoUno
//#define UseArduinoMega
 

#ifdef UseArduinoUno
  SoftwareSerial btSerial(10,11); // RX, TX
  //SoftwareSerial RoombaSerial(8, 9); // RX, TX
  //Roomba roomba(RoombaSerial, roomba.Baud19200);
  Roomba roomba(&Serial, roomba.Baud19200);
#endif
#ifdef UseArduinoMega
  SoftwareSerial btSerial(10, 11); // RX, TX
  Roomba roomba(&Serial1, roomba.Baud19200);
#endif


String btCommand = "";
String serialCommand = "";

int16_t Vitesse = 100;
int16_t Radius = 0;


bool brushON = false;
bool brushSideON = false;
bool vaccumON = false;



void playtune(){
// 2 bytes per note
  uint8_t song[] = {62, 12, 66, 12, 69, 12, 74, 36};
  roomba.song(0, song, sizeof(song));
  roomba.playSong(0);
}

void Debugln(String value){
#ifdef UseArduinoMega
  Serial.println(value);  
#endif
}

int getCommandState(String mycommand){
  int result = 0; 
  return result;
}

void readinputCommand8(String command){
      String substringX = command.substring(1,4);
      String substringY = command.substring(4,8);

      int intX = substringX.toInt(); 
      int intY = substringY.toInt(); 
      
      if ((intX >=100) && (intX <=300)){
        Vitesse = map(intY,100,300,-500,500);
        int dir = map(intX,100,300,-500,500);
        int VitesseG = Vitesse + dir;
        int VitesseD = Vitesse - dir;

        roomba.driveDirect(VitesseG, VitesseD);
      }      
}

void readCommand(String command){

     if ((command == "V1") || (command.indexOf("V--1") > -1)){
        Vitesse = 100;
        Debugln("V1");
        //driveRoomba();
     } else if ((command == "V2") || (command.indexOf("V--2") > -1)){
        Vitesse = 200;
        Debugln("V2");
        //driveRoomba();
     } else if ((command == "V3") || (command.indexOf("V--3") > -1)){
        Vitesse = 300;
        Debugln("V3");
        //driveRoomba();
     } else if ((command == "V4") || (command.indexOf("V--4") > -1)){
        Vitesse = 400;
        Debugln("V4");
        //driveRoomba();
     } else if ((command == "V5") || (command.indexOf("V--5") > -1)){
        Vitesse = 500;
        Debugln("V5");
        //driveRoomba();


//--------------------------------------------- DEPLACEMENT ROBOT ----------------------------------------------------------------------

     // STOP DEPLACEMENT
     } else if ((command == "stop") || (command.indexOf("stop") > -1)){        
       Debugln("Stop Deplacement");
       roomba.driveDirect(0, 0);
        
      // AVANT GAUCHE
     } else if ((command == "AVgauche") || (command.indexOf("A--V--g--a--u--c--h--e") > -1)){
         Debugln("Avant gauche");
         roomba.driveDirect(Vitesse-200, Vitesse);         
    
    // AVANT DROITE
     } else if ((command == "AVdroite") || (command.indexOf("A--V--d--r--o--i--t--e") > -1)){
         Debugln("Avant droite");
         roomba.driveDirect(Vitesse, Vitesse-200);         
    
      // ARRIERE GAUCHE
     } else if ((command == "ARgauche") || (command.indexOf("A--R--g--a--u--c--h--e") > -1)){
         Debugln("Arriere gauche");
         roomba.driveDirect( -Vitesse+200, -Vitesse);         
    
    // ARRIERE DROITE
     } else if ((command == "ARdroite") || (command.indexOf("A--R--d--r--o--i--t--e") > -1)){
         Debugln("Arriere droite");
         roomba.driveDirect( -Vitesse, -Vitesse +200);         


     } else if ((command == "stop") || (command.indexOf("s--t--o--p") > -1)){
         Debugln("Stop");
         roomba.driveDirect(0, 0);         
     } else if ((command == "spot") || (command.indexOf("s--p--o--t") > -1)){
         Debugln("spot");
         roomba.spot();
     } else if ((command == "coverAndDock") || (command.indexOf("c--o--v--e--r--A--n--d--D--o--c--k") > -1)){
         Debugln("coverAndDock");
         roomba.coverAndDock();
     } else if ((command == "cover") || (command.indexOf("c--o--v--e--r") > -1)){
         Debugln("cover");
         roomba.cover();
//     } else if (command == "demo"){
//         Serial.println("demo");
//         roomba.demo();
     } else if ((command == "dock") || (command.indexOf("d--o--c--k") > -1)){
         Debugln("dock");
         roomba.dock();
     } else if ((command == "power") || (command.indexOf("p--o--w--e--r") > -1)){
         Debugln("power");
         roomba.power();
     } else if ((command == "fullMode") || (command.indexOf("f--u--l--l--M--o--d--e") > -1)){
         Debugln("fullMode");
         roomba.fullMode();
     } else if ((command == "safeMode") || (command.indexOf("s--a--f--e--M--o--d--e") > -1)){
         Debugln("safeMode");
         roomba.safeMode();
     } else if ((command == "start") || (command.indexOf("s--t--a--r--t") > -1)){
         Debugln("start");
         roomba.start();
     } else if ((command == "reset") || (command.indexOf("r--e--s--e--t") > -1)){
         Debugln("reset");
         roomba.reset();    
         
     } else if ((command == "motor0") || (command.indexOf("m--o--t--o--r--0") > -1)){
         Debugln("motor0");
         uint8_t mot = 0;
         roomba.drivers(mot);    
     } else if ((command == "motor1") || (command.indexOf("m--o--t--o--r--1") > -1)){
         Debugln("motor1");
         uint8_t mot = 1;
         roomba.drivers(mot); 
     } else if ((command == "motor2") || (command.indexOf("m--o--t--o--r--2") > -1)){
         Debugln("motor2");
         uint8_t mot = 2;
         roomba.drivers(mot);    
     } else if ((command == "motor3") || (command.indexOf("m--o--t--o--r--3") > -1)){
         Debugln("motor3");
         uint8_t mot = 3;
         roomba.drivers(mot);
     } else if ((command == "motor4") || (command.indexOf("m--o--t--o--r--4") > -1)){
         Debugln("motor4");
         uint8_t mot = 4;
         roomba.drivers(mot);    
     } else if ((command == "motor5") || (command.indexOf("m--o--t--o--r--5") > -1)){
         Debugln("motor5");
         uint8_t mot = 5;
         roomba.drivers(mot);    
     } else if ((command == "motor6") || (command.indexOf("m--o--t--o--r--6") > -1)){
         Debugln("motor6");
         uint8_t mot = 6;
         roomba.drivers(mot);    
     } else if ((command == "motor7") || (command.indexOf("m--o--t--o--r--7") > -1)){
         Debugln("motor7");
         uint8_t mot = 7;
         roomba.drivers(mot);    
     } else if ((command == "motorAll") || (command.indexOf("m--o--t--o--r--A--l--l") > -1)){
         Debugln("motorAll");
         uint8_t mot = 7;
         roomba.drivers(mot);    
     } else if ((command == "tune") || (command.indexOf("t--u--n--e") > -1)){
         Debugln("Tune");
         playtune();
     
 
      // GAUCHE
     } else if ((command == "gauche") || (command.indexOf("g--a--u--c--h--e") > -1)){        
       Debugln("gauche");
       roomba.driveDirect(- Vitesse , Vitesse);

      // DROITE
     } else if ((command == "droite") || (command.indexOf("d--r--o--i--t--e") > -1)){        
       Debugln("droite");
       roomba.driveDirect(Vitesse , - Vitesse);

      // AVANT
     } else if ((command == "avant") || (command.indexOf("a--v--a--n--t") > -1)){
         Debugln("Avant");
         roomba.drive(Vitesse, 0);         
     // ARRIERE
     } else if ((command == "arriere") || (command.indexOf("a--r--r--i--e--r--e") > -1)){
         Debugln("arriere");
         roomba.drive( - Vitesse, 0);         
     }
     else {
       Debugln("Erreur de commande: ");
       Debugln(String(command.length()) + command);
     }

}  // End of function "ReadCommand"

void driveRoomba(){
   roomba.drive(Vitesse, Radius); 
}



void setup() {
  

  roomba.start();
  roomba.fullMode();
  //roomba.safeMode();

  playtune();

  btSerial.begin(19200);
  delay(50);

#ifdef UseArduinoMega
  Serial.begin(19200);
  delay(50);
  Debugln("------------ Init ------------");
#endif

}
void loop() {
   

   if (btSerial.available()) {
     while(btSerial.available()) { // While there is more to be read, keep reading.
       btCommand += (char)btSerial.read();
     }
     readCommand(btCommand);
     btCommand = ""; // No repeats
   }
     
  delay(50); // delay 50ms 
  
  if (Serial.available()) {
     while(Serial.available()) { // While there is more to be read, keep reading.
       serialCommand += (char)Serial.read();
     }
     readCommand(serialCommand);
     serialCommand = ""; // No repeats
   }
  delay(50);
}



