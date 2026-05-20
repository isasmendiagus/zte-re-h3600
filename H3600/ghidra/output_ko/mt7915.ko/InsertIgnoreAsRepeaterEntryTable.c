// module: mt7915.ko
// function: InsertIgnoreAsRepeaterEntryTable @ 0x82860
// size: 448 bytes
//

void InsertIgnoreAsRepeaterEntryTable(int param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  undefined4 *__s1;
  
  if ((0x1f < (byte)(&DAT_003686a0)[param_1]) ||
     (iVar8 = memcmp(param_2,&ZERO_MAC_ADDR,6), iVar8 == 0)) {
    return;
  }
  iVar8 = 0;
  _raw_spin_lock_bh(&DAT_00367914 + param_1);
  puVar7 = (undefined4 *)(&DAT_00368120 + param_1);
  do {
    __s1 = puVar7;
    iVar9 = memcmp(__s1,param_2,6);
    if (iVar9 == 0) {
      iVar9 = iVar8 * 2;
      if ((&DAT_00368127)[param_1 + iVar8 * 0xc] != '\0') goto LAB_000829b4;
LAB_000828fc:
      iVar9 = param_1 + (iVar9 + iVar8) * 4;
      *__s1 = *(undefined4 *)param_2;
      *(undefined2 *)(__s1 + 1) = *(undefined2 *)(param_2 + 4);
      (&DAT_00368126)[iVar9] = (char)iVar8;
      (&DAT_00368127)[iVar9] = 1;
      break;
    }
    if (*(char *)((int)__s1 + 7) == '\0') {
      iVar9 = iVar8 << 1;
      goto LAB_000828fc;
    }
    iVar8 = iVar8 + 1;
    puVar7 = __s1 + 3;
  } while (iVar8 != 0x20);
  if (__s1 != (undefined4 *)0x0) {
    bVar1 = param_2[1];
    bVar2 = *param_2;
    bVar3 = param_2[2];
    bVar4 = param_2[3];
    bVar5 = param_2[4];
    bVar6 = param_2[5];
    __s1[2] = 0;
    iVar9 = param_1 + (uint)(byte)(bVar2 ^ bVar1 ^ bVar3 ^ bVar4 ^ bVar5 ^ bVar6) * 4;
    iVar8 = *(int *)(&DAT_003682a0 + iVar9);
    if (*(int *)(&DAT_003682a0 + iVar9) == 0) {
      *(undefined4 **)(&DAT_003682a0 + iVar9) = __s1;
    }
    else {
      do {
        iVar9 = iVar8;
        iVar8 = *(int *)(iVar9 + 8);
      } while (iVar8 != 0);
      *(undefined4 **)(iVar9 + 8) = __s1;
    }
  }
  if (-1 < DebugLevel) {
    printk(" Store Invaild MacAddr = %02x:%02x:%02x:%02x:%02x:%02x. !!!\n",*(undefined1 *)__s1,
           *(undefined *)((int)__s1 + 1),*(undefined *)((int)__s1 + 2),*(undefined *)((int)__s1 + 3)
           ,*(undefined1 *)(__s1 + 1),*(undefined *)((int)__s1 + 5));
  }
  (&DAT_003686a0)[param_1] = (&DAT_003686a0)[param_1] + '\x01';
LAB_000829b4:
  _raw_spin_unlock_bh(&DAT_00367914 + param_1);
  return;
}

