#include "MapFloat.h"
#include <EEPROM.h>
#include <TimerOne.h>
enum errores{errorups,errortemp,noerror};
errores errorsistema=noerror;
// definimos estructuras 
 typedef struct hora {
    unsigned int hour;
    unsigned int minutes;
    unsigned int seconds;
  }; // tipo hora con minutos , segundos y horas
  hora horareal;
  typedef struct t_humidity_sensor {
    float hysteresisriego;
    float gain;
    float offset;
    float valuehumedad;
    
  }; // tipo sensor de humedad
struct BOTON {
  bool estado;
  bool estadoanterior;
  unsigned long currentmillis;
  unsigned long previousmillis;
};
   
  typedef struct t_temperature_sensor {
    float hysteresiscalef;
    float hysteresisven;
    float gain;
    float offset;
    float temperature;
  }; // tipo sensor de temperatura
  
typedef struct t_control_zones {
    t_temperature_sensor temperatura;
    t_humidity_sensor humedad;
    BOTON BotonPuerta;
    float tempObjCal;
    float tempObjVen;
    float PorActivacion;
    float PorDesactivacion;
    unsigned long  currentMillist;
    unsigned long previuosMillist;
    unsigned long currentMillis;
    unsigned long previuosMillis;
    float humedadlimite;
    bool estado;
    bool calefactor;
    bool ventilador;
    bool riego;
    unsigned int error_indicator_temp;
    hora horariego;
    hora horariegof;
  }; // control de zona del invernadero
  t_control_zones zonaerror;
  t_control_zones errorzona2;
  t_control_zones riegozona0;
  t_control_zones riegozona1;
  typedef struct t_greenhouse_controller {
    hora horainvernadero;
    BOTON Botonencendido;
    t_control_zones zona[2];
    float supply_voltage;
    unsigned int error_indicator_ups;
    unsigned int errorindicadorpuerta;
    unsigned int pMillispuerta;
    unsigned int cMillispuerta;
    bool puerta=LOW;
    unsigned int previousMillislocal;
    unsigned int currentMillislocal;
  }; // control del invernadero total
 t_greenhouse_controller invernadero;
  t_greenhouse_controller invernaderodefecto;
int entrada;
float valorvoltaje;

int entrada2;
float valorvoltaje2;
int alternadorparpadeo=0;

