// module: mt7915.ko
// function: SendBTMRequestEvent @ 0x2250d0
// size: 16 bytes
//

void SendBTMRequestEvent(void)

{
  char in_stack_00000000;
  
  if (in_stack_00000000 != '\0') {
    return;
  }
  wext_send_btm_req_event();
  return;
}

