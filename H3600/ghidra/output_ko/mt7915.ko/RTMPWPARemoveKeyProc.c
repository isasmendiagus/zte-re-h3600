// module: mt7915.ko
// function: RTMPWPARemoveKeyProc @ 0xdbb20
// size: 352 bytes
//

undefined4 RTMPWPARemoveKeyProc(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  void *__s1;
  undefined4 uVar3;
  
  if (2 < DebugLevel) {
    printk("---> RTMPWPARemoveKeyProc\n");
  }
  uVar2 = *(uint *)(param_2 + 4);
  if ((int)uVar2 < 0) {
    uVar3 = 2;
  }
  else {
    if ((uVar2 & 0x40000000) == 0) {
      if (2 < DebugLevel) {
        printk("RTMPWPARemoveKeyProc(KeyIdx=%ld)\n",uVar2 & 0xff);
      }
      iVar1 = param_1 + (uVar2 & 0xff) * 0x49;
      *(undefined1 *)(iVar1 + 0xa377a5) = 0;
      *(undefined1 *)(iVar1 + 0xa377a4) = 0;
      AsicRemoveSharedKeyEntry(param_1,0);
      return 0;
    }
    uVar2 = 0;
    __s1 = (void *)(param_1 + 0xa377a6);
    do {
      iVar1 = memcmp(__s1,(void *)(param_2 + 8),6);
      if (iVar1 == 0) {
        if (2 < DebugLevel) {
          printk("RTMPWPARemoveKeyProc(KeyIdx=%d)\n",uVar2);
        }
        iVar1 = param_1 + uVar2 * 0x49;
        *(undefined1 *)(iVar1 + 0xa377a5) = 0;
        *(undefined1 *)(iVar1 + 0xa377a4) = 0;
        AsicRemoveSharedKeyEntry(param_1,0,uVar2 & 0xff);
        return 0;
      }
      uVar2 = uVar2 + 1;
      __s1 = (void *)((int)__s1 + 0x49);
    } while (uVar2 != 4);
    uVar3 = 1;
  }
  return uVar3;
}

