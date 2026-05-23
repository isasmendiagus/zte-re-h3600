// module: mt7915.ko
// function: TxBfFbRptDbgInfoPrint @ 0x87134
// size: 588 bytes
//

void TxBfFbRptDbgInfoPrint(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  undefined2 *puVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  bool bVar12;
  
  uVar1 = *param_2;
  iVar10 = param_2[6];
  uVar2 = param_2[1];
  iVar6 = param_2[5];
  uVar3 = param_2[2];
  iVar11 = param_2[7];
  iVar8 = param_2[8];
  uVar4 = param_2[3];
  if (0 < DebugLevel) {
    printk(&_LC32);
    if (0 < DebugLevel) {
      printk(&_LC33);
      if (0 < DebugLevel) {
        printk(&_LC34,param_2[6]);
        if (0 < DebugLevel) {
          printk(&_LC35,param_2[5]);
          if (0 < DebugLevel) {
            printk(&_LC36,param_2[4]);
            if (0 < DebugLevel) {
              printk(&_LC37,param_2[7]);
              if (0 < DebugLevel) {
                printk(&_LC38,param_2[8]);
                if (0 < DebugLevel) {
                  printk(&_LC39,iVar6 + iVar10 + iVar11 + iVar8);
                  if (0 < DebugLevel) {
                    printk(&_LC40,uVar2);
                    if (0 < DebugLevel) {
                      printk(&_LC41,uVar1);
                      if (0 < DebugLevel) {
                        printk(&_LC42,uVar3);
                        if (0 < DebugLevel) {
                          printk(&_LC43,uVar4);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  param_2 = param_2 + 9;
  uVar9 = 0;
  puVar7 = (undefined2 *)(param_1 + 0xa1e18);
  while( true ) {
    uVar5 = HcGetMaxStaNum(param_1);
    bVar12 = uVar5 <= uVar9;
    uVar9 = uVar9 + 1;
    if (bVar12) break;
    if ((*(int *)(puVar7 + -0x7c) != 0) && (0 < DebugLevel)) {
      printk(&_LC44,*puVar7,*param_2);
    }
    puVar7 = puVar7 + 0xa60;
    param_2 = param_2 + 1;
  }
  if (0 < DebugLevel) {
    printk(&_LC33);
    if (0 < DebugLevel) {
      printk(&_LC32);
      return;
    }
  }
  return;
}

