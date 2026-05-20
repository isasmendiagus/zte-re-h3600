// module: mt7915.ko
// function: nonerp_sta_num @ 0x155a10
// size: 164 bytes
//

undefined2 nonerp_sta_num(int *param_1,int param_2)

{
  int iVar1;
  
  if ((*param_1 == 0x20001) && (iVar1 = param_1[0x3d], iVar1 != 0)) {
    if (((*(byte *)((int)param_1 + 0xbf) & 0xe0) == 0) && (param_1[0x3f] == 2)) {
      if (param_2 == 0) {
        *(short *)(iVar1 + 0x5064) = *(short *)(iVar1 + 0x5064) + 1;
        return *(undefined2 *)(param_1[0x3d] + 0x5064);
      }
      if (param_2 == 1) {
        if (*(short *)(iVar1 + 0x5064) == 0) {
          return 0;
        }
        *(short *)(iVar1 + 0x5064) = *(short *)(iVar1 + 0x5064) + -1;
        iVar1 = param_1[0x3d];
      }
    }
    return *(undefined2 *)(iVar1 + 0x5064);
  }
  return 0;
}

