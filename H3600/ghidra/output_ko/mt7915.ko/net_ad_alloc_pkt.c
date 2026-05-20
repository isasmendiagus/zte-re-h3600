// module: mt7915.ko
// function: net_ad_alloc_pkt @ 0x25c824
// size: 156 bytes
//

int net_ad_alloc_pkt(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    iVar1 = 0x606;
  }
  else if (*(int *)(param_2 + 4) == 0) {
    printk("%s: invalid test_pkt\n","net_ad_alloc_pkt");
    iVar1 = 0;
  }
  else {
    iVar1 = RTMPAllocateNdisPacket
                      (iVar1,param_4,0,0,*(int *)(param_2 + 4),
                       param_3 + (uint)*(byte *)(param_1 + 0x3e));
    if (iVar1 != 0) {
      printk("%s: AllocateNdisPacket fail\n","net_ad_alloc_pkt");
    }
  }
  return iVar1;
}

