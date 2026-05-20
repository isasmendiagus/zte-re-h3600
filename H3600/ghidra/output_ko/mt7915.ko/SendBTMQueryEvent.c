// module: mt7915.ko
// function: SendBTMQueryEvent @ 0x2248b8
// size: 16 bytes
//

void SendBTMQueryEvent(void)

{
  char in_stack_00000000;
  
  if (in_stack_00000000 != '\0') {
    return;
  }
  wext_send_btm_query_event_newapi();
  return;
}

