// module: mt7915.ko
// function: announce_802_3_packet @ 0x14fb48
// size: 368 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void announce_802_3_packet(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  char cVar4;
  
  uVar3 = *(undefined4 *)(param_1 + 0xa1904);
  if (param_1 == 0) {
    printk(&_LC47,0x465);
    dump_stack();
  }
  if (param_2 == 0) {
    printk(&_LC48,0x466);
    dump_stack();
  }
  g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + -1;
  if (_netif_device_detach != (code *)0x0) {
    (*_netif_device_detach)(param_2,3,"MT7915_Rx");
  }
  skb_pull(param_2,0xe);
  uVar1 = RtmpOsPktNetDevGet(param_2);
  dev_mirror(uVar1,param_2,1);
  skb_push(param_2,0xe);
  HintPreloadData(*(undefined4 *)(param_2 + 0xcc));
  cVar4 = *(char *)(param_1 + 0x286285);
  if (cVar4 == '\x01') {
    uVar1 = RtmpOsPktNetDevGet(param_2);
    iVar2 = MATPktRxNeedConvert(param_1,uVar1);
    if (iVar2 != 0) {
      MATEngineRxHandle(param_1,param_2,0);
    }
    cVar4 = *(char *)(param_1 + 0x286285);
  }
  if (cVar4 == '\0') {
    uVar1 = RtmpOsPktNetDevGet(param_2);
    iVar2 = MATPktRxNeedConvert(param_1,uVar1);
    if ((iVar2 != 0) && ((*(byte *)(param_1 + 0xa77bcf) & 1) != 0)) {
      MATEngineRxHandle(param_1,param_2,0);
    }
  }
  RtmpOsPktRcvHandle(param_2,uVar3);
  return;
}

