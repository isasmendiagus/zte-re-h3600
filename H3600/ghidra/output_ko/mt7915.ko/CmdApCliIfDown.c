// module: mt7915.ko
// function: CmdApCliIfDown @ 0xc4550
// size: 192 bytes
//

undefined4 CmdApCliIfDown(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = (uint)**(byte **)(param_2 + 4);
  iVar2 = param_1 + uVar3 * 0x2137b0;
  cVar1 = (&DAT_00580e8d)[iVar2];
  if (2 < DebugLevel) {
    printk("cmd>  CMDTHREAD_APCLI_IF_DOWN! apidx=%u, apcliEn=%d\n",uVar3,cVar1,iVar2,param_4);
  }
  if (cVar1 == '\x01') {
    (&DAT_00580e8d)[param_1 + uVar3 * 0x2137b0] = 0;
    ApCliIfDown(param_1);
  }
  (&DAT_00580e8d)[param_1 + uVar3 * 0x2137b0] = cVar1;
  return 0;
}

