// module: mt7915.ko
// function: ProcessMessageM1 @ 0x1f7114
// size: 1976 bytes
//

undefined4 ProcessMessageM1(int param_1,int param_2,void *param_3,size_t param_4,char *param_5)

{
  bool bVar1;
  undefined1 uVar2;
  uint uVar3;
  uint *__dest;
  undefined4 uVar4;
  uint __n;
  char *__src;
  uint uVar5;
  undefined1 *puVar6;
  int iVar7;
  uint uVar8;
  uint *__src_00;
  uint local_114;
  uint local_110;
  uint local_10c;
  int local_100;
  undefined1 local_ed;
  uint local_ec;
  undefined4 local_e8;
  undefined1 auStack_28 [4];
  
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    local_100 = 0;
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
    local_100 = 2;
  }
  else {
    local_100 = 0xff;
  }
  __src = param_5 + 0x469;
  param_5[0x175] = '\0';
  local_ec = 0xc0;
  __memzero(__src,0xc0);
  puVar6 = (undefined1 *)(param_2 + 0x357);
  do {
    uVar2 = RandomByte(param_1);
    puVar6 = puVar6 + 1;
    *puVar6 = uVar2;
  } while (puVar6 != (undefined1 *)(param_2 + 0x417));
  DH_PublicKey_Generate(&WPS_DH_G_VALUE,1,WPS_DH_P_VALUE,0xc0,param_2 + 0x358,0xc0,__src,&local_ec);
  if (local_ec < 0xc0) {
    iVar7 = 0xc0 - local_ec;
    __memzero(&local_e8,iVar7);
    uVar5 = local_ec;
    memcpy((void *)((int)&local_e8 + iVar7),__src,local_ec);
    memcpy(__src,&local_e8,0xc0);
    local_ec = iVar7 + uVar5;
    if (2 < DebugLevel) {
      printk("%s: Do zero padding!\n","ProcessMessageM1");
    }
  }
  __dest = (uint *)(param_5 + 0x1274);
  *(size_t *)(param_5 + 0x1270) = param_4;
  memmove(__dest,param_3,param_4);
  __memzero((void *)(param_2 + 0x2a5b),0xc6);
  param_5[0x2e5] = '\0';
  if ((int)param_4 < 5) {
    uVar4 = 0xfd;
  }
  else {
    uVar5 = 0x2314;
    uVar8 = 0x201f;
    local_114 = 0x407;
    local_10c = 0x1004;
    local_110 = 0x494;
    bVar1 = true;
    do {
      uVar3 = *__dest;
      local_e8._2_2_ = (ushort)(uVar3 >> 0x10);
      __n = (local_e8._2_2_ & 0xff) << 8 | (uint)(local_e8._2_2_ >> 8);
      local_e8 = uVar3;
      if ((int)param_4 < (int)(__n + 4)) {
        if (2 < DebugLevel) {
          printk("unexpected WSC IE Length(%u)\n",__n);
        }
        break;
      }
      __src_00 = __dest + 1;
      switch((uVar3 & 0xff) << 8 | uVar3 >> 8 & 0xff) {
      case 0x1002:
        uVar5 = uVar5 ^ 4;
        *(short *)(param_5 + 0x278) = (short)__dest[1];
        break;
      default:
        if (2 < DebugLevel) {
          printk("ProcessMessageM1 --> Unknown IE 0x%04x\n");
        }
        break;
      case 0x1004:
        uVar5 = uVar5 ^ 0x10;
        *(short *)(param_5 + 0x1c6) = (short)__dest[1];
        break;
      case 0x1008:
        uVar5 = uVar5 ^ 0x100;
        *(short *)(param_5 + 0x1cc) = (short)__dest[1];
        break;
      case 0x1009:
        uVar5 = uVar5 ^ 0x200;
        *(short *)(param_5 + 0x27c) = (short)__dest[1];
        break;
      case 0x100d:
        uVar5 = uVar5 ^ 0x2000;
        param_5[0x1ca] = (char)__dest[1];
        break;
      case 0x1010:
        local_114 = local_114 ^ 1;
        *(short *)(param_5 + 0x1c8) = (short)__dest[1];
        break;
      case 0x1011:
        local_114 = local_114 ^ 2;
        memmove(param_5 + 0x18c,__src_00,__n);
        memmove((void *)(param_2 + 0x2a5b),__src_00,__n);
        break;
      case 0x1012:
        if (DebugLevel < 3) {
          if ((short)__dest[1] == 0) {
LAB_001f78d4:
            *(undefined2 *)(param_2 + 0x176) = 0;
            local_114 = local_114 ^ 4;
            break;
          }
          if ((short)__dest[1] == 4) {
LAB_001f7908:
            *(undefined2 *)(param_2 + 0x176) = 0x400;
          }
        }
        else {
          printk("   WPS Registrar DPID %04x\n",*(undefined2 *)(param_5 + 0x106));
          if ((short)__dest[1] == 0) {
            if (2 < DebugLevel) {
              printk("Rx WPS           DPID PIN\n");
            }
            goto LAB_001f78d4;
          }
          if ((short)__dest[1] == 4) {
            if (2 < DebugLevel) {
              printk("Rx WPS           DPID PBC\n");
            }
            goto LAB_001f7908;
          }
          if (2 < DebugLevel) {
            printk("Rx WPS           DPID unsupport\n");
          }
        }
        local_114 = local_114 ^ 4;
        break;
      case 0x101a:
        local_114 = local_114 ^ 0x400;
        memmove(param_5 + 0x1ad0,__src_00,__n);
        break;
      case 0x1020:
        memmove(param_5 + 0x186,__src_00,__n);
        uVar8 = uVar8 ^ 1;
        memmove((void *)(param_2 + 0x2b1b),__src_00,__n);
        break;
      case 0x1021:
        memmove(param_5 + 0x1cf,__src_00,__n);
        uVar8 = uVar8 ^ 2;
        memmove((void *)(param_2 + 0x2a7b),__src_00,__n);
        break;
      case 0x1022:
        if (((char)__dest[1] != '\x04') && (-1 < DebugLevel)) {
          printk("Rx WPS Message Type mismatched %02x\n");
        }
        uVar8 = uVar8 ^ 4;
        break;
      case 0x1023:
        memmove(param_5 + 0x20f,__src_00,__n);
        uVar8 = uVar8 ^ 8;
        memmove((void *)(param_2 + 0x2abb),__src_00,__n);
        break;
      case 0x1024:
        memmove(param_5 + 0x22f,__src_00,__n);
        uVar8 = uVar8 ^ 0x10;
        memmove((void *)(param_2 + 0x2adb),__src_00,__n);
        break;
      case 0x102d:
        uVar8 = uVar8 ^ 0x2000;
        *(uint *)(param_5 + 0x270) = __dest[1];
        break;
      case 0x1032:
        local_10c = local_10c ^ 4;
        memmove(param_5 + 0x3a9,__src_00,__n);
        break;
      case 0x103c:
        param_5[0x26f] = (char)__dest[1];
        local_10c = local_10c ^ 0x1000;
        break;
      case 0x1042:
        memmove(param_5 + 0x24f,__src_00,__n);
        local_110 = local_110 ^ 4;
        memmove((void *)(param_2 + 0x2afb),__src_00,__n);
        break;
      case 0x1044:
        uVar3 = __dest[1];
        param_5[0x1ce] = (char)uVar3;
        if (local_100 == 2) {
          *(bool *)(param_2 + 0x2788) = (char)uVar3 == '\x02';
        }
        local_110 = local_110 ^ 0x10;
        break;
      case 0x1047:
        local_110 = local_110 ^ 0x80;
        memmove(param_5 + 0x176,__src_00,__n);
        break;
      case 0x1049:
        if (*(char *)(param_2 + 0x2b31) != '\0') {
          local_ed = 0;
          WscParseV2SubItem(0,__src_00,__n,param_5 + 0x175,&local_ed);
          if (2 < DebugLevel) {
            printk("ProcessMessageM1 --> Version2 = %x\n",param_5[0x175]);
          }
        }
        if (*(char *)(param_1 + 0xa7cbfa) == '\x01') {
          local_ed = 0;
          WscParseV2SubItem(6,__src_00,__n,param_5 + 0x2e5,&local_ed);
          if (0 < DebugLevel) {
            printk("ProcessMessageM1 --> MAP PeerRole = %x\n",param_5[0x2e5]);
          }
        }
        break;
      case 0x104a:
        if ((*param_5 != (char)__dest[1]) && (-1 < DebugLevel)) {
          printk("Rx WPS Message Version mismatched %02x\n");
        }
        local_110 = local_110 ^ 0x400;
        break;
      case 0x1054:
        bVar1 = (bool)(bVar1 ^ 1);
        memmove(param_5 + 0x1ac,__src_00,__n);
      }
      param_4 = (param_4 - 4) - __n;
      __dest = (uint *)((int)__src_00 + __n);
    } while (4 < (int)param_4);
    if ((((uVar5 == 0) && (local_114 == 0)) && (uVar8 == 0)) &&
       ((local_10c == 0 && (local_110 == 0)))) {
      if (bVar1) {
        uVar4 = 0xfd;
      }
      else {
        uVar4 = 0;
      }
    }
    else {
      uVar4 = 0xfd;
    }
  }
  if (2 < DebugLevel) {
    printk("ProcessMessageM1 :\n");
  }
  return uVar4;
}

