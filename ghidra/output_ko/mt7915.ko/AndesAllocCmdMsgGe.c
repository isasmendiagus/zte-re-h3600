// module: mt7915.ko
// function: AndesAllocCmdMsgGe @ 0x1a4064
// size: 284 bytes
//

int AndesAllocCmdMsgGe(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int local_1c;
  
  local_1c = 0;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar3 = RTMP_AllocateFragPacketBuffer
                    (param_1,(uint)*(byte *)(iVar2 + 0x125) + (uint)*(byte *)(iVar2 + 0x124) +
                             param_2);
  if (iVar3 == 0) {
    iVar2 = 0;
    if (-1 < DebugLevel) {
      printk("can not allocate net_pkt\n");
    }
  }
  else {
    bVar1 = *(byte *)(iVar2 + 0x124);
    *(uint *)(iVar3 + 0xcc) = *(int *)(iVar3 + 0xcc) + (uint)bVar1;
    *(uint *)(iVar3 + 0xc0) = *(int *)(iVar3 + 0xc0) + (uint)bVar1;
    os_alloc_mem(0,&local_1c,100);
    iVar2 = local_1c;
    if (local_1c == 0) {
      if (-1 < DebugLevel) {
        printk("can not allocate cmd msg\n");
      }
      RTMPFreeNdisPacket(param_1,iVar3);
    }
    else {
      *(int *)(iVar3 + 0x20) = local_1c;
      os_zero_mem(local_1c,100);
      *(int *)(local_1c + 0x1c) = param_1;
      *(int *)(local_1c + 0x20) = iVar3;
      *(int *)(param_1 + 0xa78510) = *(int *)(param_1 + 0xa78510) + 1;
      iVar2 = local_1c;
    }
  }
  return iVar2;
}

