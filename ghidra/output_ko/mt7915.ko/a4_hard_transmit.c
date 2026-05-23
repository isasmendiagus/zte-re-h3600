// module: mt7915.ko
// function: a4_hard_transmit @ 0x9f5e8
// size: 284 bytes
//

undefined4 a4_hard_transmit(int param_1,int param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 *puVar4;
  
  puVar4 = *(undefined4 **)(param_2 + 0x904);
  if (*(short *)(param_3 + 0x42) == 0) {
    if (-1 < DebugLevel) {
      printk("invalid wcid=0 in a4_hard_transmit\n");
    }
  }
  else {
    if (0xe < *(uint *)(param_3 + 100)) {
      uVar1 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
      if ((uVar1 & 0x400) == 0) {
        iVar3 = RTMPCheckEtherType(param_1,param_3,
                                   param_1 + (uint)*(byte *)(param_3 + 0x42) * 0x620 + 0x217520,
                                   param_2);
        if (iVar3 == 0) {
          if (1 < DebugLevel) {
            printk("Pkt Len/Ethernet Check Fail\n");
          }
          goto LAB_0009f61c;
        }
        UNRECOVERED_JUMPTABLE = (code *)*puVar4;
      }
      else {
        UNRECOVERED_JUMPTABLE = (code *)puVar4[1];
      }
                    /* WARNING: Could not recover jumptable at 0x0009f690. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar2 = (*UNRECOVERED_JUMPTABLE)(param_1,param_2,param_3);
      return uVar2;
    }
    if (-1 < DebugLevel) {
      printk("%s():pkt error(len: %d)\n","a4_hard_transmit");
    }
  }
LAB_0009f61c:
  RTMPFreeNdisPacket(param_1,param_3);
  return 0;
}

