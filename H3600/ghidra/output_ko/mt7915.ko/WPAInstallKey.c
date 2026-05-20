// module: mt7915.ko
// function: WPAInstallKey @ 0x11cac8
// size: 340 bytes
//

void WPAInstallKey(undefined4 param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  uint __n;
  uint uVar2;
  
  uVar1 = *(uint *)(param_2 + 8);
  uVar2 = uVar1 & 0x10;
  if (uVar2 == 0) {
    if ((uVar1 & 0x20) == 0) {
      if ((uVar1 & 0x40) != 0) goto LAB_0011cb70;
      if ((uVar1 & 0x80) != 0) goto LAB_0011caf0;
      if ((uVar1 & 0x100) != 0) goto LAB_0011cb70;
      __n = (uint)*(byte *)(param_2 + 0x81);
      if ((__n == 0) || ((uVar1 & 0x1c00) != 0)) goto LAB_0011cb40;
LAB_0011cba8:
      if ((*(byte *)(param_2 + 0x60) + __n < 0x21) && ((uVar1 & 0x1e0) != 0)) {
        os_move_mem((void *)(param_2 + 0x10 + (uint)*(byte *)(param_2 + 0x60)),
                    (void *)(param_2 + 0x61),__n);
        uVar2 = *(uint *)(param_2 + 8) & 0x10;
        *(char *)(param_2 + 0x60) = *(char *)(param_2 + 0x81) + *(char *)(param_2 + 0x60);
      }
      goto LAB_0011cb10;
    }
LAB_0011caf0:
    __n = (uint)*(byte *)(param_2 + 0x81);
    *(undefined1 *)(param_2 + 0x60) = 0x10;
    if (__n != 0) {
      uVar1 = *(uint *)(param_2 + 8);
      goto joined_r0x0011cb8c;
    }
  }
  else {
LAB_0011cb70:
    __n = (uint)*(byte *)(param_2 + 0x81);
    *(undefined1 *)(param_2 + 0x60) = 0x20;
    if (__n != 0) {
      uVar1 = *(uint *)(param_2 + 8);
joined_r0x0011cb8c:
      if ((uVar1 & 0x1c00) == 0) goto LAB_0011cba8;
    }
LAB_0011cb10:
    if (uVar2 != 0) {
      if (param_3 == 0) {
        os_move_mem((void *)(param_2 + 0x30),(void *)(param_2 + 0x28),8);
        os_move_mem((void *)(param_2 + 0x38),(void *)(param_2 + 0x20),8);
        if (param_4 == 0) {
          return;
        }
        goto LAB_0011cb48;
      }
      os_move_mem((void *)(param_2 + 0x30),(void *)(param_2 + 0x20),8);
      os_move_mem((void *)(param_2 + 0x38),(void *)(param_2 + 0x28),8);
    }
  }
LAB_0011cb40:
  if (param_4 == 0) {
    return;
  }
LAB_0011cb48:
  HW_ADDREMOVE_KEYTABLE(param_1,param_2);
  return;
}

