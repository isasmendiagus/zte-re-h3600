// module: mt7915.ko
// function: bss_color_collision_detect @ 0x206ac8
// size: 120 bytes
//

void bss_color_collision_detect(int param_1,int param_2,uint param_3)

{
  int iVar1;
  int extraout_r3;
  undefined4 unaff_r4;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  undefined4 unaff_lr;
  
  if (3 < DebugLevel) {
    printk("%s: received BSS color disabled = %d, color = %d\n","bss_color_collision_detect",param_2
           ,param_3);
  }
  if (param_2 != 0) {
    return;
  }
  if (*(byte *)(param_1 + 0xa3d) != param_3) {
    hc_bcolor_occupy(param_1,param_3);
    return;
  }
  if (*(uint *)(param_1 + 0x990) < 3) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: wdev(%d) bss not ready!!!\n","bss_color_trigger_collision",
           *(undefined1 *)(param_1 + 0xc));
    return;
  }
  iVar1 = *(int *)(param_1 + 0x14);
  if (iVar1 == 1) {
    *(undefined4 *)(param_1 + 0xa40) = jiffies;
    if (*(char *)(param_1 + 0xa3f) != '\0') {
      return;
    }
    *(undefined1 *)(param_1 + 0xa3f) = 1;
    iVar1 = param_1;
    if (2 < DebugLevel) {
      printk("collision is detected\n");
      iVar1 = extraout_r3;
    }
    if (*(char *)(param_1 + 0xa46) == '\0') {
      RTMPSetTimer(param_1 + 0xa48,(uint)*(byte *)(param_1 + 0xa45) * 1000,
                   (uint)*(byte *)(param_1 + 0xa45),iVar1,unaff_r4,unaff_r5,unaff_r6,unaff_lr);
      iVar1 = DebugLevel;
      *(undefined1 *)(param_1 + 0xa46) = 1;
      if (2 < iVar1) {
        printk("timer is triggered\n");
      }
    }
    iVar1 = *(int *)(param_1 + 0x14);
  }
  if (iVar1 != 2) {
    return;
  }
  if (*(char *)(param_1 + 0xa3f) != '\0') {
    return;
  }
  *(undefined1 *)(param_1 + 0xa3f) = 1;
  if (2 < DebugLevel) {
    printk("collision is detected\n");
  }
  if (*(char *)(param_1 + 0xa46) != '\0') {
    return;
  }
  RTMPSetTimer(param_1 + 0xa48,(uint)*(byte *)(param_1 + 0xa45) * 1000);
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + 0xa46) = 1;
  if (iVar1 < 3) {
    return;
  }
  printk("timer is triggered\n");
  return;
}

