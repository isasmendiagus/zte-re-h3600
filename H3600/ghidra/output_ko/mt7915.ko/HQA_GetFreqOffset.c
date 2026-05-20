// module: mt7915.ko
// function: HQA_GetFreqOffset @ 0x26ef34
// size: 220 bytes
//

undefined4 HQA_GetFreqOffset(int param_1,undefined4 param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  uint local_1c [2];
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  local_1c[0] = 0;
  if (DebugLevel < 3) {
    pcVar1 = *(code **)(iVar2 + 0x50);
    if (pcVar1 == (code *)0x0) {
LAB_0026efbc:
      FUN_0026cdd0(param_3,param_2,2,1);
      return 1;
    }
    (*pcVar1)(param_1,local_1c);
  }
  else {
    printk(&_LC11,"HQA_GetFreqOffset");
    pcVar1 = *(code **)(iVar2 + 0x50);
    if (pcVar1 == (code *)0x0) goto LAB_0026efbc;
    (*pcVar1)(param_1,local_1c);
  }
  local_1c[0] = local_1c[0] << 0x18 | (local_1c[0] >> 8 & 0xff) << 0x10 |
                (local_1c[0] >> 0x10 & 0xff) << 8 | local_1c[0] >> 0x18;
  *(uint *)(param_3 + 0xe) = local_1c[0];
  FUN_0026cdd0(param_3,param_2,6,0);
  return 0;
}

