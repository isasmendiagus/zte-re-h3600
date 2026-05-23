// module: mt7915.ko
// function: EventRxvReport @ 0x1a8a54
// size: 912 bytes
//

void EventRxvReport(undefined4 param_1,int param_2)

{
  if (DebugLevel < 1) {
    return;
  }
  printk("====================================================================================\n");
  if (DebugLevel < 1) {
LAB_001a8ae4:
    if (0 < DebugLevel) {
      printk("PostRssiRu        = %d\n",*(undefined2 *)(param_2 + 6));
      if (DebugLevel < 1) {
        return;
      }
      printk("RxCeLtfSnr        = %d\n",*(undefined1 *)(param_2 + 8));
      goto LAB_001a8b24;
    }
LAB_001a8b64:
    if (0 < DebugLevel) {
      printk("PostNoiseFloorRx1 = %d\n",*(undefined1 *)(param_2 + 0x11));
      if (DebugLevel < 1) {
        return;
      }
      printk("PostNoiseFloorRx2 = %d\n",*(undefined1 *)(param_2 + 0x12));
      goto LAB_001a8ba4;
    }
LAB_001a8be4:
    if (0 < DebugLevel) {
      printk("UserRate          = %d\n",*(undefined1 *)(param_2 + 0x15));
      if (DebugLevel < 1) {
        return;
      }
      printk("UserStreamNum     = %d\n",*(undefined1 *)(param_2 + 0x16));
      goto LAB_001a8c24;
    }
LAB_001a8c64:
    if (0 < DebugLevel) {
      printk("RxFcsErr          = %d\n",*(undefined1 *)(param_2 + 0x1a));
      if (DebugLevel < 1) {
        return;
      }
      printk("OfdmRu26Snr0    = %d\n",*(undefined4 *)(param_2 + 0x1c));
      goto LAB_001a8ca4;
    }
LAB_001a8ce4:
    if (0 < DebugLevel) {
      printk("OfdmRu26Snr3    = %d\n",*(undefined4 *)(param_2 + 0x28));
      if (DebugLevel < 1) {
        return;
      }
      printk("OfdmRu26Snr4    = %d\n",*(undefined4 *)(param_2 + 0x2c));
      goto LAB_001a8d24;
    }
  }
  else {
    printk("RXV Report                                   \n");
    if (DebugLevel < 1) {
      return;
    }
    printk("====================================================================================\n")
    ;
    if (0 < DebugLevel) {
      printk("RxvCallBackType   = %d\n",*(undefined1 *)(param_2 + 2));
      if (DebugLevel < 1) {
        return;
      }
      printk("PostMd            = %d\n",*(undefined2 *)(param_2 + 4));
      goto LAB_001a8ae4;
    }
LAB_001a8b24:
    if (0 < DebugLevel) {
      printk("TftFoe            = %d\n",*(undefined4 *)(param_2 + 0xc));
      if (DebugLevel < 1) {
        return;
      }
      printk("PostNoiseFloorRx0 = %d\n",*(undefined1 *)(param_2 + 0x10));
      goto LAB_001a8b64;
    }
LAB_001a8ba4:
    if (0 < DebugLevel) {
      printk("PostNoiseFloorRx3 = %d\n",*(undefined1 *)(param_2 + 0x13));
      if (DebugLevel < 1) {
        return;
      }
      printk("DecUserNum        = %d\n",*(undefined1 *)(param_2 + 0x14));
      goto LAB_001a8be4;
    }
LAB_001a8c24:
    if (0 < DebugLevel) {
      printk("UserRuAlloc       = %d\n",*(undefined1 *)(param_2 + 0x17));
      if (DebugLevel < 1) {
        return;
      }
      printk("MuAid             = %d\n",*(undefined2 *)(param_2 + 0x18));
      goto LAB_001a8c64;
    }
LAB_001a8ca4:
    if (0 < DebugLevel) {
      printk("OfdmRu26Snr1    = %d\n",*(undefined4 *)(param_2 + 0x20));
      if (DebugLevel < 1) {
        return;
      }
      printk("OfdmRu26Snr2    = %d\n",*(undefined4 *)(param_2 + 0x24));
      goto LAB_001a8ce4;
    }
LAB_001a8d24:
    if (DebugLevel < 1) goto LAB_001a8da4;
    printk("OfdmRu26Snr5    = %d\n",*(undefined4 *)(param_2 + 0x30));
    if (DebugLevel < 1) {
      return;
    }
    printk("OfdmRu26Snr6    = %d\n",*(undefined4 *)(param_2 + 0x34));
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("OfdmRu26Snr7    = %d\n",*(undefined4 *)(param_2 + 0x38));
  if (DebugLevel < 1) {
    return;
  }
  printk("OfdmRu26Snr8    = %d\n",*(undefined4 *)(param_2 + 0x3c));
LAB_001a8da4:
  if (DebugLevel < 1) {
    return;
  }
  printk("OfdmRu26Snr9    = %d\n",*(undefined4 *)(param_2 + 0x40));
  if (DebugLevel < 1) {
    return;
  }
  printk("====================================================================================\n");
  return;
}

