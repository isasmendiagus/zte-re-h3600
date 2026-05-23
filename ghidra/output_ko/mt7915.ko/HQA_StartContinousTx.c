// module: mt7915.ko
// function: HQA_StartContinousTx @ 0x26e80c
// size: 260 bytes
//

int HQA_StartContinousTx(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  code *pcVar5;
  
  iVar4 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_StartContinousTx",param_3,0,0,0);
  }
  iVar3 = param_1 + 0xa3a000;
  *(char *)(param_1 + 0xa3ad68) = (char)((uint)*(undefined4 *)(param_3 + 0xc) >> 0x18);
  *(char *)(param_1 + 0xa3ad65) = (char)((uint)*(undefined4 *)(param_3 + 0x10) >> 0x18);
  *(char *)(param_1 + 0xa3ad5e) = (char)((uint)*(undefined4 *)(param_3 + 0x14) >> 0x18);
  uVar1 = *(uint *)(param_3 + 0x18);
  *(char *)(param_1 + 0xa3ad6c) = (char)(uVar1 >> 0x18);
  uVar2 = *(uint *)(param_3 + 0x1c);
  pcVar5 = *(code **)(iVar4 + 0x9c);
  if (pcVar5 == (code *)0x0) {
    iVar3 = 1;
  }
  if (pcVar5 != (code *)0x0) {
    iVar3 = 0;
    (*pcVar5)(param_1,(int)(char)(uVar2 >> 0x18),1,uVar2,
              uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
              uVar1 >> 0x18,
              uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
              uVar2 >> 0x18);
  }
  FUN_0026cdd0(param_3,param_2,2,iVar3);
  return iVar3;
}

