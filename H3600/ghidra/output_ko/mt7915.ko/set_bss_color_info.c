// module: mt7915.ko
// function: set_bss_color_info @ 0x2068f4
// size: 268 bytes
//

void set_bss_color_info(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_21 [5];
  
  uVar2 = *(undefined4 *)(param_1 + 8);
  if ((*(int *)(param_1 + 0x14) == 2) && (*(int *)(param_1 + 0x990) == 3)) {
    if (3 < DebugLevel) {
      printk("%s: receive BSS color info, disabled = %d, color = %d\n","set_bss_color_info",param_2,
             param_3);
    }
    if (*(byte *)(param_1 + 0xa3c) == param_2) {
      if (*(byte *)(param_1 + 0xa3d) == param_3) {
        return;
      }
    }
    else if (*(char *)(param_1 + 0xa3f) == '\x01') {
      *(undefined1 *)(param_1 + 0xa3f) = 0;
      if (*(char *)(param_1 + 0xa46) != '\0') {
        RTMPCancelTimer(param_1 + 0xa48,auStack_21);
        *(undefined1 *)(param_1 + 0xa46) = 0;
      }
      iVar1 = DebugLevel;
      *(undefined1 *)(param_1 + 0xa44) = 0;
      if (2 < iVar1) {
        printk("collision is alleviated\n");
      }
    }
    *(char *)(param_1 + 0xa3c) = (char)param_2;
    *(char *)(param_1 + 0xa3d) = (char)param_3;
    hc_bcolor_occupy(param_1,param_3);
    FUN_00206598(uVar2,param_1 + 0x98c,param_1 + 0xa3c);
    return;
  }
  return;
}

