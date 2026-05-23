// module: mt7915.ko
// function: MlmeAuthReqSanity @ 0x112234
// size: 216 bytes
//

undefined4
MlmeAuthReqSanity(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4,
                 byte *param_5,undefined4 *param_6,ushort *param_7)

{
  ushort uVar1;
  int iVar2;
  
  iVar2 = GetStaCfgByWdev();
  *(undefined4 *)param_5 = *param_3;
  *(undefined2 *)(param_5 + 4) = *(undefined2 *)(param_3 + 1);
  *param_6 = param_3[2];
  uVar1 = *(ushort *)((int)param_3 + 6);
  *param_7 = uVar1;
  if ((1 < uVar1) || ((*param_5 & 1) != 0)) {
    if (DebugLevel < 3) {
      return 0;
    }
    printk("MlmeAuthReqSanity fail - wrong algorithm\n");
    return 0;
  }
  if ((iVar2 != 0) && ((*(char *)(iVar2 + 0x3cc8) != '\0' && (*(int *)(iVar2 + 0x12e4) != 0)))) {
    *param_7 = *param_5 & 1;
  }
  if (DebugLevel < 3) {
    return 1;
  }
  printk("STA: %p\n",iVar2);
  return 1;
}

