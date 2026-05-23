// module: tm.ko
// function: tm_pon_pp_adm_initial @ 0x4dcd0
// size: 3412 bytes
//

uint tm_pon_pp_adm_initial(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  uint uVar28;
  uint uVar29;
  uint uVar30;
  uint uVar31;
  uint uVar32;
  uint uVar33;
  uint uVar34;
  uint uVar35;
  uint uVar36;
  uint uVar37;
  uint uVar38;
  uint uVar39;
  uint uVar40;
  uint uVar41;
  uint uVar42;
  uint uVar43;
  uint uVar44;
  uint uVar45;
  uint uVar46;
  uint uVar47;
  uint uVar48;
  uint uVar49;
  uint uVar50;
  uint uVar51;
  uint uVar52;
  uint uVar53;
  uint uVar54;
  uint uVar55;
  uint uVar56;
  uint uVar57;
  uint uVar58;
  uint uVar59;
  uint uVar60;
  uint uVar61;
  uint uVar62;
  uint uVar63;
  uint uVar64;
  uint uVar65;
  uint uVar66;
  uint uVar67;
  uint uVar68;
  uint uVar69;
  uint uVar70;
  uint uVar71;
  uint uVar72;
  uint uVar73;
  uint uVar74;
  uint uVar75;
  uint uVar76;
  uint uVar77;
  uint uVar78;
  uint uVar79;
  uint uVar80;
  uint uVar81;
  uint uVar82;
  uint uVar83;
  uint uVar84;
  uint uVar85;
  uint uVar86;
  uint uVar87;
  uint uVar88;
  uint uVar89;
  uint uVar90;
  uint uVar91;
  uint uVar92;
  uint uVar93;
  uint uVar94;
  uint uVar95;
  uint uVar96;
  uint uVar97;
  uint uVar98;
  uint uVar99;
  uint uVar100;
  uint uVar101;
  uint uVar102;
  uint uVar103;
  uint uVar104;
  uint uVar105;
  uint uVar106;
  uint uVar107;
  uint uVar108;
  uint uVar109;
  uint uVar110;
  uint uVar111;
  uint uVar112;
  uint uVar113;
  uint uVar114;
  uint uVar115;
  uint uVar116;
  uint uVar117;
  uint uVar118;
  uint uVar119;
  uint uVar120;
  uint uVar121;
  uint uVar122;
  uint uVar123;
  uint uVar124;
  uint uVar125;
  uint uVar126;
  uint uVar127;
  uint uVar128;
  uint uVar129;
  int iVar130;
  int iVar131;
  bool bVar132;
  
  uVar1 = adm_set_turnon_enable(1);
  uVar2 = adm_set_one_second(200000000);
  iVar130 = 0;
  if ((uVar2 | uVar1) != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x1fb);
    return uVar2 | uVar1;
  }
  do {
    uVar1 = tm_protocol_pkt_limit_pps_set(iVar130,0,1,800);
    uVar2 = tm_protocol_pkt_limit_pps_set(iVar130,3,1,400);
    uVar3 = tm_protocol_pkt_limit_pps_set(iVar130,4,1,400);
    uVar4 = tm_protocol_pkt_limit_pps_set(iVar130,5,1,400);
    uVar5 = tm_protocol_pkt_limit_pps_set(iVar130,6,1,1000);
    bVar132 = iVar130 != 1;
    iVar130 = 1;
  } while (bVar132);
  uVar1 = uVar4 | uVar5 | uVar3 | uVar2 | uVar1;
  if (uVar1 != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x206);
    return uVar1;
  }
  iVar130 = 0;
  uVar1 = 0;
  do {
    iVar131 = 0;
    while( true ) {
      uVar2 = tm_protocol_pkt_limit_map_set(iVar130,0,7,iVar131);
      uVar3 = tm_protocol_pkt_limit_map_set(iVar130,1,7,iVar131);
      uVar4 = tm_protocol_pkt_limit_map_set(iVar130,2,6,iVar131);
      uVar5 = tm_protocol_pkt_limit_map_set(iVar130,0x2d,6,iVar131);
      uVar6 = tm_protocol_pkt_limit_map_set(iVar130,0x2e,6,iVar131);
      uVar7 = tm_protocol_pkt_limit_map_set(iVar130,0x2f,6,iVar131);
      uVar8 = tm_protocol_pkt_limit_map_set(iVar130,0x30,6,iVar131);
      uVar9 = tm_protocol_pkt_limit_map_set(iVar130,8,6,iVar131);
      uVar10 = tm_protocol_pkt_limit_map_set(iVar130,9,6,iVar131);
      uVar11 = tm_protocol_pkt_limit_map_set(iVar130,10,6,iVar131);
      uVar12 = tm_protocol_pkt_limit_map_set(iVar130,0xb,6,iVar131);
      uVar13 = tm_protocol_pkt_limit_map_set(iVar130,0xc,6,iVar131);
      uVar14 = tm_protocol_pkt_limit_map_set(iVar130,0x10,6,iVar131);
      uVar15 = tm_protocol_pkt_limit_map_set(iVar130,0x11,6,iVar131);
      uVar16 = tm_protocol_pkt_limit_map_set(iVar130,0x12,6,iVar131);
      uVar17 = tm_protocol_pkt_limit_map_set(iVar130,0x13,6,iVar131);
      uVar18 = tm_protocol_pkt_limit_map_set(iVar130,0x14,6,iVar131);
      uVar19 = tm_protocol_pkt_limit_map_set(iVar130,0x15,6,iVar131);
      uVar20 = tm_protocol_pkt_limit_map_set(iVar130,0x16,6,iVar131);
      uVar21 = tm_protocol_pkt_limit_map_set(iVar130,0x1b,6,iVar131);
      uVar22 = tm_protocol_pkt_limit_map_set(iVar130,0x1c,6,iVar131);
      uVar23 = tm_protocol_pkt_limit_map_set(iVar130,0x1d,6,iVar131);
      uVar24 = tm_protocol_pkt_limit_map_set(iVar130,0x1e,6,iVar131);
      uVar25 = tm_protocol_pkt_limit_map_set(iVar130,0x1f,6,iVar131);
      uVar26 = tm_protocol_pkt_limit_map_set(iVar130,0x20,6,iVar131);
      uVar27 = tm_protocol_pkt_limit_map_set(iVar130,0x21,6,iVar131);
      uVar28 = tm_protocol_pkt_limit_map_set(iVar130,0x22,6,iVar131);
      uVar29 = tm_protocol_pkt_limit_map_set(iVar130,0x23,6,iVar131);
      uVar30 = tm_protocol_pkt_limit_map_set(iVar130,0x24,6,iVar131);
      uVar31 = tm_protocol_pkt_limit_map_set(iVar130,0x25,6,iVar131);
      uVar32 = tm_protocol_pkt_limit_map_set(iVar130,0x26,6,iVar131);
      uVar33 = tm_protocol_pkt_limit_map_set(iVar130,0x27,6,iVar131);
      uVar34 = tm_protocol_pkt_limit_map_set(iVar130,0x28,6,iVar131);
      uVar35 = tm_protocol_pkt_limit_map_set(iVar130,0x29,6,iVar131);
      uVar36 = tm_protocol_pkt_limit_map_set(iVar130,0x2a,6,iVar131);
      uVar37 = tm_protocol_pkt_limit_map_set(iVar130,0x2b,6,iVar131);
      uVar38 = tm_protocol_pkt_limit_map_set(iVar130,0x48,6,iVar131);
      uVar39 = tm_protocol_pkt_limit_map_set(iVar130,0x49,6,iVar131);
      uVar40 = tm_protocol_pkt_limit_map_set(iVar130,0x2c,5,iVar131);
      uVar41 = tm_protocol_pkt_limit_map_set(iVar130,0x53,5,iVar131);
      uVar42 = tm_protocol_pkt_limit_map_set(iVar130,3,4,iVar131);
      uVar43 = tm_protocol_pkt_limit_map_set(iVar130,4,4,iVar131);
      uVar44 = tm_protocol_pkt_limit_map_set(iVar130,5,4,iVar131);
      uVar45 = tm_protocol_pkt_limit_map_set(iVar130,6,4,iVar131);
      uVar46 = tm_protocol_pkt_limit_map_set(iVar130,7,4,iVar131);
      uVar47 = tm_protocol_pkt_limit_map_set(iVar130,0xd,4,iVar131);
      uVar48 = tm_protocol_pkt_limit_map_set(iVar130,0xe,4,iVar131);
      uVar49 = tm_protocol_pkt_limit_map_set(iVar130,0xf,4,iVar131);
      uVar50 = tm_protocol_pkt_limit_map_set(iVar130,0x17,4,iVar131);
      uVar51 = tm_protocol_pkt_limit_map_set(iVar130,0x18,4,iVar131);
      uVar52 = tm_protocol_pkt_limit_map_set(iVar130,0x19,4,iVar131);
      uVar53 = tm_protocol_pkt_limit_map_set(iVar130,0x1a,4,iVar131);
      uVar54 = tm_protocol_pkt_limit_map_set(iVar130,0x33,4,iVar131);
      uVar55 = tm_protocol_pkt_limit_map_set(iVar130,0x34,4,iVar131);
      uVar56 = tm_protocol_pkt_limit_map_set(iVar130,0x35,4,iVar131);
      uVar57 = tm_protocol_pkt_limit_map_set(iVar130,0x36,4,iVar131);
      uVar58 = tm_protocol_pkt_limit_map_set(iVar130,0x37,4,iVar131);
      uVar59 = tm_protocol_pkt_limit_map_set(iVar130,0x38,4,iVar131);
      uVar60 = tm_protocol_pkt_limit_map_set(iVar130,0x39,4,iVar131);
      uVar61 = tm_protocol_pkt_limit_map_set(iVar130,0x3a,4,iVar131);
      uVar62 = tm_protocol_pkt_limit_map_set(iVar130,0x3b,4,iVar131);
      uVar63 = tm_protocol_pkt_limit_map_set(iVar130,0x3c,4,iVar131);
      uVar64 = tm_protocol_pkt_limit_map_set(iVar130,0x3d,4,iVar131);
      uVar65 = tm_protocol_pkt_limit_map_set(iVar130,0x3e,4,iVar131);
      uVar66 = tm_protocol_pkt_limit_map_set(iVar130,0x3f,4,iVar131);
      uVar67 = tm_protocol_pkt_limit_map_set(iVar130,0x40,4,iVar131);
      uVar68 = tm_protocol_pkt_limit_map_set(iVar130,0x41,4,iVar131);
      uVar69 = tm_protocol_pkt_limit_map_set(iVar130,0x42,4,iVar131);
      uVar70 = tm_protocol_pkt_limit_map_set(iVar130,0x43,4,iVar131);
      uVar71 = tm_protocol_pkt_limit_map_set(iVar130,0x44,4,iVar131);
      uVar72 = tm_protocol_pkt_limit_map_set(iVar130,0x45,4,iVar131);
      uVar73 = tm_protocol_pkt_limit_map_set(iVar130,0x46,4,iVar131);
      uVar74 = tm_protocol_pkt_limit_map_set(iVar130,0x4d,4,iVar131);
      uVar75 = tm_protocol_pkt_limit_map_set(iVar130,0x4e,4,iVar131);
      uVar76 = tm_protocol_pkt_limit_map_set(iVar130,0x4f,4,iVar131);
      uVar77 = tm_protocol_pkt_limit_map_set(iVar130,0x55,4,iVar131);
      uVar78 = tm_protocol_pkt_limit_map_set(iVar130,0x58,4,iVar131);
      uVar79 = tm_protocol_pkt_limit_map_set(iVar130,0x59,4,iVar131);
      uVar80 = tm_protocol_pkt_limit_map_set(iVar130,0x5a,4,iVar131);
      uVar81 = tm_protocol_pkt_limit_map_set(iVar130,0x5b,4,iVar131);
      uVar82 = tm_protocol_pkt_limit_map_set(iVar130,0x5c,4,iVar131);
      uVar83 = tm_protocol_pkt_limit_map_set(iVar130,0x5d,4,iVar131);
      uVar84 = tm_protocol_pkt_limit_map_set(iVar130,0x5e,4,iVar131);
      uVar85 = tm_protocol_pkt_limit_map_set(iVar130,0x5f,4,iVar131);
      uVar86 = tm_protocol_pkt_limit_map_set(iVar130,0x62,4,iVar131);
      uVar87 = tm_protocol_pkt_limit_map_set(iVar130,99,4,iVar131);
      uVar88 = tm_protocol_pkt_limit_map_set(iVar130,100,4,iVar131);
      uVar89 = tm_protocol_pkt_limit_map_set(iVar130,0x65,4,iVar131);
      uVar90 = tm_protocol_pkt_limit_map_set(iVar130,0x66,4,iVar131);
      uVar91 = tm_protocol_pkt_limit_map_set(iVar130,0x67,4,iVar131);
      uVar92 = tm_protocol_pkt_limit_map_set(iVar130,0x68,4,iVar131);
      uVar93 = tm_protocol_pkt_limit_map_set(iVar130,0x69,4,iVar131);
      uVar94 = tm_protocol_pkt_limit_map_set(iVar130,0x6a,4,iVar131);
      uVar95 = tm_protocol_pkt_limit_map_set(iVar130,0x6b,4,iVar131);
      uVar96 = tm_protocol_pkt_limit_map_set(iVar130,0x6c,4,iVar131);
      uVar97 = tm_protocol_pkt_limit_map_set(iVar130,0x6d,4,iVar131);
      uVar98 = tm_protocol_pkt_limit_map_set(iVar130,0x6e,4,iVar131);
      uVar99 = tm_protocol_pkt_limit_map_set(iVar130,0x6f,4,iVar131);
      uVar100 = tm_protocol_pkt_limit_map_set(iVar130,0x70,4,iVar131);
      uVar101 = tm_protocol_pkt_limit_map_set(iVar130,0x71,4,iVar131);
      uVar102 = tm_protocol_pkt_limit_map_set(iVar130,0x72,4,iVar131);
      uVar103 = tm_protocol_pkt_limit_map_set(iVar130,0x73,4,iVar131);
      uVar104 = tm_protocol_pkt_limit_map_set(iVar130,0x74,4,iVar131);
      uVar105 = tm_protocol_pkt_limit_map_set(iVar130,0x75,4,iVar131);
      uVar106 = tm_protocol_pkt_limit_map_set(iVar130,0x76,4,iVar131);
      uVar107 = tm_protocol_pkt_limit_map_set(iVar130,0x77,4,iVar131);
      uVar108 = tm_protocol_pkt_limit_map_set(iVar130,0x78,4,iVar131);
      uVar109 = tm_protocol_pkt_limit_map_set(iVar130,0x79,4,iVar131);
      uVar110 = tm_protocol_pkt_limit_map_set(iVar130,0x7a,4,iVar131);
      uVar111 = tm_protocol_pkt_limit_map_set(iVar130,0x7b,4,iVar131);
      uVar112 = tm_protocol_pkt_limit_map_set(iVar130,0x7c,4,iVar131);
      uVar113 = tm_protocol_pkt_limit_map_set(iVar130,0x7d,4,iVar131);
      uVar114 = tm_protocol_pkt_limit_map_set(iVar130,0x7e,4,iVar131);
      uVar115 = tm_protocol_pkt_limit_map_set(iVar130,0x7f,4,iVar131);
      uVar116 = tm_protocol_pkt_limit_map_set(iVar130,0x32,4,iVar131);
      uVar117 = tm_protocol_pkt_limit_map_set(iVar130,0x47,3,iVar131);
      uVar118 = tm_protocol_pkt_limit_map_set(iVar130,0x31,3,iVar131);
      uVar119 = tm_protocol_pkt_limit_map_set(iVar130,0x50,3,iVar131);
      uVar120 = tm_protocol_pkt_limit_map_set(iVar130,0x51,3,iVar131);
      uVar121 = tm_protocol_pkt_limit_map_set(iVar130,0x52,3,iVar131);
      uVar122 = tm_protocol_pkt_limit_map_set(iVar130,0x54,3,iVar131);
      uVar123 = tm_protocol_pkt_limit_map_set(iVar130,0x56,3,iVar131);
      uVar124 = tm_protocol_pkt_limit_map_set(iVar130,0x57,3,iVar131);
      uVar125 = tm_protocol_pkt_limit_map_set(iVar130,0x4b,2,iVar131);
      uVar126 = tm_protocol_pkt_limit_map_set(iVar130,0x4c,1,iVar131);
      uVar127 = tm_protocol_pkt_limit_map_set(iVar130,0x60,1,iVar131);
      uVar128 = tm_protocol_pkt_limit_map_set(iVar130,0x61,1,iVar131);
      uVar129 = tm_protocol_pkt_limit_map_set(iVar130,0x4a,0,iVar131);
      uVar1 = uVar1 | uVar3 | uVar2 | uVar4 | uVar5 | uVar6 | uVar7 | uVar8 | uVar9 | uVar10 |
                      uVar11 | uVar12 | uVar13 | uVar14 | uVar15 | uVar16 | uVar17 | uVar18 | uVar19
                      | uVar20 | uVar21 | uVar22 | uVar23 | uVar24 | uVar25 | uVar26 | uVar27 |
                      uVar28 | uVar29 | uVar30 | uVar31 | uVar32 | uVar33 | uVar34 | uVar35 | uVar36
                      | uVar37 | uVar38 | uVar39 | uVar40 | uVar41 | uVar42 | uVar43 | uVar44 |
                      uVar45 | uVar46 | uVar47 | uVar48 | uVar49 | uVar50 | uVar51 | uVar52 | uVar53
                      | uVar54 | uVar55 | uVar56 | uVar57 | uVar58 | uVar59 | uVar60 | uVar61 |
                      uVar62 | uVar63 | uVar64 | uVar65 | uVar66 | uVar67 | uVar68 | uVar69 | uVar70
                      | uVar71 | uVar72 | uVar73 | uVar74 | uVar75 | uVar76 | uVar77 | uVar78 |
                      uVar79 | uVar80 | uVar81 | uVar82 | uVar83 | uVar84 | uVar85 | uVar86 | uVar87
                      | uVar88 | uVar89 | uVar90 | uVar91 | uVar92 | uVar93 | uVar94 | uVar95 |
                      uVar96 | uVar97 | uVar98 | uVar99 | uVar100 | uVar101 | uVar102 | uVar103 |
                      uVar104 | uVar105 | uVar106 | uVar107 | uVar108 | uVar109 | uVar110 | uVar111
                      | uVar112 | uVar113 | uVar114 | uVar115 | uVar116 | uVar117 | uVar118 |
                      uVar119 | uVar120 | uVar121 | uVar122 | uVar123 | uVar124 | uVar125 | uVar126
                      | uVar127 | uVar128 | uVar129;
      if (iVar131 == 1) break;
      iVar131 = 1;
    }
    iVar130 = iVar130 + 1;
  } while (iVar130 != 8);
  if (uVar1 != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x29a);
    return uVar1;
  }
  return 0;
}

