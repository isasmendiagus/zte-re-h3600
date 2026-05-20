// module: mt7915.ko
// function: HQA_SetCfgOnOff @ 0x26f014
// size: 204 bytes
//

bool HQA_SetCfgOnOff(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  code *pcVar3;
  bool bVar4;
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_SetCfgOnOff");
  }
  uVar1 = *(uint *)(param_3 + 0xc);
  *(char *)(param_1 + 0xa3ae36) = (char)((uint)*(undefined4 *)(param_3 + 0x14) >> 0x18);
  pcVar3 = *(code **)(iVar2 + 0xe4);
  bVar4 = pcVar3 == (code *)0x0;
  if (!bVar4) {
    (*pcVar3)(param_1,uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
                      uVar1 >> 0x18);
  }
  FUN_0026cdd0(param_3,param_2,2,bVar4);
  return bVar4;
}

