// module: mt7915.ko
// function: RcGetMgmtQueueIdx @ 0xabe50
// size: 76 bytes
//

undefined4 RcGetMgmtQueueIdx(int param_1,int param_2)

{
  undefined4 uVar1;
  char *pcVar2;
  
  if (param_2 != 3) {
    uVar1 = asic_get_hwq_from_ac
                      (*(undefined4 *)(*(int *)(*(int *)(param_1 + 8) + 0x18) + 0x4328),
                       *(undefined1 *)(param_1 + 5),1);
    return uVar1;
  }
  pcVar2 = *(char **)(*(int *)(param_1 + 8) + 4);
  if (pcVar2 == (char *)0x0) {
    return 0x10;
  }
  if (*pcVar2 == '\0') {
    uVar1 = 0x10;
  }
  else {
    uVar1 = 0x14;
  }
  return uVar1;
}

