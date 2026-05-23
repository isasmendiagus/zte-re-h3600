// module: mt7915.ko
// function: amsdu_history_exec @ 0xd1ed0
// size: 248 bytes
//

int amsdu_history_exec(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  bool bVar5;
  
  piVar4 = (int *)(param_2 + 0x2f6a0);
  uVar3 = 0;
  while( true ) {
    uVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_2 + 0xa797a0));
    bVar5 = 0x11f < uVar3;
    if (uVar3 != 0x120) {
      bVar5 = uVar1 <= uVar3;
    }
    if (bVar5) break;
    if (*piVar4 != 0) {
      iVar2 = param_2 + (*(int *)(param_2 + 0x285c14) + uVar3 * 0x188) * 4;
      *(int *)(iVar2 + 0x2fb5c) = piVar4[0x12e];
      piVar4[0x12e] = 0;
      *(int *)(iVar2 + 0x2fb88) = piVar4[0x139];
      piVar4[0x139] = 0;
      *(int *)(iVar2 + 0x2fbb4) = piVar4[0x144];
      piVar4[0x144] = 0;
      *(int *)(iVar2 + 0x2fbe0) = piVar4[0x14f];
      piVar4[0x14f] = 0;
      *(int *)(iVar2 + 0x2fc0c) = piVar4[0x15a];
      piVar4[0x15a] = 0;
      *(int *)(iVar2 + 0x2fc38) = piVar4[0x165];
      piVar4[0x165] = 0;
      *(int *)(iVar2 + 0x2fc64) = piVar4[0x170];
      piVar4[0x170] = 0;
      *(int *)(iVar2 + 0x2fc90) = piVar4[0x17b];
      piVar4[0x17b] = 0;
    }
    piVar4 = piVar4 + 0x188;
    uVar3 = uVar3 + 1;
  }
  uVar3 = *(int *)(param_2 + 0x285c14) + 1;
  *(uint *)(param_2 + 0x285c14) = uVar3 % 10;
  return uVar3 * -0x33333333;
}

