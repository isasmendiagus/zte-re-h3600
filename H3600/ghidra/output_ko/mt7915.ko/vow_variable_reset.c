// module: mt7915.ko
// function: vow_variable_reset @ 0x42e30
// size: 880 bytes
//

void vow_variable_reset(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined2 *puVar5;
  undefined2 *puVar6;
  uint uVar7;
  uint uVar8;
  
  iVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  *(undefined1 *)(param_1 + 0xa7a2e8) = 0;
  uVar8 = 0;
  *(undefined1 *)(param_1 + 0xa7a2ee) = 5;
  *(undefined1 *)(param_1 + 0xa7a2e9) = 1;
  *(undefined1 *)(param_1 + 0xa7a2ea) = 1;
  *(undefined1 *)(param_1 + 0xa7a2eb) = 1;
  *(undefined1 *)(param_1 + 0xa7a2ec) = 1;
  *(undefined1 *)(param_1 + 0xa7a2ed) = 1;
  *(undefined2 *)(param_1 + 0xa7a2f0) = 0xffff;
  *(undefined1 *)(param_1 + 0xa7a2f2) = 0x40;
  *(undefined1 *)(param_1 + 0xa7a2f3) = 0x40;
  *(undefined2 *)(param_1 + 0xa7a320) = 0x1e;
  puVar5 = (undefined2 *)(param_1 + 0xa79828);
  do {
    uVar7 = uVar8 & 0xff;
    *(undefined1 *)(puVar5 + 6) = 0x10;
    *(undefined1 *)((int)puVar5 + 0xd) = 0x10;
    *(undefined1 *)(puVar5 + 7) = 0x10;
    *(undefined1 *)((int)puVar5 + 0xf) = 0x10;
    uVar8 = uVar8 + 1;
    puVar5[3] = 1000;
    puVar5[4] = 1000;
    puVar5[5] = 1000;
    *puVar5 = 10;
    puVar5[1] = 0x1e;
    *(undefined1 *)(puVar5 + 2) = 5;
    *(undefined1 *)((int)puVar5 + 5) = 10;
    uVar1 = vow_convert_rate_token(param_1,0,uVar7);
    puVar5[8] = uVar1;
    uVar1 = vow_convert_rate_token(param_1,1,uVar7);
    puVar5[9] = uVar1;
    uVar1 = vow_convert_airtime_token(param_1,0,uVar7);
    puVar5[10] = uVar1;
    uVar1 = vow_convert_airtime_token(param_1,1,uVar7);
    *(undefined1 *)((int)puVar5 + 0x19) = 0;
    *(undefined1 *)(puVar5 + 0xd) = 1;
    puVar5[0xb] = uVar1;
    puVar5 = puVar5 + 0xe;
  } while (uVar8 != 0x10);
  if (iVar2 != 0) {
    puVar3 = (undefined1 *)(param_1 + 0xa799e8);
    do {
      *puVar3 = 2;
      puVar4 = puVar3 + 8;
      puVar3[1] = 2;
      puVar3[2] = 1;
      puVar3[3] = 0;
      puVar3[4] = 0;
      puVar3[5] = 0;
      puVar3[6] = 0;
      puVar3[7] = 0;
      puVar3 = puVar4;
    } while (puVar4 != (undefined1 *)(param_1 + (iVar2 + 0x14f33d) * 8));
  }
  puVar3 = (undefined1 *)(param_1 + 0xa797df);
  *(undefined1 *)(param_1 + 0xa7a2f4) = 6;
  *(undefined1 *)(param_1 + 0xa7a2f5) = 0xc;
  *(undefined1 *)(param_1 + 0xa7a2f6) = 0x10;
  *(undefined1 *)(param_1 + 0xa7a2f7) = 0x14;
  *(undefined1 *)(param_1 + 0xa7a2f8) = 0x18;
  *(undefined1 *)(param_1 + 0xa7a2f9) = 0x1c;
  *(undefined1 *)(param_1 + 0xa7a2fa) = 0x20;
  *(undefined1 *)(param_1 + 0xa7a2fb) = 0x24;
  *(undefined1 *)(param_1 + 0xa79826) = 1;
  *(undefined2 *)(param_1 + 0xa797de) = 0x142;
  *(undefined2 *)(param_1 + 0xa79814) = 0x142;
  *(undefined1 *)(param_1 + 0xa797dc) = 4;
  puVar5 = (undefined2 *)(param_1 + 0xa797e4);
  do {
    *puVar5 = 0x166;
    puVar6 = puVar5 + 4;
    puVar5[1] = 0x142;
    puVar5[2] = 0xa9;
    puVar5[3] = 0x61;
    puVar3 = puVar3 + 1;
    *puVar3 = 1;
    puVar5 = puVar6;
  } while (puVar6 != (undefined2 *)(param_1 + 0xa79804));
  *(undefined1 *)(param_1 + 0xa7be36) = 0;
  *(undefined1 *)(param_1 + 0xa7be35) = 2;
  puVar3 = (undefined1 *)(param_1 + 0xa79815);
  *(undefined2 *)(param_1 + 0xa79804) = 0x166;
  *(undefined2 *)(param_1 + 0xa79806) = 0x142;
  *(undefined2 *)(param_1 + 0xa79808) = 0xa9;
  *(undefined2 *)(param_1 + 0xa7980a) = 0x61;
  *(undefined2 *)(param_1 + 0xa7980c) = 0x166;
  *(undefined2 *)(param_1 + 0xa7980e) = 0x142;
  *(undefined2 *)(param_1 + 0xa79810) = 0xa9;
  *(undefined2 *)(param_1 + 0xa79812) = 0x61;
  do {
    puVar3 = puVar3 + 1;
    *puVar3 = 0;
  } while (puVar3 != (undefined1 *)(param_1 + 0xa79825));
  *(undefined1 *)(param_1 + 0xa7a312) = 1;
  *(undefined2 *)(param_1 + 0xa7a314) = 0x36;
  *(undefined2 *)(param_1 + 0xa7a316) = 0x208;
  if (*(byte *)(param_1 + 0xa797a4) - 1 < 2) {
    *(undefined1 *)(param_1 + 0xa7a308) = 1;
    *(undefined1 *)(param_1 + 0xa7a309) = 1;
    *(undefined1 *)(param_1 + 0xa7a30a) = 0;
    *(undefined1 *)(param_1 + 0xa7a30b) = 1;
    *(undefined1 *)(param_1 + 0xa7a30c) = 1;
    *(undefined1 *)(param_1 + 0xa7a30e) = 0;
    *(undefined1 *)(param_1 + 0xa7a30f) = 1;
    *(undefined1 *)(param_1 + 0xa7a310) = 1;
    *(undefined1 *)(param_1 + 0xa7a311) = 1;
    *(undefined1 *)(param_1 + 0xa7a319) = 0;
    *(undefined1 *)(param_1 + 0xa7a30d) = 0x14;
    *(undefined1 *)(param_1 + 0xa7a318) = 0x1a;
  }
  return;
}