// error sistema temperatura
float *temperature ;
// funcion boton
enum estadossistema {OFF,ON};
estadossistema estadoactual1 = OFF;
estadossistema estadoanterior=OFF;
int interval_encend=2000;
int interval_apag = 5000;
void tiempopulsacion(struct t_greenhouse_controller invernadero ,int intervalo_encender , int intervalo_apagar,bool pulsado3);
bool led_state2=LOW;
bool pulsado = HIGH;
int previuosMillisbot;
int currentMillisbot;
bool led_state;
int cambio=0;
// PARTE UPS
int entradaups;
int alternadorparpadeoe;
unsigned int vmillis1;
unsigned int vmillis;
unsigned int cmillis;
unsigned int cmillis1;
unsigned int cmillisz;
unsigned int cmillis1z;
unsigned int vmillis1z;
unsigned int vmillisz;
int c;
bool x;
String onString = __TIME__;
// Shell
String inString="";
int param1;
int param2;
int param3;
void creahoractual (String onString);
void setup() {
  Serial.begin(9600);
  pinMode(A1,OUTPUT);
  pinMode(A5,OUTPUT);
  pinMode(9,INPUT_PULLUP);
 Timer1.initialize(1000000); // periodo de cada cuanto llama
  Timer1.attachInterrupt(periodo);
invernadero.zona[0].temperatura.gain=10;
invernadero.zona[0].tempObjCal=5;
invernadero.zona[0].tempObjVen=26;
invernadero.zona[1].tempObjCal=5;
invernadero.zona[1].tempObjVen=26;
invernadero.zona[0].temperatura.hysteresiscalef=1;
invernadero.zona[0].temperatura.hysteresisven=1;
invernadero.zona[0].temperatura.gain=10;
invernadero.zona[0].temperatura.offset=-10;
invernadero.zona[1].temperatura.gain=10;
invernadero.zona[1].temperatura.offset=-10;
invernadero.zona[0].humedad.gain=25;
invernadero.zona[0].humedad.offset=-25;
invernadero.zona[1].humedad.gain=25;
invernadero.zona[1].humedad.hysteresisriego=1;
invernadero.zona[1].humedad.offset=-25;
invernadero.zona[0].PorActivacion=35;
invernadero.zona[0].PorDesactivacion=50;
invernadero.zona[1].PorActivacion=35;
invernadero.zona[1].PorDesactivacion=50;
invernadero.zona[1].horariegof.hour=21;
invernadero.zona[1].horariegof.minutes=30;
invernadero.zona[1].horariegof.seconds=00;
invernadero.zona[1].horariego.hour=6;
invernadero.zona[1].horariego.minutes=30;
invernadero.zona[1].horariego.seconds=00;
invernadero.zona[0].horariegof.hour=21;
invernadero.zona[0].horariegof.minutes=30;
invernadero.zona[0].horariegof.seconds=00;
invernadero.zona[0].horariego.hour=6;
invernadero.zona[0].horariego.minutes=30;
invernadero.zona[0].horariego.seconds=00;
invernadero.Botonencendido.estado=OFF;
invernadero.Botonencendido.estadoanterior=OFF;
invernaderodefecto.zona[0].temperatura.gain=10;
invernaderodefecto.zona[0].tempObjCal=5;
invernaderodefecto.zona[0].tempObjVen=26;
invernaderodefecto.zona[1].tempObjCal=5;
invernaderodefecto.zona[1].tempObjVen=26;
invernaderodefecto.zona[0].temperatura.hysteresiscalef=1;
invernaderodefecto.zona[0].temperatura.hysteresisven=1;
invernaderodefecto.zona[0].temperatura.gain=10;
invernaderodefecto.zona[0].temperatura.offset=-10;
invernaderodefecto.zona[1].temperatura.gain=10;
invernaderodefecto.zona[1].temperatura.offset=-10;
invernaderodefecto.zona[0].humedad.gain=25;
invernaderodefecto.zona[0].humedad.offset=-25;
invernaderodefecto.zona[1].humedad.gain=25;
invernaderodefecto.zona[1].humedad.hysteresisriego=1;
invernaderodefecto.zona[1].humedad.offset=-25;
invernaderodefecto.zona[0].PorActivacion=35;
invernaderodefecto.zona[0].PorDesactivacion=50;
invernaderodefecto.zona[1].PorActivacion=35;
invernaderodefecto.zona[1].PorDesactivacion=50;
invernaderodefecto.zona[1].horariegof.hour=21;
invernaderodefecto.zona[1].horariegof.minutes=30;
invernaderodefecto.zona[1].horariegof.seconds=00;
invernaderodefecto.zona[1].horariego.hour=6;
invernaderodefecto.zona[1].horariego.minutes=30;
invernaderodefecto.zona[1].horariego.seconds=00;
invernaderodefecto.zona[0].horariegof.hour=21;
invernaderodefecto.zona[0].horariegof.minutes=30;
invernaderodefecto.zona[0].horariegof.seconds=00;
invernaderodefecto.zona[0].horariego.hour=6;
invernaderodefecto.zona[0].horariego.minutes=30;
invernaderodefecto.zona[0].horariego.seconds=00;
invernaderodefecto.Botonencendido.estado=OFF;
invernaderodefecto.Botonencendido.estadoanterior=OFF;
Serial.println(EEPROM.read(5));
EEPROM.get(0,invernadero);
EEPROM.put(0,invernadero);
creahoractual(onString);
}

