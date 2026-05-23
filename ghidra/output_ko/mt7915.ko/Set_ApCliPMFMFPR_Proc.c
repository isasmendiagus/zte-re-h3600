// module: mt7915.ko
// function: Set_ApCliPMFMFPR_Proc @ 0x21babc
// size: 568 bytes
//

undefined4 Set_ApCliPMFMFPR_Proc(int *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (*param_2 == '\0') {
    return 0;
  }
  iVar4 = *(int *)(*param_1 + 0x3c);
  iVar3 = iVar4 * 0x2137b0;
  if (param_1 + iVar4 * 0x84dec != (int *)0xffc9209c &&
      (undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar3)) != (undefined *)0x0) {
    iVar2 = os_str_tol(param_2,0,10);
    if (iVar2 == 0) {
      *(undefined1 *)((int)param_1 + iVar3 + 0x36df67) = 0;
      *(undefined1 *)((int)param_1 + iVar3 + 0x36df66) = 0;
    }
    else {
      *(undefined1 *)((int)param_1 + iVar3 + 0x36df67) = 1;
    }
    if (-1 < DebugLevel) {
      printk("[PMF]%s:: Desired MFPR=%d\n","Set_ApCliPMFMFPR_Proc",
             *(undefined1 *)((int)param_1 + iVar4 * 0x2137b0 + 0x36df67));
    }
    iVar3 = DebugLevel;
    if (((param_1[iVar4 * 0x84dec + 0xdb6e1] & 0x20c0U) == 0) ||
       ((param_1[iVar4 * 0x84dec + 0xdb733] & 0x20U) == 0)) {
      if (*(char *)((int)param_1 + iVar4 * 0x2137b0 + 0x36df65) != '\0') {
        if (DebugLevel < 0) {
          return 1;
        }
        printk("[PMF]%s:: Security is not WPA2/WPA2PSK AES\n","Set_ApCliPMFMFPR_Proc");
        iVar3 = DebugLevel;
      }
    }
    else {
      cVar1 = *(char *)((int)param_1 + iVar4 * 0x2137b0 + 0x36df65);
      *(undefined1 *)(param_1 + iVar4 * 0x84dec + 0xdb7da) =
           *(undefined1 *)((int)param_1 + iVar4 * 0x2137b0 + 0x36df69);
      if (cVar1 != '\0') {
        cVar1 = *(char *)((int)param_1 + iVar4 * 0x2137b0 + 0x36df67);
        *(undefined1 *)(param_1 + iVar4 * 0x84dec + 0xdb7d9) = 1;
        if (cVar1 != '\0') {
          *(undefined1 *)(param_1 + iVar4 * 0x84dec + 0xdb7da) = 1;
        }
        *(char *)((int)param_1 + iVar4 * 0x2137b0 + 0x36df66) = cVar1;
      }
    }
    if (-1 < iVar3) {
      printk("[PMF]%s:: MFPC=%d, MFPR=%d, SHA256=%d\n","Set_ApCliPMFMFPR_Proc",
             (char)param_1[iVar4 * 0x84dec + 0xdb7d9],
             *(undefined1 *)((int)param_1 + iVar4 * 0x2137b0 + 0x36df66),
             (char)param_1[iVar4 * 0x84dec + 0xdb7da]);
    }
    return 1;
  }
  if (-1 < DebugLevel) {
    printk("[PMF]%s:: pPmfCfg=%p, wdev=%p\n","Set_ApCliPMFMFPR_Proc");
  }
  return 0;
}

