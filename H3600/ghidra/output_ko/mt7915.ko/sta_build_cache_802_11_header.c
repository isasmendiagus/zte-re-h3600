// module: mt7915.ko
// function: sta_build_cache_802_11_header @ 0x5570c
// size: 284 bytes
//

void sta_build_cache_802_11_header(int param_1,int param_2,byte *param_3,undefined4 param_4)

{
  byte bVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  
  *(undefined1 *)(param_2 + 0x2c) = 0x18;
  iVar3 = *(int *)(param_2 + 8);
  param_3[1] = param_3[1] & 0xdf | (byte)(((uint)(*(int *)(param_2 + 0x18) << 0x19) >> 0x1f) << 5);
  iVar5 = iVar3 + (*(byte *)(param_2 + 0x1c) + 8) * 2;
  param_3[0x16] = param_3[0x16] & 0xf | *(char *)(iVar5 + 4) << 4;
  param_3[0x17] = (byte)(((uint)*(ushort *)(iVar5 + 4) << 0x14) >> 0x18);
  iVar5 = iVar3 + (uint)*(byte *)(param_2 + 0x1c) * 2;
  *(ushort *)(iVar5 + 0x14) = *(short *)(iVar5 + 0x14) + 1U & 0xfff;
  if ((*(uint *)(param_1 + 0x795124) & 2) == 0) {
    puVar6 = *(undefined4 **)(param_2 + 0x24);
  }
  else {
    puVar6 = (undefined4 *)(&DAT_0057ff80 + param_1);
  }
  uVar4 = *puVar6;
  *(undefined4 *)(param_3 + 0x10) = uVar4;
  uVar2 = *(undefined2 *)(puVar6 + 1);
  *(undefined2 *)(param_3 + 0x14) = uVar2;
  uVar4 = GetStaCfgByWdev(param_1,*(undefined4 *)(iVar3 + 4),uVar4,uVar2,param_4);
  if (*(char *)(param_1 + 0x794cc6) == '\0') {
    iVar3 = RtmpPktPmBitCheck(param_1,uVar4);
    param_3[1] = param_3[1] & 0xef | (iVar3 == 1) << 4;
  }
  else {
    param_3[1] = param_3[1] | 0x10;
  }
  *(byte *)(param_2 + 0x83) = (byte)(((uint)*param_3 << 0x1c) >> 0x1e);
  bVar1 = *param_3;
  *(undefined1 *)(param_2 + 0x35) = *(undefined1 *)(param_2 + 0x2c);
  *(byte *)(param_2 + 0x84) = bVar1 >> 4;
  return;
}