void loop() {
 pulsado=digitalRead(13);
 tiempopulsacion(&invernadero,5000,2000,pulsado); // primero encendido , segundo pagado
 Serial.println(invernadero.Botonencendido.estado);
  switch(invernadero.Botonencendido.estado){
    case(ON):
      
      digitalWrite(13,1);
      invernadero.Botonencendido.estadoanterior=invernadero.Botonencendido.estado;
      
        break; 
      case(OFF): 
       
       digitalWrite(13,0);
       invernadero.Botonencendido.estadoanterior=invernadero.Botonencendido.estado;
       
        break;
}
//EEPROM.put(0, invernadero);
if(invernadero.Botonencendido.estado==1){
 Shell();
 //Serial.println("Entra aqui antes Shell");
 if(invernadero.zona[0].estado==1){
 mapeohumedad(A2,0);
 mapeotemperatura(A1,0);
 error_temperatura(&invernadero.zona[0].temperatura.temperature,&invernadero.zona[0].currentMillist , &invernadero.zona[0].previuosMillist);
 Basculatemp(&invernadero.zona[0].temperatura,invernadero.zona[0].tempObjCal,invernadero.zona[0].tempObjVen,0);
 if(x==0){
 digitalWrite(4,invernadero.zona[0].calefactor);
 digitalWrite(11,invernadero.zona[0].ventilador);
 }
 if(x==1){
 digitalWrite(4,LOW);
 digitalWrite(11,LOW);
 }
 Basculahumedad(&invernadero.zona[0].humedad,invernadero.zona[0].PorActivacion ,invernadero.zona[0].PorDesactivacion ,0);
 if(invernadero.zona[0].riego==1){
  cmillisz = millis();
  vmillis1z=millis();
  //Serial.println(vmillis1z);
  digitalWrite(2,LOW);
  if(cmillisz-vmillisz<1000){
    digitalWrite(2,HIGH);
  }
 }
  if(invernadero.zona[0].riego==0){
  cmillis1z = millis();
  vmillisz=millis();
  digitalWrite(2,LOW);
  if(cmillis1z-vmillis1z<1000){
    digitalWrite(2,HIGH);
  }
  }
 }
 if(invernadero.zona[1].estado==1){
 mapeohumedad(A4,1);
// Serial.println(invernadero.zona[0].humedad.valuehumedad); 
 mapeotemperatura(A3,1);
//Serial.println(invernadero.zona[1].temperatura.temperature);
error_temperatura(&invernadero.zona[1].temperatura.temperature,&invernadero.zona[1].currentMillist , &invernadero.zona[1].previuosMillist);
 //Serial.println(errorsistema);
 

 
 Basculatemp(&invernadero.zona[1].temperatura,invernadero.zona[1].tempObjCal,invernadero.zona[1].tempObjVen,1);
 if(x==0){
 digitalWrite(3,invernadero.zona[1].calefactor);
 digitalWrite(12,invernadero.zona[1].ventilador);
 }
 if(x==1){
 digitalWrite(3,LOW);
 digitalWrite(12,LOW);
 }
 
 Basculahumedad(&invernadero.zona[1].humedad,invernadero.zona[1].PorActivacion ,invernadero.zona[1].PorDesactivacion ,1);
 Serial.println(invernadero.zona[1].riego);
 if(invernadero.zona[1].riego==1 ){
  cmillis = millis();
  vmillis1=millis();
  Serial.println(vmillis1);
  if(cmillis-vmillis>1000){
  digitalWrite(5,LOW);
  }
  if(cmillis-vmillis<1000){
    digitalWrite(5,HIGH);
  }
 }
  if(invernadero.zona[1].riego==0 ){
  cmillis1 = millis();
  vmillis=millis();
  if(cmillis-vmillis>1000){
  digitalWrite(5,LOW);
  }
  if(cmillis1-vmillis1<1000){
    digitalWrite(5,HIGH);
  }
 }
 
 
 
 }
//Serial.println(invernadero.zona[0].riego);
//Parte ups
invernadero.supply_voltage = mapFloat(analogRead(A0), 0,920, 0.0 , 12.0) ;  // Alimentacion que llega al invernadero
//Serial.println(invernadero.supply_voltage);
 porcentajebateria(invernadero.supply_voltage,12.0,10.0,&invernadero);
 //Serial.println(invernadero.error_indicator_ups);
 
 if(invernadero.error_indicator_ups==1){
  parpadeo(1000,1000,10,&invernadero.zona[0]);
  //parpadeo(2000,4000,12,&invernadero.zona[1]);
  //parpadeo(2000,2000,12,&errorzona2); 
 }
 x=digitalRead(6);
   if (x==1){
    invernadero.cMillispuerta=millis();
    invernadero.puerta=HIGH;
      if (invernadero.cMillispuerta-invernadero.pMillispuerta > 10000){
      invernadero.errorindicadorpuerta=HIGH;
   }
   }
   if(x==0){
   invernadero.puerta=LOW;
   invernadero.pMillispuerta=invernadero.cMillispuerta;
   invernadero.errorindicadorpuerta=LOW;
   //Serial.println("entra aqui");
}
if(invernadero.errorindicadorpuerta==1){
  parpadeo(1000,5000,10,&invernadero.zona[1]);
}
   }
}


