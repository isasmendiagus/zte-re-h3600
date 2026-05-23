// module: mt7915.ko
// function: TxBfPlyInfoPrint @ 0x87894
// size: 720 bytes
//

void TxBfPlyInfoPrint(int param_1,undefined1 *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined1 auStack_34 [4];
  undefined1 auStack_30 [4];
  undefined1 auStack_2c [8];
  
  if (0 < DebugLevel) {
    printk("============================= Global Setting ========================================\n"
          );
    if (0 < DebugLevel) {
      printk("GloOpt = 0x%02X, GrpIBfOpt = 0x%02X, GrpEBfOp = 0x%02X\n",*param_2,param_2[1],
             param_2[2]);
      if (0 < DebugLevel) {
        printk("============================= STA Info ========================================\n");
      }
    }
  }
  iVar3 = 1;
  do {
    if (0 < DebugLevel) {
      printk("AID%2u ",iVar3);
    }
    iVar5 = 0;
    do {
      iVar2 = iVar3 * 4 + iVar5;
      iVar5 = iVar5 + 1;
      TxBFPlyGetGrpStr(param_2[iVar2 + 4] & 0xf,auStack_34);
      TxBFPlyGetPlyStr((byte)param_2[iVar2 + 4] >> 4,auStack_30);
      if (0 < DebugLevel) {
        printk("Nss%2u Grp=%s, Ply=%s ",iVar5,auStack_34,auStack_30);
      }
    } while (iVar5 != 4);
    TxBFPlyGetPlyStr(param_2[iVar3 + 0x484],auStack_2c);
    if (0 < DebugLevel) {
      printk("Rlt=%s ",auStack_2c);
      if (0 < DebugLevel) {
        printk(&_LC32);
      }
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 5);
  if (0 < DebugLevel) {
    printk("============================= STA Info Connected ==============================\n");
  }
  uVar1 = HcGetMaxStaNum(param_1);
  uVar4 = 1;
  if (1 < uVar1) {
    do {
      iVar3 = uVar4 * 0x14c0 + param_1;
      if (*(int *)(iVar3 + 0xa1d20) != 0) {
        if (0 < DebugLevel) {
          printk("AID%2u ",*(undefined2 *)(iVar3 + 0xa1e18));
        }
        iVar3 = 0;
        do {
          iVar5 = uVar4 * 4 + iVar3;
          iVar3 = iVar3 + 1;
          TxBFPlyGetGrpStr(param_2[iVar5 + 4] & 0xf,auStack_34);
          TxBFPlyGetPlyStr((byte)param_2[iVar5 + 4] >> 4,auStack_30);
          if (0 < DebugLevel) {
            printk("Nss%2u Grp=%s, Ply=%s ",iVar3,auStack_34,auStack_30);
          }
        } while (iVar3 != 4);
        TxBFPlyGetPlyStr(param_2[uVar4 + 0x484],auStack_2c);
        if (0 < DebugLevel) {
          printk("Rlt=%s ",auStack_2c);
          if (0 < DebugLevel) {
            printk(&_LC32);
          }
        }
      }
      uVar1 = HcGetMaxStaNum(param_1);
      uVar4 = uVar4 + 1 & 0xffff;
    } while (uVar4 < uVar1);
  }
  if (0 < DebugLevel) {
    printk("=====================================================================================\n"
          );
  }
  return;
}

