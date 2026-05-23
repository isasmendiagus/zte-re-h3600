// module: mt7915.ko
// function: RepeaterRemoveIngoreEntry @ 0x82a20
// size: 360 bytes
//

undefined4 RepeaterRemoveIngoreEntry(int param_1,int param_2,byte *param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  undefined *puVar4;
  
  _raw_spin_lock_bh(&DAT_00367914 + param_1);
  puVar4 = &DAT_00368120 + param_1 + param_2 * 0xc;
  if ((puVar4 == (undefined *)0x0) || ((&DAT_00368127)[param_1 + param_2 * 0xc] == '\0'))
  goto LAB_00082b14;
  iVar3 = param_1 + (uint)(byte)(param_3[5] ^
                                param_3[3] ^ param_3[1] ^ *param_3 ^ param_3[2] ^ param_3[4]) * 4;
  puVar2 = *(undefined **)(&DAT_003682a0 + iVar3);
  if (puVar2 == (undefined *)0x0) {
    printk(&_LC57,0x58e);
    dump_stack();
LAB_00082b58:
    printk(&_LC61,0x5a2);
    dump_stack();
  }
  else {
    if (puVar4 != puVar2) {
      for (puVar1 = *(undefined **)(puVar2 + 8); puVar1 != (undefined *)0x0;
          puVar1 = *(undefined **)(puVar1 + 8)) {
        if (puVar1 == puVar4) {
          if (puVar2 == (undefined *)0x0) goto LAB_00082b70;
          *(undefined4 *)(puVar2 + 8) = *(undefined4 *)(&DAT_00368128 + param_1 + param_2 * 0xc);
          goto LAB_00082b04;
        }
        puVar2 = puVar1;
      }
      goto LAB_00082b58;
    }
LAB_00082b70:
    *(undefined4 *)(&DAT_003682a0 + iVar3) =
         *(undefined4 *)(&DAT_00368128 + param_1 + param_2 * 0xc);
  }
LAB_00082b04:
  (&DAT_003686a0)[param_1] = (&DAT_003686a0)[param_1] + -1;
LAB_00082b14:
  __memzero(puVar4,6);
  (&DAT_00368127)[param_1 + param_2 * 0xc] = 0;
  _raw_spin_unlock_bh(&DAT_00367914 + param_1);
  return 1;
}

