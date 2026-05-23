// module: switch.ko
// function: sw_qos_select_queue @ 0x18910
// size: 52 bytes
//

uint sw_qos_select_queue(void)

{
  uint uVar1;
  
  uVar1 = CSPKernel_skb_SelectQueue();
  uVar1 = uVar1 & 0xff;
  if (uVar1 - 1 < 8) {
    return 8 - uVar1 & 0xff;
  }
  if (uVar1 == 0x8f) {
    uVar1 = 7;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

