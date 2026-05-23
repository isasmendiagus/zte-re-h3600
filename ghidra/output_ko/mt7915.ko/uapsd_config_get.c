// module: mt7915.ko
// function: uapsd_config_get @ 0x1df008
// size: 116 bytes
//

void uapsd_config_get(int param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = GetStaCfgByWdev(*(undefined4 *)(param_1 + 8),param_1,param_3,param_4,param_4);
  iVar2 = *(int *)(param_1 + 8);
  if (iVar1 == 0 || *(char *)(param_1 + 0x8d8) == '\0') {
    return;
  }
  if (*(char *)(iVar1 + 0x41eb) == '\0') {
    return;
  }
  *param_2 = 1;
  param_2[1] = *(char *)(iVar2 + 0x794ca8) << 2 | *(char *)(iVar2 + 0x794ca9) << 1 |
               *(byte *)(iVar2 + 0x794caa) | *(char *)(iVar2 + 0x794ca7) << 3;
  return;
}

