// module: mt7915.ko
// function: ApCliPbcApFoundHandler @ 0xc4404
// size: 332 bytes
//

undefined4 ApCliPbcApFoundHandler(int param_1,int param_2)

{
  undefined1 uVar1;
  char cVar2;
  uint uVar3;
  
  uVar3 = (uint)**(byte **)(param_2 + 4);
  uVar1 = (&DAT_00371cbd)[param_1 + uVar3 * 0x2137b0];
  if (0 < DebugLevel) {
    printk("cmd> channel=%d CMDTHREAD_APCLI_PBC_AP_FOUND!\n",uVar1);
  }
  rtmp_set_channel(param_1,&DAT_0036db58 + param_1 + uVar3 * 0x2137b0,uVar1);
  cVar2 = (&DAT_00580e8d)[param_1 + uVar3 * 0x2137b0];
  if (0 < DebugLevel) {
    printk("cmd>  CMDTHREAD_APCLI_PBC_AP_FOUND!apcliEn=%d\n",cVar2);
  }
  if (cVar2 == '\x01') {
    (&DAT_00580e8d)[param_1 + uVar3 * 0x2137b0] = 0;
    ApCliIfDown(param_1);
  }
  param_1 = param_1 + uVar3 * 0x2137b0;
  (&DAT_00580e8d)[param_1] = cVar2;
  *(undefined4 *)(&DAT_0036ee4c + param_1) = 2;
  *(undefined4 *)(&DAT_0036ee48 + param_1) = 0x27;
  return 0;
}

