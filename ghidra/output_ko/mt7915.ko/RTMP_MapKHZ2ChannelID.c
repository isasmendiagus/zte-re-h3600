// module: mt7915.ko
// function: RTMP_MapKHZ2ChannelID @ 0x14149c
// size: 132 bytes
//

void RTMP_MapKHZ2ChannelID(uint param_1,uint *param_2)

{
  ushort *puVar1;
  int iVar2;
  undefined1 *puVar3;
  
  if (CH_HZ_ID_MAP_NUM < 1) {
    iVar2 = 0;
  }
  else {
    puVar3 = CH_HZ_ID_MAP;
    if ((ushort)CH_HZ_ID_MAP._2_2_ == param_1) {
      iVar2 = 0;
    }
    else {
      iVar2 = 0;
      do {
        iVar2 = iVar2 + 1;
        if (iVar2 == CH_HZ_ID_MAP_NUM) goto LAB_001414ec;
        puVar1 = (ushort *)(puVar3 + 6);
        puVar3 = puVar3 + 4;
      } while (*puVar1 != param_1);
    }
    *param_2 = (uint)*(ushort *)(CH_HZ_ID_MAP + iVar2 * 4);
  }
  if (iVar2 != CH_HZ_ID_MAP_NUM) {
    return;
  }
LAB_001414ec:
  *param_2 = 1;
  return;
}

