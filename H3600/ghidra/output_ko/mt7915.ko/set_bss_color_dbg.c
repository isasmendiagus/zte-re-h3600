// module: mt7915.ko
// function: set_bss_color_dbg @ 0x207088
// size: 608 bytes
//

void set_bss_color_dbg(int param_1,int param_2,undefined4 param_3,uint param_4)

{
  undefined1 uVar1;
  undefined4 uVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  
  uVar2 = jiffies;
  iVar4 = *(int *)(param_1 + param_2 * 4 + 0xc);
  if (iVar4 == 0) {
    if (-1 < DebugLevel) {
      pcVar3 = "invalid wdev\n";
LAB_0020712c:
      printk(pcVar3);
      return;
    }
  }
  else if ((*(char *)(iVar4 + 0x28) == '\0') || (iVar5 = *(int *)(iVar4 + 0x14), 1 < iVar5 - 1U)) {
    if (-1 < DebugLevel) {
      pcVar3 = "BSS color is not applied for this wdev\n";
      goto LAB_0020712c;
    }
  }
  else {
    uVar1 = (undefined1)param_4;
    switch(param_3) {
    case 1:
      if (param_4 - 1 < 0x3f) {
        hc_bcolor_occupy(iVar4,param_4);
        return;
      }
      break;
    case 2:
      if (param_4 != 0) {
        *(undefined1 *)(iVar4 + 0xa45) = uVar1;
      }
      break;
    case 3:
      *(undefined1 *)(iVar4 + 0xa3f) = 1;
      *(undefined4 *)(iVar4 + 0xa40) = uVar2;
      if (iVar5 == 1) {
        if (*(char *)(iVar4 + 0xa46) != '\0') {
          return;
        }
        RTMPSetTimer(iVar4 + 0xa48,(uint)*(byte *)(iVar4 + 0xa45) * 1000);
        *(undefined1 *)(iVar4 + 0xa46) = 1;
        if (*(int *)(iVar4 + 0x14) != 2) {
          return;
        }
      }
      if (*(char *)(iVar4 + 0xa46) == '\0') {
        RTMPSetTimer(iVar4 + 0xa48,(uint)*(byte *)(iVar4 + 0xa45) * 1000);
        *(undefined1 *)(iVar4 + 0xa46) = 1;
      }
      break;
    case 4:
      if (iVar5 == 1) {
        bss_color_event_handler(iVar4);
        return;
      }
      break;
    case 5:
      if (((iVar5 == 1) && (param_4 - 1 < 0x3f)) && (*(byte *)(iVar4 + 0xa3d) != param_4)) {
        hc_bcolor_release(iVar4);
        hc_bcolor_occupy(iVar4,param_4);
        *(undefined1 *)(iVar4 + 0xa3d) = uVar1;
        *(undefined1 *)(iVar4 + 0xa3c) = 0;
        FUN_00206598(param_1,iVar4 + 0x98c,iVar4 + 0xa3c);
        wlan_operate_set_he_bss_color
                  (iVar4,*(undefined1 *)(iVar4 + 0xa3d),*(undefined1 *)(iVar4 + 0xa3c));
LAB_00207198:
        UpdateBeaconHandler(param_1,iVar4,2);
        return;
      }
      break;
    case 6:
      if (((iVar5 == 1) && (param_4 - 1 < 0x3f)) && (*(byte *)(iVar4 + 0xa3d) != param_4)) {
        *(undefined1 *)(iVar4 + 0xa3c) = 1;
        FUN_00206598(param_1,iVar4 + 0x98c,iVar4 + 0xa3c);
        wlan_operate_set_he_bss_color(iVar4,*(undefined1 *)(iVar4 + 0xa3d),1);
        *(undefined1 *)(iVar4 + 0xa3e) = uVar1;
        wlan_operate_set_he_bss_next_color(iVar4,param_4,*(undefined1 *)(iVar4 + 0xa44));
        goto LAB_00207198;
      }
    }
  }
  return;
}

