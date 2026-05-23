// module: mt7915.ko
// function: ReservedAction @ 0xa1b08
// size: 84 bytes
//

void ReservedAction(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_2 + 0x908);
  if (uVar1 < 0x19) {
    return;
  }
  if (2 < DebugLevel) {
    printk("Rcv reserved category(%d) Action Frame\n",*(undefined1 *)(param_2 + 0x18));
    uVar1 = *(uint *)(param_2 + 0x908);
  }
  hex_dump("Reserved Action Frame",param_2,uVar1);
  return;
}

