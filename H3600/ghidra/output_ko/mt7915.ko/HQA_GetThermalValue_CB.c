// module: mt7915.ko
// function: HQA_GetThermalValue_CB @ 0x27b52c
// size: 88 bytes
//

void HQA_GetThermalValue_CB(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DebugLevel;
  iVar2 = *(int *)(param_1 + 0x1c);
  *(undefined4 *)(iVar2 + 0xa3ad8c) = *(undefined4 *)(param_2 + 4);
  if (2 < iVar1) {
    printk("%s(): value: 0x%x\n","HQA_GetThermalValue_CB",*(undefined4 *)(param_2 + 4));
  }
  complete(iVar2 + 0xa3ba38);
  return;
}

