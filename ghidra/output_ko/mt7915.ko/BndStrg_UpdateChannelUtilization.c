// module: mt7915.ko
// function: BndStrg_UpdateChannelUtilization @ 0x9e5a8
// size: 356 bytes
//

void BndStrg_UpdateChannelUtilization(int param_1)

{
  uint uVar1;
  uint uVar2;
  byte *pbVar3;
  char *pcVar4;
  undefined1 local_60 [44];
  uint local_34;
  
  pcVar4 = &DAT_0036b928 + param_1;
  pbVar3 = &DAT_0036c949 + param_1;
  do {
    if ((*pcVar4 != '\0') && (pcVar4[1] != '\0')) {
      if (pbVar3[0x49] == 1) {
        if (pbVar3[-4] != 0) {
          uVar1 = *(uint *)(pcVar4 + 0xc) & 0x40;
          goto joined_r0x0009e704;
        }
      }
      else if (pbVar3[-5] != 0) {
        uVar1 = *(uint *)(pcVar4 + 0xc) & 0x80;
joined_r0x0009e704:
        if (uVar1 != 0) {
          uVar1 = ZTE_Get_ChannelUtilization(param_1);
          if (uVar1 < *pbVar3) {
            *(undefined4 *)(param_1 + 0xa7d160) = 0;
            uVar2 = *(int *)(param_1 + 0xa7d15c) + 1;
            *(uint *)(param_1 + 0xa7d15c) = uVar2;
            if (*(uint *)(pbVar3 + 99) <= uVar2) {
              *(undefined4 *)(param_1 + 0xa7d15c) = 0;
              if (pbVar3[0x49] == 1) goto LAB_0009e664;
LAB_0009e6a0:
              pbVar3[0x67] = (byte)uVar1;
              local_60[0] = 0x1a;
LAB_0009e6ac:
              local_34 = uVar1;
              RtmpOSWrielessEventSend(*(undefined4 *)(pcVar4 + -4),1,0x950,0,local_60,0x40);
            }
          }
          else {
            *(undefined4 *)(param_1 + 0xa7d15c) = 0;
            uVar2 = *(int *)(param_1 + 0xa7d160) + 1;
            *(uint *)(param_1 + 0xa7d160) = uVar2;
            if (*(uint *)(pbVar3 + 99) <= uVar2) {
              *(undefined4 *)(param_1 + 0xa7d160) = 0;
              if (pbVar3[0x49] != 1) goto LAB_0009e6a0;
LAB_0009e664:
              pbVar3[0x68] = (byte)uVar1;
              local_60[0] = 0x1b;
              goto LAB_0009e6ac;
            }
          }
        }
      }
    }
    pbVar3 = pbVar3 + 0x1094;
    pcVar4 = pcVar4 + 0x1094;
    if (pbVar3 == (byte *)(param_1 + 0x36ea71)) {
      return;
    }
  } while( true );
}

