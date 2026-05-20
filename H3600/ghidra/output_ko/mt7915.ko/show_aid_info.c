// module: mt7915.ko
// function: show_aid_info @ 0x14bec0
// size: 448 bytes
//

undefined4 show_aid_info(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  if (((param_2 != (char *)0x0) && (*param_2 != 0)) &&
     (iVar2 = simple_strtol(param_2,0,10,(int)*param_2,param_4), 0x7d6 < iVar2 - 1U)) {
    if (0 < DebugLevel) {
      printk("wrong AID input\n");
      return 0;
    }
    return 0;
  }
  iVar2 = *(int *)(param_1 + 0x28594c);
  if (iVar2 == 0) {
    if (-1 < DebugLevel) {
      printk("no aid_bitmap\n");
      return 1;
    }
  }
  else {
    uVar4 = 0;
    iVar1 = DebugLevel;
    while( true ) {
      uVar3 = *(uint *)(iVar2 + (uVar4 >> 5) * 4);
      if (uVar3 == 0) {
        uVar4 = uVar4 + 0x20 & 0xffff;
      }
      else {
        uVar5 = uVar4 & 0x1f;
        if (uVar5 == 0) {
          if (-1 < iVar1) {
            uVar3 = 0x7d7;
            if (uVar4 + 0x1f < 0x7d9) {
              uVar3 = uVar4 + 0x1f;
            }
            printk("BIT:%d - BIT:%d:\t\t",uVar4,uVar3);
            iVar1 = DebugLevel;
            if (-1 < DebugLevel) {
              printk(&_LC72,*(uint *)(*(int *)(param_1 + 0x28594c) + (uVar4 >> 5) * 4) & 1);
              iVar1 = DebugLevel;
            }
          }
        }
        else if (((-1 < iVar1) &&
                 (printk(&_LC72,(uVar3 & 1 << uVar5) >> uVar5), iVar1 = DebugLevel, uVar5 == 0x1f))
                && (-1 < DebugLevel)) {
          printk(&_LC73);
          iVar1 = DebugLevel;
        }
      }
      uVar4 = uVar4 + 1 & 0xffff;
      if (*(ushort *)(param_1 + 0x285952) < uVar4) break;
      iVar2 = *(int *)(param_1 + 0x28594c);
    }
    if (-1 < iVar1) {
      printk(&_LC73);
    }
  }
  return 1;
}

