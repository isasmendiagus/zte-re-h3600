/* ===== FUN FUN_40e4fa9c @ 40e4fa9c =====
 * callers: 40e4fc7c:FUN_40e4fc7c
 * callees: (none)
 */


void FUN_40e4fa9c(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = DAT_40e4fb68/*=0x018a6400*/;
  puVar1 = DAT_40e4fb60/*=0x9fe00000[SERDES]*/;
  *DAT_40e4fb60/*=0x9fe00000[SERDES]*/ = DAT_40e4fb64/*=0x800010a7[GIC]*/;
  puVar1[1] = 0xf;
  puVar1[2] = 0x540;
  puVar1[3] = 4;
  puVar1[4] = 0;
  puVar1[5] = uVar2;
  puVar1[6] = DAT_40e4fb6c/*=0x08b50140*/;
  puVar1[7] = DAT_40e4fb70/*=0x01216000*/;
  puVar1[8] = 0x40000000;
  puVar1[9] = DAT_40e4fb74/*=0x0b570001*/;
  uVar2 = DAT_40e4fb78/*=0x20242000*/;
  puVar1[10] = 0;
  puVar1[0xb] = 0;
  puVar1[0xc] = uVar2;
  puVar1[0xd] = DAT_40e4fb7c/*=0xc0593d44*/;
  puVar1[0xe] = 0x42f;
  puVar1[0xf] = 0;
  puVar1[0x10] = 0x3c0000;
  puVar1[0x10] = 0x3c0040;
  puVar1[0x11] = DAT_40e4fb80/*=0xeac0a013*/;
  puVar1[0x12] = DAT_40e4fb84/*=0x101038ca*/;
  puVar1[0x13] = 0x5a000;
  iVar3 = DAT_40e4fb88/*=0x33333333*/;
  puVar1[0x14] = DAT_40e4fb88/*=0x33333333*/;
  puVar1[0x15] = iVar3;
  puVar1[0x16] = iVar3 + -0x2f510000;
  puVar1[0x17] = DAT_40e4fb8c/*=0x00040244*/;
  return;
}
