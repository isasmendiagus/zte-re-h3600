// module: mt7915.ko
// function: RTMP_MapChannelID2KHZ @ 0x141408
// size: 148 bytes
//

void RTMP_MapChannelID2KHZ(short param_1,int *param_2)

{
  int iVar1;
  undefined1 *puVar2;
  
  if (CH_HZ_ID_MAP_NUM < 1) {
    iVar1 = 0;
  }
  else {
    puVar2 = CH_HZ_ID_MAP;
    if (CH_HZ_ID_MAP._0_2_ == param_1) {
      iVar1 = 0;
    }
    else {
      iVar1 = 0;
      do {
        iVar1 = iVar1 + 1;
        if (iVar1 == CH_HZ_ID_MAP_NUM) goto LAB_00141458;
        puVar2 = (undefined1 *)((int)puVar2 + 4);
      } while (*(short *)puVar2 != param_1);
    }
    *param_2 = (uint)*(ushort *)(CH_HZ_ID_MAP + iVar1 * 4 + 2) * 1000;
  }
  if (iVar1 != CH_HZ_ID_MAP_NUM) {
    return;
  }
LAB_00141458:
  *param_2 = 0x24cde0;
  return;
}

