// module: mt7915.ko
// function: RTMPSoftDecryptTKIP @ 0x117e50
// size: 852 bytes
//

undefined1
RTMPSoftDecryptTKIP(int param_1,int param_2,undefined4 param_3,int param_4,byte param_5,
                   undefined1 *param_6,ushort *param_7)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 local_176;
  undefined2 local_172;
  undefined4 local_170;
  undefined2 local_16c;
  undefined4 local_16a;
  undefined2 local_166;
  undefined4 local_164;
  undefined4 uStack_160;
  undefined4 local_15c;
  undefined4 uStack_158;
  undefined1 auStack_154 [16];
  undefined1 auStack_144 [20];
  undefined1 auStack_130 [268];
  
  iVar1 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_1 + (uint)param_5 * 4 + 0xc));
  if (iVar1 == 0) {
    printk(&_LC1,0x2df);
    dump_stack();
  }
  if (*(char *)(param_4 + 0x41) == '\0') {
    if (-1 < DebugLevel) {
      printk("%s : the key is empty)\n","RTMPSoftDecryptTKIP");
      return 0;
    }
  }
  else {
    uVar4 = (uint)*(byte *)(param_2 + 1);
    uVar3 = -((int)(uVar4 << 0x1e) >> 0x1f);
    if ((uVar3 & ~uVar4) == 0) {
      if (uVar3 == 0 && (*(byte *)(param_2 + 1) & 1) == 0) {
        local_170 = *(undefined4 *)(param_2 + 4);
        local_176 = *(undefined4 *)(param_2 + 10);
        local_16c = *(undefined2 *)(param_2 + 8);
        local_172 = *(undefined2 *)(param_2 + 0xe);
        local_16a = local_176;
        local_166 = local_172;
      }
      else if ((uVar4 & 1 & (uVar3 ^ 1)) == 0) {
        if ((uVar3 & uVar4 & 1) != 0) {
          local_170 = *(undefined4 *)(param_2 + 0x10);
          local_176 = *(undefined4 *)(param_2 + 10);
          local_16a = *(undefined4 *)(param_2 + 0x18);
          local_16c = *(undefined2 *)(param_2 + 0x14);
          local_172 = *(undefined2 *)(param_2 + 0xe);
          local_166 = *(undefined2 *)(param_2 + 0x1c);
        }
      }
      else {
        local_176 = *(undefined4 *)(param_2 + 10);
        local_170 = *(undefined4 *)(param_2 + 0x10);
        local_172 = *(undefined2 *)(param_2 + 0xe);
        local_16c = *(undefined2 *)(param_2 + 0x14);
        local_16a = local_176;
        local_166 = local_172;
      }
    }
    else {
      local_176 = *(undefined4 *)(param_2 + 10);
      local_170 = *(undefined4 *)(param_2 + 4);
      local_16a = *(undefined4 *)(param_2 + 0x10);
      local_172 = *(undefined2 *)(param_2 + 0xe);
      local_16c = *(undefined2 *)(param_2 + 8);
      local_166 = *(undefined2 *)(param_2 + 0x14);
    }
    RTMPTkipMixKey(param_4,&local_176,CONCAT11(*param_6,param_6[2]),*(undefined4 *)(param_6 + 4),
                   auStack_154,auStack_144);
    uVar3 = (uint)*param_7;
    if (8 < uVar3) {
      ARC4_INIT(auStack_130,auStack_154,0x10);
      ARC4_Compute(auStack_130,param_6 + 8,uVar3 - 8,param_6);
      uVar4 = *(uint *)(param_6 + (uVar3 - 0xc));
      uVar2 = RTMP_CALC_FCS32(0xffffffff,param_6);
      if (~uVar2 == uVar4) {
        iVar6 = uVar3 - 0x14;
        local_15c = *(undefined4 *)(param_6 + iVar6);
        uStack_158 = *(undefined4 *)((int)(param_6 + iVar6) + 4);
        RTMPInitMICEngine(param_1,param_4,&local_170,&local_16a,param_3,param_4 + 0x18);
        for (iVar5 = iVar6; iVar5 != 0; iVar5 = iVar5 + -1) {
          RTMPTkipAppendByte(param_1 + 0xa39f14,*param_6);
          param_6 = param_6 + 1;
        }
        RTMPTkipGetMIC(param_1 + 0xa39f14);
        local_164 = *(undefined4 *)(param_1 + 0xa39f44);
        uStack_160 = *(undefined4 *)(param_1 + 0xa39f48);
        iVar5 = memcmp(&local_164,&local_15c,8);
        if (iVar5 != 0) {
          if (-1 < DebugLevel) {
            printk("! TKIP MIC Error !\n");
          }
          RTMPReportMicError(param_1,iVar1,param_4);
          return 0;
        }
        *param_7 = (ushort)iVar6;
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("! WEP Data CRC Error !\n");
        return 0;
      }
    }
  }
  return 0;
}

