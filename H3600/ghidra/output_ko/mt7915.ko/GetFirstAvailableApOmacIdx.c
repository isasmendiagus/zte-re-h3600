// module: mt7915.ko
// function: GetFirstAvailableApOmacIdx @ 0xaca28
// size: 176 bytes
//

int GetFirstAvailableApOmacIdx(int param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  if ((*param_2 & 1) == 0) {
    *param_2 = *param_2 | 1;
    return 0;
  }
  if (1 < *(byte *)(param_1 + 0xbc0)) {
    uVar3 = param_2[1];
    if ((uVar3 & 2) == 0) {
      uVar1 = 2;
      uVar2 = 1;
    }
    else {
      uVar2 = 1;
      do {
        uVar2 = uVar2 + 1;
        uVar1 = 1 << (uVar2 & 0xff);
        if (uVar2 == *(byte *)(param_1 + 0xbc0)) goto LAB_000aca74;
      } while ((uVar1 & uVar3) != 0);
    }
    param_2[1] = uVar1 | uVar3;
    return *(byte *)(param_1 + 0xc7f) + uVar2;
  }
LAB_000aca74:
  if (DebugLevel < 0) {
    return -1;
  }
  printk("%s: Ext OmacIndex is not available\n","GetFirstAvailableApOmacIdx");
  return -1;
}

