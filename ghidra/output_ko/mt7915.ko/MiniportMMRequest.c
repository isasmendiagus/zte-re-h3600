// module: mt7915.ko
// function: MiniportMMRequest @ 0xc6318
// size: 380 bytes
//

undefined4 MiniportMMRequest(int param_1,uint param_2,int param_3,uint param_4)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  bool bVar4;
  int local_4c;
  undefined1 auStack_48 [44];
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar1 = *(byte *)(iVar2 + 2);
  if (0x27 < bVar1) {
    printk(&_LC43,0x442);
    dump_stack();
  }
  if (bVar1 != 0) {
    __memzero(auStack_48,bVar1);
  }
  if (0x900 < param_4) {
    printk(&_LC44,0x445);
    dump_stack();
  }
  iVar2 = RTMPAllocateNdisPacket(param_1,&local_4c,auStack_48,bVar1,param_3,param_4);
  if (iVar2 == 0) {
    iVar2 = wdev_search_by_address(param_1,param_3 + 10);
    if (iVar2 != 0) {
      bVar4 = (param_2 & 0x80) != 0;
      if (bVar4) {
        param_2 = param_2 & 0x7f;
      }
      if (*(int *)(iVar2 + 0x14) == 2) {
        RTMPWakeUpWdev(param_1,iVar2);
      }
      *(undefined1 *)(local_4c + 0x4f) = 2;
      uVar3 = (**(code **)(*(int *)(iVar2 + 0x904) + 8))(param_1,local_4c,iVar2,param_2,bVar4);
      return uVar3;
    }
    RTMPFreeNdisPacket(param_1,local_4c);
    *(int *)(param_1 + 0x9db64) = *(int *)(param_1 + 0x9db64) + 1;
  }
  else if (1 < DebugLevel) {
    printk("MiniportMMRequest (error:: can\'t allocate NDIS PACKET)\n");
  }
  return 1;
}

