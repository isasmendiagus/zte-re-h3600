// module: mt7915.ko
// function: Set_ApCliPMFMFPC_Proc @ 0x21b87c
// size: 572 bytes
//

undefined4 Set_ApCliPMFMFPC_Proc(int *param_1,char *param_2)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  
  if (*param_2 == '\0') {
    return 0;
  }
  iVar4 = *(int *)(*param_1 + 0x3c);
  iVar1 = iVar4 * 0x2137b0;
  if (param_1 + iVar4 * 0x84dec != (int *)0xffc9209c &&
      (undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar1)) != (undefined *)0x0) {
    iVar3 = os_str_tol(param_2,0,10);
    if (iVar3 == 0) {
      *(undefined1 *)((int)param_1 + iVar1 + 0x36df65) = 0;
      *(undefined1 *)(param_1 + iVar4 * 0x84dec + 0xdb7d9) = 0;
      iVar3 = DebugLevel;
      *(undefined1 *)((int)param_1 + iVar1 + 0x36df66) = 0;
    }
    else {
      *(undefined1 *)((int)param_1 + iVar1 + 0x36df65) = 1;
      iVar3 = DebugLevel;
    }
    if (-1 < iVar3) {
      printk("[PMF]%s:: Desired MFPC=%d\n","Set_ApCliPMFMFPC_Proc",
             *(undefined1 *)((int)param_1 + iVar4 * 0x2137b0 + 0x36df65));
      iVar3 = DebugLevel;
    }
    if (((param_1[iVar4 * 0x84dec + 0xdb6e1] & 0x20c0U) == 0) ||
       ((param_1[iVar4 * 0x84dec + 0xdb733] & 0x20U) == 0)) {
      if (*(char *)((int)param_1 + iVar4 * 0x2137b0 + 0x36df65) != '\0') {
        if (iVar3 < 0) {
          return 1;
        }
        printk("[PMF]%s:: Security is not WPA2/WPA2PSK AES\n","Set_ApCliPMFMFPC_Proc");
        iVar3 = DebugLevel;
      }
    }
    else {
      cVar2 = *(char *)((int)param_1 + iVar4 * 0x2137b0 + 0x36df65);
      *(undefined1 *)(param_1 + iVar4 * 0x84dec + 0xdb7da) =
           *(undefined1 *)((int)param_1 + iVar4 * 0x2137b0 + 0x36df69);
      if (cVar2 != '\0') {
        cVar2 = *(char *)((int)param_1 + iVar4 * 0x2137b0 + 0x36df67);
        *(undefined1 *)(param_1 + iVar4 * 0x84dec + 0xdb7d9) = 1;
        if (cVar2 != '\0') {
          *(undefined1 *)(param_1 + iVar4 * 0x84dec + 0xdb7da) = 1;
        }
        *(char *)((int)param_1 + iVar4 * 0x2137b0 + 0x36df66) = cVar2;
      }
    }
    if (-1 < iVar3) {
      printk("[PMF]%s:: MFPC=%d, MFPR=%d, SHA256=%d\n","Set_ApCliPMFMFPC_Proc",
             (char)param_1[iVar4 * 0x84dec + 0xdb7d9],
             *(undefined1 *)((int)param_1 + iVar4 * 0x2137b0 + 0x36df66),
             (char)param_1[iVar4 * 0x84dec + 0xdb7da]);
    }
    return 1;
  }
  if (-1 < DebugLevel) {
    printk("[PMF]%s:: pPmfCfg=%p, wdev=%p\n","Set_ApCliPMFMFPC_Proc");
  }
  return 0;
}

