// module: mt7915.ko
// function: wifi_test_muru_set_manual_config @ 0x23e95c
// size: 844 bytes
//

bool wifi_test_muru_set_manual_config(undefined4 param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined2 uVar9;
  int iVar10;
  uint uVar11;
  undefined4 uVar12;
  undefined1 *puVar13;
  undefined4 *puVar14;
  undefined1 *puVar15;
  undefined4 *puVar16;
  undefined2 *puVar17;
  undefined2 *puVar18;
  bool bVar19;
  undefined4 local_250;
  undefined4 local_24c;
  undefined4 local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined1 local_22c;
  undefined1 local_22b;
  undefined1 local_22a;
  undefined1 local_229;
  undefined1 local_228;
  byte local_226;
  undefined1 local_225;
  undefined1 local_224;
  undefined1 local_223;
  undefined1 local_222;
  undefined1 local_221;
  undefined1 local_220;
  undefined1 local_21f;
  undefined1 local_21e [8];
  undefined1 local_216;
  undefined1 local_215;
  undefined2 local_214;
  undefined1 local_212 [12];
  undefined2 local_206 [121];
  byte local_114;
  undefined1 local_113;
  undefined2 local_112;
  undefined2 local_110;
  undefined1 local_10e;
  undefined1 local_10d;
  undefined2 local_10c;
  undefined1 local_10a;
  undefined1 local_109 [17];
  undefined2 local_f8 [96];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined1 local_2c;
  
  local_24c = 0;
  local_248 = 0;
  local_244 = 0;
  local_240 = 0;
  local_23c = 0;
  local_250 = 100;
  memset(&local_238,0,0x210);
  local_238 = *param_2;
  puVar15 = (undefined1 *)((int)param_2 + 0x19);
  local_21f = *puVar15;
  local_22c = *(undefined1 *)(param_2 + 3);
  local_22b = *(undefined1 *)((int)param_2 + 0xd);
  local_22a = *(undefined1 *)((int)param_2 + 0xe);
  local_229 = *(undefined1 *)((int)param_2 + 0xf);
  local_228 = *(undefined1 *)(param_2 + 4);
  local_234 = param_2[1];
  local_226 = *(byte *)((int)param_2 + 0x12);
  puVar13 = &local_21f;
  local_225 = *(undefined1 *)((int)param_2 + 0x13);
  local_224 = *(undefined1 *)(param_2 + 5);
  local_223 = *(undefined1 *)((int)param_2 + 0x15);
  local_222 = *(undefined1 *)((int)param_2 + 0x16);
  local_221 = *(undefined1 *)((int)param_2 + 0x17);
  local_220 = *(undefined1 *)(param_2 + 6);
  do {
    puVar15 = puVar15 + 1;
    puVar13 = puVar13 + 1;
    *puVar13 = *puVar15;
  } while (puVar15 != (undefined1 *)((int)param_2 + 0x21));
  local_216 = *(undefined1 *)((int)param_2 + 0x22);
  local_215 = *(undefined1 *)((int)param_2 + 0x23);
  if (local_226 != 0) {
    uVar11 = 0;
    puVar14 = param_2;
    puVar16 = &local_238;
    do {
      uVar11 = uVar11 + 1;
      uVar1 = *(undefined1 *)((int)puVar14 + 0x26);
      uVar2 = *(undefined1 *)((int)puVar14 + 0x27);
      uVar3 = *(undefined1 *)(puVar14 + 10);
      uVar4 = *(undefined1 *)((int)puVar14 + 0x29);
      uVar5 = *(undefined1 *)((int)puVar14 + 0x2a);
      uVar6 = *(undefined1 *)((int)puVar14 + 0x2b);
      uVar7 = *(undefined1 *)(puVar14 + 0xb);
      *(undefined2 *)(puVar16 + 9) = *(undefined2 *)(puVar14 + 9);
      *(undefined1 *)((int)puVar16 + 0x26) = uVar1;
      uVar1 = *(undefined1 *)((int)puVar14 + 0x2d);
      uVar8 = *(undefined1 *)(puVar14 + 0xc);
      *(undefined1 *)((int)puVar16 + 0x27) = uVar2;
      *(undefined1 *)(puVar16 + 10) = uVar3;
      uVar9 = *(undefined2 *)((int)puVar14 + 0x32);
      uVar2 = *(undefined1 *)((int)puVar14 + 0x2e);
      *(undefined1 *)((int)puVar16 + 0x29) = uVar4;
      uVar3 = *(undefined1 *)((int)puVar14 + 0x2f);
      *(undefined1 *)((int)puVar16 + 0x2a) = uVar5;
      *(undefined1 *)((int)puVar16 + 0x2b) = uVar6;
      *(undefined1 *)(puVar16 + 0xb) = uVar7;
      *(undefined1 *)((int)puVar16 + 0x2d) = uVar1;
      *(undefined1 *)(puVar16 + 0xc) = uVar8;
      *(undefined2 *)((int)puVar16 + 0x32) = uVar9;
      *(undefined1 *)((int)puVar16 + 0x2e) = uVar2;
      *(undefined1 *)((int)puVar16 + 0x2f) = uVar3;
      puVar14 = puVar14 + 4;
      puVar16 = puVar16 + 4;
    } while (local_226 != uVar11);
  }
  local_230 = param_2[2];
  local_110 = *(undefined2 *)(param_2 + 0x4a);
  puVar14 = (undefined4 *)((int)param_2 + 0x12e);
  local_10c = *(undefined2 *)(param_2 + 0x4b);
  local_112 = *(undefined2 *)((int)param_2 + 0x126);
  local_114 = *(byte *)(param_2 + 0x49);
  puVar13 = &local_10a;
  local_113 = *(undefined1 *)((int)param_2 + 0x125);
  local_10e = *(undefined1 *)((int)param_2 + 0x12a);
  local_10d = *(undefined1 *)((int)param_2 + 299);
  local_10a = *(undefined1 *)((int)param_2 + 0x12e);
  local_2c = *(undefined1 *)(param_2 + 0x83);
  local_34 = param_2[0x81];
  local_30 = param_2[0x82];
  local_38 = param_2[0x80];
  do {
    puVar14 = (undefined4 *)((int)puVar14 + 1);
    puVar13 = puVar13 + 1;
    *puVar13 = *(undefined1 *)puVar14;
  } while (puVar14 != param_2 + 0x4d);
  if (local_114 != 0) {
    puVar13 = (undefined1 *)((int)param_2 + 0x142);
    puVar17 = local_f8;
    do {
      puVar18 = puVar17 + 6;
      uVar1 = *puVar13;
      uVar2 = puVar13[1];
      uVar3 = puVar13[2];
      uVar4 = puVar13[3];
      uVar5 = puVar13[4];
      uVar6 = puVar13[5];
      uVar12 = *(undefined4 *)(puVar13 + 6);
      *puVar17 = *(undefined2 *)(puVar13 + -2);
      *(undefined1 *)(puVar17 + 1) = uVar1;
      *(undefined1 *)((int)puVar17 + 3) = uVar2;
      *(undefined1 *)(puVar17 + 2) = uVar3;
      *(undefined1 *)((int)puVar17 + 5) = uVar4;
      *(undefined1 *)(puVar17 + 3) = uVar5;
      *(undefined1 *)((int)puVar17 + 7) = uVar6;
      *(undefined4 *)(puVar17 + 4) = uVar12;
      puVar13 = puVar13 + 0xc;
      puVar17 = puVar18;
    } while (puVar18 != local_f8 + (uint)local_114 * 6);
  }
  iVar10 = AndesAllocCmdMsg(param_1,0x214);
  bVar19 = iVar10 != 0;
  if (bVar19) {
    local_24c = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_24c));
    local_248 = CONCAT31(local_248._1_3_,10);
    AndesInitCmdMsg(iVar10,local_24c,local_248,local_244,local_240,local_23c);
    AndesAppendCmdMsg(iVar10,&local_250,4);
    AndesAppendCmdMsg(iVar10,&local_238,0x210);
    AndesSendCmdMsg(param_1,iVar10);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","wifi_test_muru_set_manual_config",bVar19);
  }
  return bVar19;
}

