// module: mt7915.ko
// function: dump_he_ies @ 0x2057dc
// size: 752 bytes
//

void dump_he_ies(undefined4 param_1,char *param_2,uint param_3)

{
  byte bVar1;
  uint uVar2;
  char *pcVar3;
  uint uVar4;
  
  if (0 < DebugLevel) {
    printk("\n%s:\n",param_1);
  }
  if ((param_3 == 0) || (*param_2 != -1)) {
    return;
  }
  pcVar3 = param_2;
  do {
    if (0 < DebugLevel) {
      printk("[EID:%d][Len:%d][EID_EXT:%d] ",0xff,pcVar3[1],pcVar3[2]);
      switch(pcVar3[2]) {
      case '#':
        if (0 < DebugLevel) {
          printk("HE_CAPS\n");
        }
        break;
      case '$':
        if (0 < DebugLevel) {
          printk("HE_OP\n");
        }
        break;
      case '%':
        if (0 < DebugLevel) {
          printk("UORA_PARAM_SET\n");
        }
        break;
      case '&':
        if (0 < DebugLevel) {
          printk("MU_EDCA_PARAM\n");
        }
        break;
      case '\'':
        if (0 < DebugLevel) {
          printk("SR_PARAM_SET\n");
        }
        break;
      default:
        if (0 < DebugLevel) {
          printk("EID_EXT_NOT_RECOGNIZED\n");
        }
        break;
      case ')':
        if (0 < DebugLevel) {
          printk("NDP_FB_REPORT\n");
        }
        break;
      case '*':
        if (0 < DebugLevel) {
          printk("BSS_COLOR_CHANGE_ANNOUNCE\n");
        }
        break;
      case '+':
        if (0 < DebugLevel) {
          printk("QUIET_TIME_PERIOD\n");
        }
      }
    }
    bVar1 = pcVar3[1];
    uVar4 = bVar1 - 1;
    pcVar3 = param_2 + 3;
    if (uVar4 != 0) {
      uVar2 = 0;
      do {
        if ((uVar2 & 0xf) == 0) {
          if ((0 < DebugLevel) && (printk("0x%04x| ",uVar2), 0 < DebugLevel)) {
            printk(" %02x",*pcVar3);
          }
        }
        else if (((0 < DebugLevel) && (printk(" %02x",*pcVar3), (uVar2 & 0xf) == 0xf)) &&
                (0 < DebugLevel)) {
          printk(&_LC14);
        }
        uVar2 = uVar2 + 1;
        pcVar3 = pcVar3 + 1;
      } while (uVar2 < uVar4);
      if (param_3 < uVar4) {
        return;
      }
      pcVar3 = param_2 + bVar1 + 2;
    }
    param_3 = param_3 - uVar4;
    if (param_3 == 0) {
      return;
    }
  } while (*pcVar3 == -1);
  return;
}

