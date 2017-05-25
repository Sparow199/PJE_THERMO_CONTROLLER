/*
  <generator>
  <handlers init="init" initGet="initGet" doGet="doGet"/>
  <properties persitence="volatile" interaction="alert" channel="tempchannel"/>
  <args>
  <arg name="level" type="uint16" />
  <arg name="blue" type="uint16" />
  <arg name="red" type="uint16" />
  </args>
  </generator>
*/

#include <stdio.h>
#include "generators.h"
#include "timers.h"
#include "channels.h"
#include "TM1637.h"
#include "S9013.h"
#include "P9813.h"
#include "NCP18WF104F03RC.h"
#include "base_shield_v20.h"
#include "button.h"
#include "rotaryangle.h"

static uint16_t globalCurrentTemperature = 0;
static uint16_t levelFromClient = 0;


uint16_t current_temp =0;

//les seuil d'alerte
uint16_t levelRed=0;
uint16_t levelBlue=0;
//level mode rotary ou a distance
uint16_t mode =0;


//l'affichage des chiffres
uint16_t chiffre1=0;
uint16_t chiffre2=0;


//prototypes
void alertBuzzer(uint8_t alert);
void setLevel(int16_t levelset);
void setRotaryLevel(int16_t levelrotaryset);
void display(uint16_t cur_temp);
void alarmAuto(uint16_t cur_temp);
void alarmManu();

/*
  Trouver et envoyer la température actuelle
  vers le client si elle a changé.
*/
static void sendTemp() {
  uint16_t old_temp =0;

  current_temp = NCP18WF104F03RC_read_temp(BASE_SHIELD_A0_0);

  if (current_temp != old_temp) {

    globalCurrentTemperature = (uint16_t) current_temp;
    old_temp = current_temp;
    display(current_temp);
    // appeler doGet pour écrire dans le canal tempchannel
    server_push( &tempchannel);
  }
  alarmManu();
  setLevel(levelFromClient);
}

static char init(void) {

  rflpc_sys_timer_init();
  init_buzzer(BASE_SHIELD_A3);
  rflpc_led_init();
  TM1637_init(clk, dio);
  NCP18WF104F03RC_init_pin(BASE_SHIELD_A0_0);
  init_button(BASE_SHIELD_A1);
  initColorRGB(BASE_SHIELD_D3);
  setColorRGB(0, 255, 255, 255);
  return set_timer( &sendTemp, 300);

}



static char initGet(struct args_t * args) {
  /*
    Reçoit les instructions de "level" depuis le client (page web)
    Et met a jour la puissance du chauffage et les LED
  */

  if (args) {
    levelFromClient = args -> level;
    levelRed = args -> red;
    levelBlue = args -> blue;
  }

  alarmAuto(current_temp);

  setLevel(levelFromClient);
  return 1;
}

static char doGet(struct args_t * args) {
  /*
    Ecrire la température qui sera ensuite envoyé à travers
    le canal tempchannel vers le client
  */
  out_uint(globalCurrentTemperature);
  return 1;
}

//affichage de la temperature courrante
void display(uint16_t cur_temp){

  chiffre1 = current_temp/10;
  chiffre2 = current_temp%10;

  TM1637_output_position(7,0,0,chiffre1);
  TM1637_output_position(7,1,0,chiffre2);
  TM1637_output_position(7,2,0,16);
  TM1637_output_position(7,3,0,17);

}


//lance le buzzer quand il faut trop chaud
void alertBuzzer(uint8_t alert) {

  if (alert == 1){
    set_buzzer();
  }else
    clr_buzzer();
};

//fonction qui permet de regler la puissance du chauffage
void setLevel(int16_t levelset) {

  switch (levelset) {
  case 0:
    rflpc_led_clr(RFLPC_LED_2 | RFLPC_LED_3 | RFLPC_LED_4);
    rflpc_led_set(RFLPC_LED_1);
    break;
  case 1:
    rflpc_led_clr(RFLPC_LED_3 | RFLPC_LED_4);
    rflpc_led_set(RFLPC_LED_1 | RFLPC_LED_2);
    break;
  case 2:
    rflpc_led_clr(RFLPC_LED_4);
    rflpc_led_set(RFLPC_LED_1 | RFLPC_LED_2 | RFLPC_LED_3);
    break;
  case 3:
    rflpc_led_set(RFLPC_LED_1 | RFLPC_LED_2 | RFLPC_LED_3 | RFLPC_LED_4) ;
    break;
  case 4:
    rflpc_led_clr(RFLPC_LED_1 | RFLPC_LED_2 | RFLPC_LED_3 | RFLPC_LED_4) ;
    rflpc_led_set(RFLPC_LED_1 | RFLPC_LED_2 | RFLPC_LED_3 | RFLPC_LED_4) ;
    break;
  default:
    rflpc_led_clr(RFLPC_LED_1 | RFLPC_LED_2 | RFLPC_LED_3 | RFLPC_LED_4);
    break;

  }

}

//alarme manuelle
void alarmManu(){
  //alarme manuelle
  if (get_value_button()==1){
    setLevel(0);
    setColorRGB(0,255, 0, 0);
    alertBuzzer(1);
  }
}

//allume la led selon la temperature ambiante et système d'alerte
void alarmAuto(uint16_t cur_temp){

  if (current_temp < levelBlue  ){
    setColorRGB(0,0, 0, 255);
    alertBuzzer(1);
  }else if (current_temp >= levelBlue && current_temp < levelRed ){
    setColorRGB(0, 0,255, 0);
    alertBuzzer(0);
  }else if (current_temp >= levelRed ) {
    setColorRGB(0,255, 0, 0);
    setLevel(0);
    alertBuzzer(1);
  }
}