// Función para mapear , funciona con uno , con dos tmbn pero muy sensible
 void mapeotemperatura( int numeroled , int numerozona) {
  entrada = analogRead(numeroled); // Valor de la entrada
  //Serial.println(invernadero.zona[numerozona].temperatura.temperature);
  valorvoltaje= mapFloat(entrada , 0 , 1023, 0 , 5);
  //float x = (valorvoltaje * invernadero.zona[numerozona].temperatura.gain)+invernadero.zona[numerozona].temperatura.offset;
  invernadero.zona[numerozona].temperatura.temperature = (valorvoltaje * invernadero.zona[numerozona].temperatura.gain)+invernadero.zona[numerozona].temperatura.offset;
}
// Funcion map para humedad , funciona con los dos pero muy sensible
void mapeohumedad( int numeroled , int numerozona) {
  entrada2 = analogRead(numeroled); // Valor de la entrada
  //Serial.println(valorvoltaje2);
  valorvoltaje2= mapFloat(entrada2 , 0 , 1023.0, 0 , 5.0);
  //Serial.println(valorvoltaje2);
  if(valorvoltaje2>1){
  invernadero.zona[numerozona].humedad.valuehumedad = (valorvoltaje2 * invernadero.zona[numerozona].humedad.gain)+invernadero.zona[numerozona].humedad.offset;
  //Serial.println(invernadero.zona[numerozona].humedad.valuehumedad);
  }
  else{
    invernadero.zona[numerozona].humedad.valuehumedad=0;
    //Serial.println(invernadero.zona[numerozona].humedad.valuehumedad);
  }
}   // Funcion error temperatura funciona ya
void error_temperatura( float *temperatura, unsigned long *current_millis, unsigned long previous_millis) {
  float temperatura_alta=30;
  //Serial.println(*temperatura);
  *current_millis = millis();
  if (*temperatura > temperatura_alta && (*current_millis - previous_millis) >= 6000) {
   // invernadero.error_indicator_puerta = 1;
  }
  else if (*temperatura < temperatura_alta) {
   // invernadero.error_indicator_puerta= 0;
   // previous_millis = millis();
  }
  //if(invernadero.error_indicator_puerta=1){
  // parpadeo(1000,1000,3,&zonaerror);
  }
  //return errorestado;

void tiempopulsacion(struct t_greenhouse_controller * invernadero , int intervalo_encender , int intervalo_apagar, bool pulsado1){
   
   
   //Serial.println(pulsado1);
   if(pulsado1==1){
    invernadero->Botonencendido.currentmillis=millis();
  if ((invernadero->Botonencendido.currentmillis - invernadero->Botonencendido.previousmillis) > intervalo_encender && invernadero->Botonencendido.estadoanterior==OFF ){
    invernadero->Botonencendido.previousmillis=invernadero->Botonencendido.currentmillis;
    Serial.println("Boton pulsado");
    invernadero->Botonencendido.estado=ON;
  }
     if ((invernadero->Botonencendido.currentmillis - invernadero->Botonencendido.previousmillis) > intervalo_apagar && invernadero->Botonencendido.estadoanterior==ON){
    invernadero->Botonencendido.previousmillis=invernadero->Botonencendido.currentmillis;
    Serial.println("Boton  no pulsado");
    invernadero->Botonencendido.estado=OFF;
     }
   }
   
}
float Basculatemp(t_temperature_sensor *temperatura, float tempObjcalef, float tempObjven ,  int numerozona)  // Funciona bien con puntero y estructura
{
  //Serial.println(temperatura->temperature);
  //Serial.println(tempObjven);
  if (temperatura->temperature < (tempObjcalef - (temperatura->hysteresiscalef)))
  {
    invernadero.zona[numerozona].calefactor = 1;
    invernadero.zona[numerozona].ventilador = 0;
  }
  else if (temperatura->temperature > (tempObjven + temperatura->hysteresisven))
  {
    invernadero.zona[numerozona].calefactor = 0;
    invernadero.zona[numerozona].ventilador = 1;
  }
  
   
  
  
}

