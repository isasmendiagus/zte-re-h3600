// module: mt7915.ko
// function: APPMFInit @ 0x17f9c
// size: 396 bytes
//

void APPMFInit(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  
  uVar3 = *(uint *)(param_2 + 0x2c);
  *(undefined1 *)(param_2 + 0x40c) = 0;
  *(undefined1 *)(param_2 + 0x40e) = 0;
  *(undefined1 *)(param_2 + 0x410) = 0;
  iVar2 = DebugLevel;
  if ((uVar3 & 0x2000) == 0) {
    if ((uVar3 & 0x810000) != 0) {
      *(undefined1 *)(param_2 + 0x40c) = 1;
      iVar2 = DebugLevel;
      *(undefined1 *)(param_2 + 0x40e) = 1;
      goto LAB_00017fe4;
    }
    if ((((uVar3 & 0xc0) != 0) && ((*(uint *)(param_2 + 0x174) & 0x20) != 0)) &&
       ((*(uint *)(param_2 + 0x254) & 0x20) != 0)) {
      if (*(char *)(param_2 + 0x40d) == '\0') goto LAB_000180b8;
      *(undefined1 *)(param_2 + 0x40c) = 1;
      *(char *)(param_2 + 0x40e) = *(char *)(param_2 + 0x40f);
      iVar2 = DebugLevel;
      if (*(char *)(param_2 + 0x40f) != '\0' || *(char *)(param_2 + 0x411) != '\0') {
        *(undefined1 *)(param_2 + 0x410) = 1;
        iVar2 = DebugLevel;
      }
      goto LAB_00017fe4;
    }
    if ((*(char *)(param_2 + 0x40d) == '\0') || (DebugLevel < 2)) {
LAB_000180b8:
      cVar4 = '\0';
      goto LAB_0001800c;
    }
    printk("[PMF]%s:: Security is not WPA2/WPA2PSK AES\n","APPMFInit");
    cVar4 = *(char *)(param_2 + 0x40c);
    iVar2 = DebugLevel;
    if (cVar4 == '\0') goto LAB_0001800c;
    uVar3 = *(uint *)(param_2 + 0x2c);
  }
  else {
    *(byte *)(param_2 + 0x40e) = (byte)((byte)uVar3 ^ 0x80) >> 7;
    *(undefined1 *)(param_2 + 0x40c) = 1;
LAB_00017fe4:
    cVar4 = '\x01';
  }
  if ((uVar3 & 0x10000) == 0) {
    *(undefined1 *)(param_2 + 0x413) = 0;
    uVar1 = 2;
  }
  else {
    uVar1 = 0x10;
    *(undefined1 *)(param_2 + 0x413) = 0;
  }
  *(undefined1 *)(param_2 + 0x415) = 0;
  *(undefined1 *)(param_2 + 0x416) = 0;
  *(undefined1 *)(param_2 + 0x414) = uVar1;
LAB_0001800c:
  if (2 < iVar2) {
    printk("[PMF]%s:: apidx=%d, MFPC=%d, MFPR=%d, SHA256=%d\n","APPMFInit",
           *(undefined1 *)(param_2 + 0xe),cVar4,*(undefined1 *)(param_2 + 0x40e),
           *(undefined1 *)(param_2 + 0x410));
  }
  return;
}

