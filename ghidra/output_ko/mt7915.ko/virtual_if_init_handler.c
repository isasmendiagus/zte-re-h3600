// module: mt7915.ko
// function: virtual_if_init_handler @ 0x246454
// size: 144 bytes
//

undefined4 virtual_if_init_handler(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  iVar2 = VIRTUAL_IF_NUM();
  if (iVar2 != 0) {
    VIRTUAL_IF_INC(iVar1);
    return 0;
  }
  VIRTUAL_IF_INC(iVar1);
  *(undefined1 *)(iVar1 + 0x79540a) = 1;
  iVar2 = mt_wifi_open(*(undefined4 *)(iVar1 + 4));
  if (iVar2 == 0) {
    return 0;
  }
  VIRTUAL_IF_DEC(iVar1);
  if (DebugLevel < 3) {
    return 1;
  }
  printk("mt_wifi_open return fail!\n");
  return 1;
}

