// module: mt7915.ko
// function: HQA_SetDPD @ 0x26e74c
// size: 188 bytes
//

int HQA_SetDPD(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  code *pcVar4;
  
  iVar3 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_SetDPD",param_3,0,0);
  }
  uVar1 = *(uint *)(param_3 + 0xc);
  pcVar4 = *(code **)(iVar3 + 0x84);
  uVar2 = *(uint *)(param_3 + 0x10);
  if (pcVar4 == (code *)0x0) {
    param_1 = 1;
  }
  iVar3 = param_1;
  if (pcVar4 != (code *)0x0) {
    iVar3 = 0;
    (*pcVar4)(param_1,(int)(char)(uVar2 >> 0x18),(int)(char)(uVar1 >> 0x18),uVar2,
              uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
              uVar1 >> 0x18,
              uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
              uVar2 >> 0x18);
  }
  FUN_0026cdd0(param_3,param_2,2,iVar3);
  return iVar3;
}

