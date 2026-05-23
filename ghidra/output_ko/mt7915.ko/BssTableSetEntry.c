// module: mt7915.ko
// function: BssTableSetEntry @ 0x10f6c4
// size: 704 bytes
//

uint BssTableSetEntry(int param_1,undefined4 param_2,uint *param_3,int param_4,char param_5,
                     undefined2 param_6,undefined4 param_7)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  void *__s2;
  undefined *__s1;
  int iVar7;
  
  __s2 = (void *)(param_4 + 6);
  iVar7 = (int)param_5;
  iVar3 = GetStaCfgByWdev();
  iVar4 = get_scan_ctrl_by_wdev(param_1,param_2);
  uVar5 = BssTableSearch(param_3,__s2,*(undefined1 *)(param_4 + 0x30));
  if (uVar5 == 0xffffffff) {
    uVar5 = *param_3;
    if (uVar5 < 0x100) {
      BssEntrySet(param_1,param_3,param_3 + uVar5 * 0x2bd + 2,param_4,iVar7,param_6,param_7);
      *param_3 = *param_3 + 1;
    }
    else {
      cVar1 = (&DAT_003678f9)[param_1];
      if (cVar1 != '\0') {
        __s1 = &DAT_00371c92 + param_1;
        do {
          iVar6 = memcmp(__s1,__s2,6);
          if ((iVar6 == 0) ||
             (((*(byte *)(param_4 + 0x2c) != 0 &&
               ((uint)(byte)__s1[-1] == (uint)*(byte *)(param_4 + 0x2c))) &&
              (iVar6 = memcmp(__s1 + -0x21,(void *)(param_4 + 0xc),(uint)(byte)__s1[-1]), iVar6 == 0
              )))) {
            bVar2 = true;
            goto LAB_0010f7f8;
          }
          __s1 = __s1 + 0x2137b0;
        } while (__s1 != (undefined *)(param_1 + (uint)(byte)(cVar1 - 1) * 0x2137b0 + 0x585442));
      }
      bVar2 = false;
LAB_0010f7f8:
      if ((((iVar3 != 0) && ((*(uint *)(iVar3 + 0x212464) & 0x80) == 0)) ||
          ((*(uint *)(param_1 + 0x795124) & 0x200080) != 0x200080)) &&
         (((iVar3 = memcmp((void *)(iVar4 + 0x24),__s2,6), iVar3 == 0 ||
           (((uint)*(byte *)(param_4 + 0x2c) == (uint)*(byte *)(iVar4 + 3) &&
            (iVar3 = memcmp((void *)(iVar4 + 4),(void *)(param_4 + 0xc),
                            (uint)*(byte *)(param_4 + 0x2c)), iVar3 == 0)))) || (bVar2)))) {
        uVar5 = param_3[1];
        __memzero(param_3 + (uint)(byte)uVar5 * 0x2bd + 2,0xaf4);
        BssEntrySet(param_1,param_3,param_3 + (uint)(byte)uVar5 * 0x2bd + 2,param_4,iVar7,param_6,
                    param_7);
        *(char *)(param_3 + 1) = (char)param_3[1] + '\x01';
        return (uint)(byte)uVar5;
      }
      uVar5 = 0xffffffff;
    }
  }
  else {
    if (uVar5 < 0x100) {
      BssEntrySet(param_1,param_3,param_3 + uVar5 * 0x2bd + 2,param_4,iVar7,param_6,param_7);
      return uVar5;
    }
    if (3 < DebugLevel) {
      printk("%s(error):Idx is larger than MAX_LEN_OF_BSS_TABLE","BssTableSetEntry");
    }
  }
  return uVar5;
}

