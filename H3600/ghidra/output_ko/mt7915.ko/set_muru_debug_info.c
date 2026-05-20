// module: mt7915.ko
// function: set_muru_debug_info @ 0x23e1e4
// size: 1656 bytes
//

undefined4 set_muru_debug_info(void)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  undefined1 uVar12;
  undefined1 uVar13;
  undefined1 uVar14;
  undefined1 uVar15;
  undefined1 uVar16;
  undefined1 uVar17;
  undefined1 uVar18;
  undefined1 uVar19;
  undefined1 uVar20;
  undefined1 uVar21;
  undefined1 uVar22;
  undefined1 uVar23;
  undefined1 uVar24;
  undefined1 uVar25;
  undefined1 uVar26;
  undefined1 uVar27;
  undefined2 uVar28;
  undefined2 uVar29;
  undefined1 uVar30;
  undefined1 uVar31;
  undefined2 uVar32;
  undefined1 uVar33;
  undefined1 uVar34;
  undefined1 uVar35;
  undefined1 uVar36;
  undefined1 uVar37;
  undefined1 uVar38;
  undefined1 uVar39;
  int iVar40;
  int iVar41;
  uint uVar42;
  undefined2 *puVar43;
  uint uVar44;
  undefined1 *puVar45;
  undefined1 auStack_238 [36];
  undefined2 uStack_214;
  undefined1 auStack_212 [282];
  undefined2 auStack_f8 [106];
  
  memcpy(auStack_238,&DAT_005f5920,0x210);
  uVar39 = DAT_005f5a54;
  uVar38 = DAT_005f5a53;
  uVar37 = DAT_005f5a52;
  uVar36 = DAT_005f5a51;
  uVar35 = DAT_005f5a50;
  uVar34 = DAT_005f5a4f;
  uVar33 = DAT_005f5a4e;
  uVar32 = DAT_005f5a4c;
  uVar31 = DAT_005f5a4b;
  uVar30 = DAT_005f5a4a;
  uVar29 = DAT_005f5a48;
  uVar28 = DAT_005f5a46;
  uVar27 = DAT_005f5a45;
  uVar26 = DAT_005f5943;
  uVar25 = DAT_005f5942;
  uVar24 = DAT_005f5941;
  uVar23 = DAT_005f5940;
  uVar22 = DAT_005f593f;
  uVar21 = DAT_005f593e;
  uVar20 = DAT_005f593d;
  uVar19 = DAT_005f593c;
  uVar18 = DAT_005f593b;
  uVar17 = DAT_005f593a;
  uVar16 = DAT_005f5939;
  uVar15 = DAT_005f5938;
  uVar14 = DAT_005f5937;
  uVar13 = DAT_005f5936;
  uVar12 = DAT_005f5935;
  uVar11 = DAT_005f5934;
  uVar10 = DAT_005f5933;
  uVar9 = DAT_005f5930;
  uVar8 = DAT_005f592f;
  uVar7 = DAT_005f592e;
  uVar6 = DAT_005f592d;
  uVar5 = DAT_005f592c;
  uVar4 = DAT_005f5928;
  uVar3 = DAT_005f5924;
  uVar2 = DAT_005f5920;
  uVar42 = (uint)DAT_005f5932;
  uVar44 = (uint)DAT_005f5a44;
  if (((((((DebugLevel < 1) || (printk(&_LC39,"set_muru_debug_info"), DebugLevel < 1)) ||
         (printk("gu4MuruManCfgUsrListDl: 0x%x\n",_LANCHOR1), DebugLevel < 1)) ||
        (((printk("gu4MuruManCfgUsrListUl: 0x%x\n",DAT_005f591c), DebugLevel < 1 ||
          (printk("----- CMM PROFILE -----\n"), DebugLevel < 1)) ||
         ((printk("u4ManCfgBmpCmm: 0x%x\n",uVar2), DebugLevel < 1 ||
          ((printk("rCfgCmm.u1PpduFmt: %u\n",uVar5), DebugLevel < 1 ||
           (printk("rCfgCmm.u1SchType: %u\n",uVar6), DebugLevel < 1)))))))) ||
       (printk("rCfgCmm.u1Band: %u\n",uVar7), DebugLevel < 1)) ||
      ((((((printk("rCfgCmm.u1WmmSet: %u\n",uVar8), DebugLevel < 1 ||
           (printk("rCfgCmm.u1SpeIdx: %u\n",uVar9), DebugLevel < 1)) ||
          (printk("----- DL TX CONFIG -----\n"), DebugLevel < 1)) ||
         ((printk("u4ManCfgBmpDl: 0x%x\n",uVar3), DebugLevel < 1 ||
          (printk("rCfgDl.u1UserCnt: %u\n",uVar42), DebugLevel < 1)))) ||
        (printk("rCfgDl.u1TxMode: %u\n",uVar10), DebugLevel < 1)) ||
       ((printk("rCfgDl.u1Bw: %u\n",uVar11), DebugLevel < 1 ||
        (printk("rCfgDl.u1GI: %u\n",uVar12), DebugLevel < 1)))))) ||
     ((printk("rCfgDl.u1Ltf: %u\n",uVar13), DebugLevel < 1 ||
      (((printk("rCfgDl.u1SigBMcs: %u\n",uVar14), DebugLevel < 1 ||
        (printk("rCfgDl.u1SigBDcm: %u\n",uVar15), DebugLevel < 1)) ||
       (printk("rCfgDl.u1SigBCmprs: %u\n",uVar16), DebugLevel < 1)))))) {
    if (uVar42 == 0) goto LAB_0023e374;
LAB_0023e348:
    puVar45 = auStack_238;
    iVar40 = DebugLevel;
    iVar41 = 1;
    do {
      if (0 < iVar40) {
        printk("User:%u, WlanIdx:%u, RBN:%u, RBIdx:%u, LDPC:%u, Nsts:%u, MCS:%u, MUGrpIdx:%u, VhtGid:%u, VhtUp:%u, HeStartStream:%u, HeMuMimoSpatial:%u, AckPolicy:%u\n"
               ,iVar41,*(undefined2 *)(puVar45 + 0x24),puVar45[0x26],puVar45[0x27],puVar45[0x28],
               puVar45[0x29],puVar45[0x2a],puVar45[0x2b],puVar45[0x2c],puVar45[0x2d],puVar45[0x2e],
               puVar45[0x2f],puVar45[0x30]);
        iVar40 = DebugLevel;
      }
      puVar45 = puVar45 + 0x10;
      bVar1 = iVar41 < (int)uVar42;
      iVar41 = iVar41 + 1;
    } while (bVar1);
  }
  else {
    printk("rCfgDl.toneplan: RU1=%u,RU2=%u,RU3=%u,RU4=%u,D26=%u,RU5=%u,RU6=%u,RU7=%u,RU8=%u,U26=%u\n"
           ,uVar17,uVar18,uVar19,uVar20,uVar25,uVar21,uVar22,uVar23,uVar24,uVar26);
    iVar40 = DebugLevel;
    if (uVar42 != 0) goto LAB_0023e348;
  }
  if (((((0 < iVar40) && (printk("----- UL TX CONFIG -----\n"), 0 < DebugLevel)) &&
       ((printk("u4ManCfgBmpUl: 0x%x\n",uVar4), 0 < DebugLevel &&
        ((printk("rCfgUl.u1UserCnt: %u\n",uVar44), 0 < DebugLevel &&
         (printk("rCfgUl.u1TrigType: %u\n",uVar27), 0 < DebugLevel)))))) &&
      ((printk("rCfgUl.u2TrigCnt: %u\n",uVar28), 0 < DebugLevel &&
       (((printk("rCfgUl.u2TrigIntv: %u\n",uVar29), 0 < DebugLevel &&
         (printk("rCfgUl.u1TrigTa: %02x:%02x:%02x:%02x:%02x:%02x\n",uVar34,uVar35,uVar36,uVar37,
                 uVar38,uVar39), 0 < DebugLevel)) &&
        (printk("rCfgUl.u1UlBw: %u\n",uVar30), 0 < DebugLevel)))))) &&
     ((printk("rCfgUl.u1UlGiLtf: %u\n",uVar31), 0 < DebugLevel &&
      (printk("rCfgUl.u2UlLength: %u\n",uVar32), 0 < DebugLevel)))) {
    printk("rCfgUl.u1TfPad: %u\n",uVar33);
  }
LAB_0023e374:
  if (uVar44 != 0) {
    puVar43 = auStack_f8;
    iVar40 = 1;
    do {
      if (0 < DebugLevel) {
        printk("User:%u, WlanIdx:%u, RBN:%u, RBIdx:%u, LDPC:%u, Nsts:%u, MCS:%u, TargetRSSI:%u, PktSize=%u\n"
               ,iVar40,*puVar43,*(undefined1 *)(puVar43 + 1),*(undefined1 *)((int)puVar43 + 3),
               *(undefined1 *)(puVar43 + 2),*(undefined1 *)((int)puVar43 + 5),
               *(undefined1 *)(puVar43 + 3),*(undefined1 *)((int)puVar43 + 7),
               *(undefined4 *)(puVar43 + 4));
      }
      puVar43 = puVar43 + 6;
      bVar1 = iVar40 < (int)uVar44;
      iVar40 = iVar40 + 1;
    } while (bVar1);
  }
  return 1;
}

