// module: mt7915.ko
// function: HQA_SetShortGI @ 0x2708e4
// size: 168 bytes
//

undefined4 HQA_SetShortGI(int param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  undefined1 uVar3;
  int iVar2;
  
  bVar1 = *(byte *)(param_1 + 0xa3ae36);
  if (DebugLevel < 3) {
    uVar3 = (undefined1)((uint)*(undefined4 *)(param_3 + 0xc) >> 0x18);
  }
  else {
    printk("%s band_idx:%d\n","HQA_SetShortGI",(uint)bVar1);
    uVar3 = (undefined1)((uint)*(undefined4 *)(param_3 + 0xc) >> 0x18);
  }
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)((uint)bVar1 * 0xd18 + iVar2 + 0x113c) = uVar3;
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

