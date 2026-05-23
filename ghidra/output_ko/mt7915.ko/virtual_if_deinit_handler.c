// module: mt7915.ko
// function: virtual_if_deinit_handler @ 0x24629c
// size: 60 bytes
//

undefined4 virtual_if_deinit_handler(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  iVar2 = VIRTUAL_IF_NUM();
  if (iVar2 != 0) {
    return 0;
  }
  mt_wifi_close(*(undefined4 *)(iVar1 + 4));
  return 0;
}

