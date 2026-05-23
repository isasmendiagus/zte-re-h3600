// module: mt7915.ko
// function: RTMPToWirelessSta @ 0x119724
// size: 196 bytes
//

void RTMPToWirelessSta(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4,
                      undefined4 param_5,undefined4 param_6,char param_7)

{
  undefined1 uVar1;
  int iVar2;
  int local_14;
  
  if (((param_2 != (int *)0x0) && (*param_2 == 2 || (*param_2 - 0x20001U & 0xfffdffff) == 0)) &&
     (iVar2 = RTMPAllocateNdisPacket(param_1,&local_14,param_3,param_4,param_5,param_6), iVar2 == 0)
     ) {
    *(bool *)(local_14 + 0x2e) = param_7 != '\0';
    *(short *)(local_14 + 0x42) = (short)param_2[0x38];
    if (param_2[2] != 0) {
      uVar1 = *(undefined1 *)(param_2[2] + 0xc);
      *(undefined1 *)(local_14 + 0x2f) = 0;
      *(undefined1 *)(local_14 + 0x2d) = uVar1;
      send_data_pkt(param_1,param_2[2],local_14);
      return;
    }
    RTMPFreeNdisPacket(param_1);
  }
  return;
}

