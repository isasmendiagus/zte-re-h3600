// module: mt7915.ko
// function: RtmpOsVLANInsertTag @ 0x2449c4
// size: 232 bytes
//

int RtmpOsVLANInsertTag(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  
  bVar4 = (bool)(*(byte *)(param_1 + 0x72) & 1);
  if ((*(byte *)(param_1 + 0x72) & 1) == 0) {
    uVar2 = *(int *)(param_1 + 0xcc) - *(int *)(param_1 + 200);
    if (3 < uVar2) goto LAB_00244a18;
LAB_00244a6c:
    iVar3 = 4 - uVar2;
    if (iVar3 == 0 && bVar4 == false) goto LAB_00244a18;
  }
  else {
    uVar1 = *(uint *)(*(int *)(param_1 + 0xc4) + 0x20);
    uVar2 = *(int *)(param_1 + 0xcc) - *(int *)(param_1 + 200);
    bVar4 = (uVar1 & 0xffff) - ((int)uVar1 >> 0x10) != 1;
    if (uVar2 < 4) goto LAB_00244a6c;
    iVar3 = 0;
    if (!bVar4) goto LAB_00244a18;
  }
  iVar3 = pskb_expand_head(param_1,iVar3 + 0x1fU & 0xffffffe0,0,0x20);
  if (iVar3 < 0) {
    __dev_kfree_skb_any(param_1,1);
    return 0;
  }
LAB_00244a18:
  iVar3 = skb_push(param_1,4);
  memmove(*(void **)(param_1 + 0xcc),(void *)((int)*(void **)(param_1 + 0xcc) + 4),0xc);
  *(short *)(param_1 + 0xaa) = *(short *)(param_1 + 0xaa) + -4;
  *(undefined2 *)(iVar3 + 0xc) = 0x81;
  *(ushort *)(iVar3 + 0xe) = (ushort)((param_2 & 0xff) << 8) | (ushort)(param_2 >> 8) & 0xff;
  return param_1;
}

