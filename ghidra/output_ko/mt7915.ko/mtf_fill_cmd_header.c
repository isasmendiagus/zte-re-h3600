// module: mt7915.ko
// function: mtf_fill_cmd_header @ 0x1a0ec8
// size: 404 bytes
//

void mtf_fill_cmd_header(int param_1,short *param_2,int param_3)

{
  short sVar1;
  short *psVar2;
  uint *puVar3;
  byte bVar4;
  undefined1 uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  
  if (*(int *)(param_1 + 0xa7861c) != 2) {
    psVar2 = (short *)skb_push(param_3,0x20);
    puVar3 = (uint *)skb_push(param_3,0x20);
    __memzero(puVar3,0x20);
    uVar6 = *puVar3 | *(uint *)(param_3 + 100);
    *puVar3 = uVar6 | 0x40000000;
    uVar7 = uVar6 | 0x41000000;
    if ((char)param_2[1] == -0x12) {
      uVar7 = uVar6 | 0x41800000;
    }
    *puVar3 = uVar7;
    puVar3[1] = puVar3[1] | 0x80010000;
    __memzero(psVar2,0x20);
    *psVar2 = (short)*(undefined4 *)(param_3 + 100) + -0x20;
    psVar2[1] = param_2[10];
    sVar1 = param_2[1];
    *(undefined1 *)((int)psVar2 + 5) = 0xa0;
    *(char *)(psVar2 + 2) = (char)sVar1;
    if ((*(byte *)(param_2 + 2) & 0x10) == 0) {
      bVar4 = (byte)(((uint)*(byte *)(param_2 + 2) << 0x1c) >> 0x1f);
    }
    else {
      bVar4 = 3;
    }
    *(byte *)(psVar2 + 3) = bVar4;
    iVar8 = DebugLevel;
    *(char *)((int)psVar2 + 7) = (char)param_2[0xb];
    *(undefined1 *)((int)psVar2 + 9) = *(undefined1 *)((int)param_2 + 3);
    if (3 < iVar8) {
      pcVar9 = "HOST2CR4";
      if (*param_2 == 0) {
        pcVar9 = "HOST2N9";
      }
      printk("%s: mcu_dest(%d):%s\n","mtf_fill_cmd_header",*param_2,pcVar9);
      iVar8 = DebugLevel;
    }
    uVar5 = 0;
    if (*param_2 != 0) {
      uVar5 = 2;
    }
    *(undefined1 *)(psVar2 + 5) = uVar5;
    if (3 < iVar8) {
      printk("%s: fw_txd: 0x%x 0x%x 0x%x, Length=%d\n","mtf_fill_cmd_header",*(undefined4 *)psVar2,
             *(undefined4 *)(psVar2 + 2),*(undefined4 *)(psVar2 + 4),*psVar2);
    }
    if (((char)param_2[1] == -0x13) && ((*(byte *)(param_2 + 2) & 0x11) == 1)) {
      uVar5 = 1;
    }
    else {
      uVar5 = 0;
    }
    *(undefined1 *)((int)psVar2 + 0xb) = uVar5;
    return;
  }
  return;
}

