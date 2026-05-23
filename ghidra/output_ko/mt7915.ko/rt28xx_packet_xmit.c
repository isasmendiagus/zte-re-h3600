// module: mt7915.ko
// function: rt28xx_packet_xmit @ 0x246694
// size: 156 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void rt28xx_packet_xmit(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_14;
  
  uVar2 = *(undefined4 *)(param_1 + 0x18);
  local_14 = param_1;
  iVar1 = RtmpOsGetNetDevWdev(uVar2);
  if (iVar1 == 0) {
    printk(&_LC15,0x2b9);
    dump_stack();
  }
  if (_netif_device_detach != (code *)0x0) {
    (*_netif_device_detach)(param_1,2,"MT7915_Tx");
  }
  dev_mirror(uVar2,param_1,0);
  RTMPSendPackets(iVar1,&local_14,1,*(undefined4 *)(param_1 + 100),RtmpNetEthConvertDevSearch);
  return;
}

