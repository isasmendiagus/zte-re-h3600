// module: mt7915.ko
// function: prepare_veri_pkt_head @ 0x1d5ef0
// size: 400 bytes
//

undefined4 prepare_veri_pkt_head(int param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *param_2;
  uVar2 = param_2[1];
  *(undefined4 *)(param_1 + 0xa7cc5c) = 0;
  *(undefined4 *)(param_1 + 0xa7cc60) = 0;
  *(undefined4 *)(param_1 + 0xa7cc64) = 0;
  *(undefined4 *)(param_1 + 0xa7cc68) = 0;
  *(undefined4 *)(param_1 + 0xa7cc58) = 0;
  __memzero(param_1 + 0xa7cc6c,6);
  __memzero(param_1 + 0xa7cc72,6);
  __memzero(param_1 + 0xa7cc78,6);
  __memzero(param_1 + 0xa7cc7e,0x400);
  *(uint *)(param_1 + 0xa7cc60) = uVar1;
  *(uint *)(param_1 + 0xa7cc64) = uVar2;
  *(uint *)(param_1 + 0xa7cc6c) = param_2[2];
  *(short *)(param_1 + 0xa7cc70) = (short)param_2[3];
  *(undefined4 *)(param_1 + 0xa7cc72) = *(undefined4 *)((int)param_2 + 0xe);
  *(undefined2 *)(param_1 + 0xa7cc76) = *(undefined2 *)((int)param_2 + 0x12);
  *(uint *)(param_1 + 0xa7cc78) = param_2[5];
  *(short *)(param_1 + 0xa7cc7c) = (short)param_2[6];
  if ((uVar1 & 0xfffffffd) != 0) {
    if (uVar1 == 1) {
      *(undefined4 *)(param_1 + 0xa7cc68) = 0x10;
    }
    else {
      if (uVar1 != 3) goto LAB_001d5fe0;
      *(undefined4 *)(param_1 + 0xa7cc68) = 0xc;
      *(uint *)(param_1 + 0xa7cc58) = *(uint *)(param_1 + 0xa7cc58) | 0x40;
    }
    *(undefined4 *)(param_1 + 0xa7cc5c) = 1;
    return 1;
  }
  *(undefined4 *)(param_1 + 0xa7cc68) = 0x18;
LAB_001d5fe0:
  *(undefined4 *)(param_1 + 0xa7cc5c) = 1;
  if (uVar1 == 2) {
    if ((uVar2 & 0xfffffffb) == 8) {
      uVar1 = *(uint *)(param_1 + 0xa7cc58) | 2;
      *(uint *)(param_1 + 0xa7cc58) = uVar1;
      *(int *)(param_1 + 0xa7cc68) = *(int *)(param_1 + 0xa7cc68) + 2;
    }
    else {
      uVar1 = *(uint *)(param_1 + 0xa7cc58) & 0xfffffffd;
      *(uint *)(param_1 + 0xa7cc58) = uVar1;
    }
    if ((uVar2 & 0xfffffff7) == 4) {
      *(uint *)(param_1 + 0xa7cc58) = uVar1 | 1;
      *(undefined4 *)(param_1 + 0xa7cc5c) = 2;
    }
    else {
      *(uint *)(param_1 + 0xa7cc58) = uVar1 & 0xfffffffe;
    }
    return 1;
  }
  return 1;
}

