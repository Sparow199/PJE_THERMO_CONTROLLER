/*
<generator>
<handlers doGet="doGet"/>
<args>
 <arg name="val" type="uint8"/>
</args>
</generator>
*/


static char doGet(struct args_t *args){
  rflpc_led_init();
  if(args){
    if(args->val==1){
      rflpc_led_set(RFLPC_LED_1);
      rflpc_led_clr(RFLPC_LED_2);
      rflpc_led_clr(RFLPC_LED_3);
      rflpc_led_clr(RFLPC_LED_4);
    }
    else if(args->val==2){
      rflpc_led_set(RFLPC_LED_2);
      rflpc_led_clr(RFLPC_LED_1);
      rflpc_led_clr(RFLPC_LED_3);
      rflpc_led_clr(RFLPC_LED_4);
    }
    else if(args->val==3){
      rflpc_led_set(RFLPC_LED_3);
      rflpc_led_clr(RFLPC_LED_1);
      rflpc_led_clr(RFLPC_LED_2);
      rflpc_led_clr(RFLPC_LED_4);
    }
    else if(args->val==4){
      rflpc_led_set(RFLPC_LED_4);
      rflpc_led_clr(RFLPC_LED_2);
      rflpc_led_clr(RFLPC_LED_3);
      rflpc_led_clr(RFLPC_LED_1);
    }
    }
    else {
      out_str("Erreur, il manque d'arguments");
    }

    return 1;
  }