void Basculahumedad(t_humidity_sensor *humedad, float porActivacion, float porDesactivacion, int numberzona)  // Funciona  poniendo punteros
{
  //Serial.println(humedad->valuehumedad);
  if (humedad->valuehumedad > (porDesactivacion + humedad->hysteresisriego))
  {
    //digitalWrite(5,HIGH);
    invernadero.zona[numberzona].riego=0;       // Apaga
  }
  else if (humedad->valuehumedad< (porActivacion - humedad->hysteresisriego))
  {
    invernadero.zona[numberzona].riego=1;           // Enciende
  }
  else
  {
    invernadero.zona[numberzona].riego=invernadero.zona[numberzona].riego;
  }

 // Serial.println(invernadero.zona[0].riego);
  

}
         // Control UPS , alimentacion

void   porcentajebateria(float bateria, float tempmax , float tempmin, t_greenhouse_controller * invernadero){      // Funciona con punteros
   invernadero->currentMillislocal=millis();
// Serial.println (bateria);
// Serial.println (estadoactual);
  if (tempmin>bateria && invernadero->currentMillislocal - invernadero->previousMillislocal>500){
    invernadero->error_indicator_ups = 1 ;
    
   
  }
  if (tempmin < bateria){
    invernadero->error_indicator_ups=0;
    invernadero->previousMillislocal=invernadero->currentMillislocal;
    
  
  }
    
}
// funcion de parpadeo general calefactores , ventiladores , y demas , no para errores
void parpadeo ( int tiempoencendido , int tiempoapagado , int numeroled ,t_control_zones *zona){
  zona->currentMillis=millis();
  if(zona->currentMillis - zona->previuosMillis >= tiempoencendido && alternadorparpadeo==0){
    digitalWrite(numeroled,HIGH);
    zona->previuosMillis=zona->currentMillis;
    alternadorparpadeo=1;
    }
    if(zona->currentMillis - zona->previuosMillis >= tiempoapagado && alternadorparpadeo==1){
    digitalWrite(numeroled,LOW);
    zona->previuosMillis=zona->currentMillis;
    alternadorparpadeo=0;
    }
   // Serial.println(alternadorparpadeo);
}

