// module: mt7915.ko
// function: bcn_buf_init @ 0xb3348
// size: 228 bytes
//

int bcn_buf_init(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined1 uVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  *(int *)(param_2 + 0x948) = param_2;
  *(undefined1 *)(param_2 + 0x95a) = 0;
  *(undefined4 *)(param_2 + 0x984) = 0;
  if (*(int *)(param_2 + 0x954) == 0) {
    iVar4 = RTMPAllocateNdisPacket(param_1,param_2 + 0x954,0,0,0,0x59c);
    if (iVar4 == 1) {
      return 1;
    }
  }
  else if (0 < DebugLevel) {
    printk("%s():BcnPkt is allocated!, bcn offload=%d\n","bcn_buf_init",
           *(undefined1 *)(iVar1 + 0x14d));
  }
  iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar2 != 2) {
    return iVar4;
  }
  *(undefined4 *)(param_2 + 0x94c) = 1;
  if (*(char *)(iVar1 + 0x14d) == '\x01') {
    uVar3 = 2;
  }
  else {
    uVar3 = 1;
  }
  *(undefined1 *)(param_2 + 0x988) = uVar3;
  return iVar4;
}

