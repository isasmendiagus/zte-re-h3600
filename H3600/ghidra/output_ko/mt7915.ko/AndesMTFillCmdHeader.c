// module: mt7915.ko
// function: AndesMTFillCmdHeader @ 0x1a5ba4
// size: 236 bytes
//

void AndesMTFillCmdHeader(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  byte bVar5;
  undefined1 uVar6;
  
  if (*(int *)(*(int *)(param_1 + 0x1c) + 0xa7861c) == 3) {
    uVar3 = 0x20;
  }
  else {
    uVar3 = 0xc;
  }
  puVar2 = (undefined4 *)skb_push(param_2,uVar3);
  uVar4 = *(uint *)(param_2 + 100);
  *(short *)puVar2 = (short)uVar4;
  *(undefined2 *)((int)puVar2 + 2) = *(undefined2 *)(param_1 + 0x14);
  uVar6 = *(undefined1 *)(param_1 + 2);
  *(undefined1 *)((int)puVar2 + 5) = 0xa0;
  *(undefined1 *)(puVar2 + 1) = uVar6;
  if ((*(byte *)(param_1 + 4) & 0x10) == 0) {
    bVar5 = (byte)(((uint)*(byte *)(param_1 + 4) << 0x1c) >> 0x1f);
  }
  else {
    bVar5 = 3;
  }
  *(byte *)((int)puVar2 + 6) = bVar5;
  iVar1 = DebugLevel;
  *(undefined1 *)((int)puVar2 + 7) = *(undefined1 *)(param_1 + 0x16);
  *(undefined1 *)((int)puVar2 + 9) = *(undefined1 *)(param_1 + 3);
  if (3 < iVar1) {
    printk("%s: fw_txd: 0x%x 0x%x 0x%x, Length=%d\n","AndesMTFillCmdHeader",*puVar2,puVar2[1],
           puVar2[2],uVar4 & 0xffff);
  }
  if ((*(char *)(param_1 + 2) == -0x13) && ((*(byte *)(param_1 + 4) & 0x11) == 1)) {
    uVar6 = 1;
  }
  else {
    uVar6 = 0;
  }
  *(undefined1 *)((int)puVar2 + 0xb) = uVar6;
  return;
}