void parpadeo2 ( int tiempoencendido , int tiempoapagado , int numeroled ,t_control_zones *zona){
  zona->currentMillis=millis();
  if(zona->currentMillis - zona->previuosMillis >= tiempoencendido && alternadorparpadeo==0){
    digitalWrite(numeroled,HIGH);
    zona->previuosMillis=zona->currentMillis;
    alternadorparpadeoe=1;
    }
    if(zona->currentMillis - zona->previuosMillis >= tiempoapagado && alternadorparpadeo==1){
    digitalWrite(numeroled,LOW);
    zona->previuosMillis=zona->currentMillis;
    alternadorparpadeoe=0;
    }
   // Serial.println(alternadorparpadeo);
}

 void Shell (void) {
  String cmd;
  String cadenauxiliar;
  unsigned int strLength;
  cmd = Serial.readString();
  cmd.toUpperCase();
  Serial.println(cmd);
  if (cmd == "HELP") {
    Serial.println(F("A continuación se muestrán los comandos aceptados que permiten modificar los parámetros del sistema."));
    Serial.println(F("Modificar parametro de Zona. : ZONAX_TEMP XX , ZONAX_HORA XX , ZONAX_HUM_XX"));
    Serial.println(F("Modificar parametro de inveradero: CONTROL HORA"));
    Serial.println(F("COGIDO PARA PUERTA: PUERTA XXXXXX"));
    Serial.println(F("Para que se impriman los parametros por defecto: STATUS"));
}
if ((cmd.substring(0, cmd.indexOf(' ')) == "ZONA0_TEMPV"))  {
   cadenauxiliar = cmd.substring(cmd.indexOf(' ')+1) ;
   c=cadenauxiliar.toInt();
   invernadero.zona[0].tempObjVen=c;
   Serial.println( "Temperatura de la zona 0 actualizada a ");
   Serial.println(c);
  }
  if ((cmd.substring(0, cmd.indexOf(' ')) == "ZONA1_TEMPV"))  {
   cadenauxiliar = cmd.substring(cmd.indexOf(' ')+1) ;
   c=cadenauxiliar.toInt();
   invernadero.zona[1].tempObjVen=c;
   Serial.println( "Temperatura de la zona 1 actualizada a ");
   Serial.println(c);
  }
  if ((cmd.substring(0, cmd.indexOf(' ')) == "ZONA0_TEMPC"))  {
   cadenauxiliar = cmd.substring(cmd.indexOf(' ')+1) ;
   c=cadenauxiliar.toInt();
   invernadero.zona[0].tempObjCal=c;
   Serial.println( "Temperatura de la zona 0 actualizada a ");
   Serial.println(c);
  }
  if ((cmd.substring(0, cmd.indexOf(' ')) == "ZONA1_TEMPC"))  {
   cadenauxiliar = cmd.substring(cmd.indexOf(' ')+1) ;
   c=cadenauxiliar.toInt();
   invernadero.zona[1].tempObjCal=c;
   Serial.println( "Temperatura de la zona 1 actualizada a ");
   Serial.println(c);
  }
  if ((cmd.substring(0, cmd.indexOf(' ')) == "ZONA1_HUM"))  {
   cadenauxiliar = cmd.substring(cmd.indexOf(' ')+1) ;
   c=cadenauxiliar.toInt();
   invernadero.zona[1].humedadlimite=c; // falta cambiarlo
   Serial.println( "Humedad de la zona 1 actualizada a ");
   Serial.println(c);
  }
 if ((cmd.substring(0, cmd.indexOf(' ')) == "ZONA0_HUM"))  {
   cadenauxiliar = cmd.substring(cmd.indexOf(' ')+1) ;
   c=cadenauxiliar.toInt();
   invernadero.zona[0].humedadlimite=c; // falta cambiarlo
   Serial.println( "Humedad de la zona 0 actualizada a ");
   Serial.println(invernadero.zona[0].humedadlimite);
  }
  if ((cmd.substring(0, cmd.indexOf(' ')) == "ZONA1_ON"))  {
   invernadero.zona[1].estado=1; // falta cambiarlo
   Serial.println( "Estado de la zona 1 actualizada a ");
   Serial.println("ON");
   
  }
  if (cmd.substring(0, cmd.indexOf(' ')) == "RESET_DEFAULT")  {
    String auxiliar= cmd.substring(cmd.indexOf(' ')+1);
    int cad;
    cad = auxiliar.toInt();
    Serial.println(cad);
    if(cad==6666){
    Serial.println( "RESET A FABRICA DE EPRROM");
    EEPROM.put (0, invernaderodefecto);
  
  }
    }
  
   
   
  
  if ((cmd.substring(0, cmd.indexOf(' ')) == "ZONA0_ON"))  {
   invernadero.zona[0].estado=1; // falta cambiarlo
   Serial.println( "Estado de la zona 0 actualizada a ");
   Serial.println("ON");
   
  }
  if ((cmd.substring(0, cmd.indexOf(' ')) == "ZONA1_OFF"))  {
   invernadero.zona[1].estado=0; // falta cambiarlo
   Serial.println( "Estado de la zona 1 actualizada a ");
   Serial.println("OFF");
   
  }
  if ((cmd.substring(0, cmd.indexOf(' ')) == "ZONA0_OFF"))  {
   invernadero.zona[0].estado=0; // falta cambiarlo
   Serial.println( "Estado de la zona 0 actualizada a ");
   Serial.println("OFF");
   
  }
   if ((cmd.substring(0, cmd.indexOf(' ')) == "ZONA0_HORAEM"))  {
   dataInput( &param1,&param2, &param3, cmd, 0 );
  }
  if ((cmd.substring(0, cmd.indexOf(' ')) == "ZONA0_HORAFIN"))  {
   dataInputf( &param1,&param2, &param3, cmd, 0 );
  }
  if ((cmd.substring(0, cmd.indexOf(' ')) == "ZONA1_HORAEM"))  {
   dataInput( &param1,&param2, &param3, cmd , 1);
  }
   if ((cmd.substring(0, cmd.indexOf(' ')) == "ZONA1_HORAFIN"))  {
   dataInputf( &param1,&param2, &param3, cmd, 1 );
  }
 }
  void dataInput(int *param1, int *param2, int *param3, String cmd, int numerozona) {
  String auxStr; 
    inString =cmd.substring(cmd.indexOf(' '));
    Serial.println(inString);
    auxStr = inString.substring(0, inString.indexOf(":"));
    *param1 = auxStr.toInt();
    invernadero.zona[numerozona].horariego.hour=*param1;
    auxStr = inString.substring(inString.indexOf(":") + 1);
    auxStr = auxStr.substring(0, auxStr.indexOf(":"));
    *param2 = auxStr.toInt();
    invernadero.zona[numerozona].horariego.minutes = *param2;
    auxStr = inString.substring(inString.indexOf(":") + 1);
    auxStr = auxStr.substring(auxStr.indexOf(":")+1);
    *param3 = auxStr.toInt();
    invernadero.zona[numerozona].horariego.seconds=*param3;
    Serial.print(invernadero.zona[numerozona].horariego.hour);
    Serial.print(":");
    Serial.print(invernadero.zona[numerozona].horariego.minutes);
    Serial.print(":");
    Serial.print(invernadero.zona[numerozona].horariego.seconds);
  }
   void dataInputf(int *param1, int *param2, int *param3, String cmd, int numerozona) {
  String auxStr; 
    inString =cmd.substring(cmd.indexOf(' '));
    Serial.println(inString);
    auxStr = inString.substring(0, inString.indexOf(":"));
    *param1 = auxStr.toInt();
    invernadero.zona[numerozona].horariegof.hour=*param1;
    auxStr = inString.substring(inString.indexOf(":") + 1);
    auxStr = auxStr.substring(0, auxStr.indexOf(":"));
    *param2 = auxStr.toInt();
    invernadero.zona[numerozona].horariegof.minutes = *param2;
    auxStr = inString.substring(inString.indexOf(":") + 1);
    auxStr = auxStr.substring(auxStr.indexOf(":")+1);
    *param3 = auxStr.toInt();
    invernadero.zona[numerozona].horariegof.seconds=*param3;
    Serial.print(invernadero.zona[numerozona].horariegof.hour);
    Serial.print(":");
    Serial.print(invernadero.zona[numerozona].horariegof.minutes);
    Serial.print(":");
    Serial.print(invernadero.zona[numerozona].horariegof.seconds);
  }
    
 int relojcmp(hora horaActual , hora horaprevia){
  int b=0;
  if(horaActual.hour>horaprevia.hour){
    b=1;
  }
  if(horaActual.hour==horaprevia.hour){
     if(horaActual.minutes>horaprevia.minutes){
      b=1;
     }
     if(horaActual.minutes=horaprevia.minutes){
          if(horaActual.seconds>horaprevia.seconds){
            b=1;
          }
          if(horaActual.seconds==horaprevia.seconds){
            b=0;
          }
          if(horaActual.seconds<horaprevia.seconds){
            b=-1;
          }
     }
     if(horaActual.minutes<horaprevia.minutes){
      b=-1;
     }
  }
  
  if(horaActual.hour<horaprevia.hour){
    b=-1;
  }
  Serial.println(b);
  return b;
}

void periodo (void){
 horareal.seconds += 1 ;
  if(horareal.seconds>=60){
    horareal.seconds=0;
    horareal.minutes++;
  }
  if(horareal.minutes>=60){
    horareal.seconds=0;
    horareal.minutes=0;
    horareal.hour++;
  }
  if(horareal.hour>=24){
    horareal.seconds=0;
    horareal.minutes=0;
    horareal.hour=0;
  }
}

void creahoractual (String onString){
  String auxStr2;
    auxStr2 = onString.substring(0, onString.indexOf(":"));
    horareal.hour=auxStr2.toInt();
    auxStr2 = onString.substring(onString.indexOf(":") + 1);
    auxStr2 = auxStr2.substring(0, auxStr2.indexOf(":"));
    horareal.minutes=auxStr2.toInt();
    auxStr2 = onString.substring(onString.indexOf(":")+1); // Revisar segundos
    auxStr2 = auxStr2.substring(auxStr2.indexOf(":")+1);
    horareal.seconds=auxStr2.toInt();
//    Serial.print(horareal.hour);
//    Serial.print(":");
//    Serial.print(horareal.minutes);
//    Serial.print(":");
//    Serial.print(horareal.seconds);
    
    

}














 
