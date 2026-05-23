// module: mt7915.ko
// function: HQA_SetPreamble @ 0x270da4
// size: 164 bytes
//

undefined4 HQA_SetPreamble(int param_1,undefined4 param_2,int param_3)

{
  undefined1 uVar2;
  int iVar1;
  
  if (DebugLevel < 3) {
    uVar2 = (undefined1)((uint)*(undefined4 *)(param_3 + 0xc) >> 0x18);
  }
  else {
    printk(&_LC11,"HQA_SetPreamble");
    uVar2 = (undefined1)((uint)*(undefined4 *)(param_3 + 0xc) >> 0x18);
  }
  iVar1 = net_ad_wrap_service(param_1);
  *(undefined1 *)((uint)*(byte *)(param_1 + 0xa3ae36) * 0xd18 + iVar1 + 0x1135) = uVar2;
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

