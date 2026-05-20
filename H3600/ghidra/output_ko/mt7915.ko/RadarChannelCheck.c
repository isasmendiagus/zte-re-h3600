// module: mt7915.ko
// function: RadarChannelCheck @ 0x100b40
// size: 140 bytes
//

byte RadarChannelCheck(int param_1,uint param_2)

{
  byte *pbVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  
  iVar4 = 0;
  bVar5 = 0;
  do {
    pbVar1 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar4);
    if (pbVar1[0x49c] != 0) {
      if (*pbVar1 == param_2) {
        uVar3 = 0;
      }
      else {
        uVar3 = 0;
        pbVar2 = pbVar1;
        do {
          uVar3 = uVar3 + 1;
          if (uVar3 == pbVar1[0x49c]) goto LAB_00100ba0;
          pbVar2 = pbVar2 + 0x14;
        } while (*pbVar2 != param_2);
      }
      bVar5 = pbVar1[uVar3 * 0x14 + 5];
    }
LAB_00100ba0:
    if (iVar4 == 1) {
      return bVar5;
    }
    iVar4 = 1;
  } while( true );
}

