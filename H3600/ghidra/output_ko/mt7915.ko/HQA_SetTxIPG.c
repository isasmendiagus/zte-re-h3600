// module: mt7915.ko
// function: HQA_SetTxIPG @ 0x26fbb0
// size: 164 bytes
//

bool HQA_SetTxIPG(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  code *pcVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar3 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  iVar4 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk("%s(): val:%d,0x%04x\n","HQA_SetTxIPG",uVar3,uVar3);
  }
  pcVar2 = *(code **)(iVar4 + 0x70);
  bVar5 = pcVar2 == (code *)0x0;
  if (!bVar5) {
    (*pcVar2)(param_1,(int)(char)(uVar1 >> 0x18));
  }
  FUN_0026cdd0(param_3,param_2,2,bVar5);
  return bVar5;
}

