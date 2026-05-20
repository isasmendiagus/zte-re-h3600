// module: mt7915.ko
// function: SendBTMConfirmEvent @ 0x225008
// size: 16 bytes
//

void SendBTMConfirmEvent(void)

{
  char in_stack_00000000;
  
  if (in_stack_00000000 != '\0') {
    return;
  }
  wext_send_btm_cfm_event_newapi();
  return;
}

