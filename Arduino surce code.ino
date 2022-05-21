 #include <LiquidCrystal_I2C.h>
#include <DFRobot_DHT11.h>

LiquidCrystal_I2C lcd(0x27,16,2);  
DFRobot_DHT11 DHT;

#define DHT11_PIN 2 
int Relay_5v_command_humi=3,Relay_5v_command_temp=4,superior_limit_humy=40,inferior_limit_humy=30,superior_limit_temp=30,inferior_limit_temp=25;
char incoming_value,mode_humi='H',mode_temp='T';


void setup() {

  pinMode(Relay_5v_command_humi, OUTPUT);
  pinMode(Relay_5v_command_temp, OUTPUT);
  
  Serial.begin(9600);
  lcd.init();
  lcd.clear();         
  lcd.backlight();     

  
}

void loop() {
  

  DHT.read(DHT11_PIN);
  Serial.print(DHT.temperature);
  Serial.print("/");
  Serial.print(DHT.humidity);
  Serial.print("/");
  Serial.print(superior_limit_humy);
  Serial.print("/"); 
  Serial.print(inferior_limit_humy);
  Serial.print("/");
  Serial.print(superior_limit_temp);
  Serial.print("/"); 
  Serial.print(inferior_limit_temp);
  Serial.print("/");
  Serial.print(mode_humi);
  Serial.print("/"); 
  Serial.print(mode_temp);
  Serial.println("/");
  
  if(mode_humi=='H'){ lcd.setCursor(10,1); lcd.print("->Auto");}
       else { lcd.setCursor(10,1); lcd.print("->Man  ");}
       
  if(mode_temp=='T'){ lcd.setCursor(10,0); lcd.print("->Auto");}
       else { lcd.setCursor(10,0); lcd.print("->Man  ");}     
  
  
          
  lcd.setCursor(0,0);    
  lcd.print("Temp:");
  lcd.setCursor(5,0); 
  lcd.print(DHT.temperature,1);
  lcd .print((char)223); 
  lcd.print("C");
          
  lcd.setCursor(0,1);    
  lcd.print("Humi:");
  lcd.setCursor(5,1); 
  lcd.print(DHT.humidity,1);
  lcd.print("%");
     



  
  if(Serial.available()>0)
    { incoming_value= Serial.read();
      if(incoming_value=='H'){mode_humi='H';}
      if(incoming_value=='h') mode_humi='h';

      if(incoming_value=='T'){mode_temp='T';}
      if(incoming_value=='t') mode_temp='t';
      
      if(incoming_value=='U')if(superior_limit_humy<90) superior_limit_humy=superior_limit_humy+1; 
      if(incoming_value=='D')if(superior_limit_humy>60) superior_limit_humy=superior_limit_humy-1; 
      if(incoming_value=='u')if(inferior_limit_humy<60) inferior_limit_humy=inferior_limit_humy+1; 
      if(incoming_value=='d')if(inferior_limit_humy>20) inferior_limit_humy=inferior_limit_humy-1;
      
      if(incoming_value=='S')if(superior_limit_temp<35) superior_limit_temp=superior_limit_temp+1; 
      if(incoming_value=='J')if(superior_limit_temp>30) superior_limit_temp=superior_limit_temp-1; 
      if(incoming_value=='s')if(inferior_limit_temp<30) inferior_limit_temp=inferior_limit_temp+1; 
      if(incoming_value=='j')if(inferior_limit_temp>20) inferior_limit_temp=inferior_limit_temp-1;}
      
       
      if(mode_humi=='H')
        { 
          
          if(DHT.humidity<30)digitalWrite(Relay_5v_command_humi,LOW);
          else if(DHT.humidity>40)digitalWrite(Relay_5v_command_humi,HIGH);} 

      if(mode_humi=='h')
        { 
          
          if(DHT.humidity<inferior_limit_humy)digitalWrite(Relay_5v_command_humi,LOW);
          else if(DHT.humidity>superior_limit_humy)digitalWrite(Relay_5v_command_humi,HIGH); 
              
        }

        
        
        
        if(mode_temp=='T')
        { 
          
          if(DHT.temperature<25)digitalWrite(Relay_5v_command_temp,HIGH);
          else if(DHT.temperature>30)digitalWrite(Relay_5v_command_temp,LOW);} 

      if(mode_temp=='t')
        { 
          
          if(DHT.temperature<inferior_limit_temp)digitalWrite(Relay_5v_command_temp,HIGH);
          else if(DHT.temperature>superior_limit_temp)digitalWrite(Relay_5v_command_temp,LOW); 
              
        }

        
      delay(1000);   
   


 
  
                
 

  
}
