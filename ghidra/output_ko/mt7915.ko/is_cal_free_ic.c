// module: mt7915.ko
// function: is_cal_free_ic @ 0x17d0d4
// size: 684 bytes
//

undefined4 is_cal_free_ic(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  ushort *puVar6;
  undefined2 local_2c;
  undefined2 local_2a [3];
  
  local_2c = 0;
  iVar2 = rtmp_ee_efuse_read16(param_1,0x50,&local_2c);
  if ((iVar2 != 0) || ((byte)local_2c == '\0')) {
    if (DebugLevel < 1) {
      return 0;
    }
    printk(&_LC315,"is_cal_free_ic");
    return 0;
  }
  if (DebugLevel < 1) {
    uVar4 = 1;
    if ((byte)local_2c != '\x01') {
      return 0;
    }
  }
  else {
    printk(&_LC316);
    uVar4 = (uint)(byte)local_2c;
    if (1 < uVar4) {
      if (DebugLevel < 1) {
        return 0;
      }
      printk(&_LC317);
      return 0;
    }
  }
  iVar2 = (uVar4 - 1) * 0x7a;
  cVar1 = (&DAT_0029b96c)[iVar2];
  if (cVar1 != '\0') {
    puVar6 = (ushort *)(&DAT_0029b96c + iVar2);
    do {
      puVar6 = puVar6 + 1;
      uVar5 = (uint)*puVar6;
      local_2a[0] = 0;
      uVar3 = uVar5;
      if ((*puVar6 & 1) != 0) {
        uVar3 = uVar5 - 1 & 0xffff;
      }
      iVar2 = rtmp_ee_efuse_read16(param_1,uVar3,local_2a);
      if (((iVar2 != 0) && (7 < uVar5 - 0xa8)) && (7 < uVar5 - 0x9b0)) goto LAB_0017d2a8;
    } while (puVar6 != (ushort *)(&DAT_0029b96c + ((byte)(cVar1 - 1) + 1 + (uVar4 - 1) * 0x3d) * 2))
    ;
  }
  iVar2 = rtmp_ee_efuse_read16(param_1,0x9a0,&local_2c);
  if (iVar2 == 0) {
    uVar4 = (uint)(byte)local_2c;
    if (uVar4 != 0) {
      if (DebugLevel < 1) {
        if (2 < uVar4) {
          return 0;
        }
      }
      else {
        printk(&_LC320);
        uVar4 = (uint)(byte)local_2c;
        if (2 < uVar4) {
          if (DebugLevel < 1) {
            return 0;
          }
          printk(&_LC321);
          return 0;
        }
      }
      iVar2 = (uVar4 - 1) * 0x7a;
      cVar1 = (&DAT_0029b9e8)[iVar2];
      if (cVar1 != '\0') {
        puVar6 = (ushort *)(&DAT_0029b9e8 + iVar2);
        do {
          puVar6 = puVar6 + 1;
          uVar5 = (uint)*puVar6;
          local_2a[0] = 0;
          uVar3 = uVar5;
          if ((*puVar6 & 1) != 0) {
            uVar3 = uVar5 - 1 & 0xffff;
          }
          iVar2 = rtmp_ee_efuse_read16(param_1,uVar3,local_2a);
          if (iVar2 != 0) {
LAB_0017d2a8:
            if (DebugLevel < 1) {
              return 0;
            }
            printk(&_LC318,"is_cal_free_ic",uVar5);
            return 0;
          }
        } while (puVar6 != (ushort *)
                           (&DAT_0029b9e8 + ((byte)(cVar1 - 1) + 1 + (uVar4 - 1) * 0x3d) * 2));
      }
      return 1;
    }
  }
  if (DebugLevel < 1) {
    return 0;
  }
  printk(&_LC319,"is_cal_free_ic");
  return 0;
}

