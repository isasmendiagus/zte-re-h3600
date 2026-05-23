// module: mt7915.ko
// function: WscRxMsgType @ 0x1e1044
// size: 636 bytes
//

undefined1 WscRxMsgType(undefined4 param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint __n;
  char local_6b [6];
  undefined4 local_65;
  char local_61 [5];
  undefined4 local_5c;
  char acStack_58 [4];
  undefined2 local_54;
  char local_52 [13];
  undefined4 local_45;
  char local_41 [22];
  undefined4 local_2b;
  char local_27 [23];
  
  builtin_strncpy(local_6b,"hello",6);
  local_65._0_1_ = 'E';
  local_65._1_1_ = 'A';
  local_65._2_1_ = 'P';
  local_65._3_1_ = '_';
  builtin_strncpy(local_61,"FAIL",5);
  local_5c._0_1_ = 'W';
  local_5c._1_1_ = 'S';
  local_5c._2_1_ = 'C';
  local_5c._3_1_ = '_';
  builtin_strncpy(acStack_58,"STAR",4);
  local_54 = 0x54;
  builtin_strncpy(local_52,"WSC_FRAG_ACK",0xd);
  builtin_strncpy(local_27,"SimpleConfig",0xc);
  local_2b._0_1_ = 'W';
  local_2b._1_1_ = 'F';
  local_2b._2_1_ = 'A';
  local_2b._3_1_ = '-';
  builtin_strncpy(local_27 + 0xc,"-Registrar",0xb);
  local_45._0_1_ = 'W';
  local_45._1_1_ = 'F';
  local_45._2_1_ = 'A';
  local_45._3_1_ = '-';
  builtin_strncpy(local_41,"SimpleConfig-Enrollee",0x16);
  if ((*param_2 & 0xffffff) == 0x414657) {
    iVar2 = memcmp(&local_2b,param_2,0x1a);
    if (iVar2 == 0) {
      return 0x22;
    }
    iVar2 = memcmp(&local_45,param_2,0x19);
    if (iVar2 == 0) {
      return 0x23;
    }
    return 0xff;
  }
  __n = param_2[0x242];
  if (__n != 0) {
    iVar2 = memcmp(local_6b,param_2,__n);
    if (iVar2 == 0) {
      return 0x25;
    }
    iVar2 = memcmp(&local_65,param_2,__n);
    if (iVar2 == 0) {
      return 0x27;
    }
    iVar2 = memcmp(&local_5c,param_2,__n);
    if (iVar2 == 0) {
      return 0x26;
    }
    iVar2 = memcmp(local_52,param_2,__n);
    if (iVar2 == 0) {
      return 0x28;
    }
    if ((ushort)*param_2 == 0x4a10) {
      do {
        uVar1 = __n & 0xffff;
        if (uVar1 < 5) {
          return 0xff;
        }
        uVar3 = (*(ushort *)((int)param_2 + 2) & 0xff) << 8 |
                (uint)(*(ushort *)((int)param_2 + 2) >> 8);
        if ((ushort)((ushort)*param_2 << 8 | (ushort)*param_2 >> 8) == 0x1022) {
          return (char)param_2[1];
        }
        __n = uVar1 + (0xfffc - uVar3);
        param_2 = (uint *)((int)param_2 + uVar3 + 4);
      } while (uVar3 + 4 <= uVar1);
      if (2 < DebugLevel) {
        printk("unexpected WSC IE Length(%u)\n",uVar3);
      }
    }
  }
  return 0xff;
}

