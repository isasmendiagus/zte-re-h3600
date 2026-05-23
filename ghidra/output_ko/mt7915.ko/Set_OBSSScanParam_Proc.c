// module: mt7915.ko
// function: Set_OBSSScanParam_Proc @ 0x2b294
// size: 712 bytes
//

undefined4 Set_OBSSScanParam_Proc(int param_1,char *param_2)

{
  undefined2 uVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *local_24;
  
  iVar5 = 0;
  local_24 = param_2;
  do {
    pcVar2 = strsep(&local_24,"-");
    if (pcVar2 == (char *)0x0) {
      if (iVar5 == 7) {
        iVar4 = (uint)*(ushort *)(param_1 + 0x7956a2) * (uint)*(ushort *)(param_1 + 0x7956a8);
        iVar5 = DebugLevel;
      }
      else {
        if (-1 < DebugLevel) {
          printk("Wrong OBSSScanParamtetrs format in ioctl cmd!!!!! Use default value\n");
        }
        iVar5 = DebugLevel;
        iVar4 = 0x5dc;
        *(undefined2 *)(param_1 + 0x79569e) = 0x14;
        *(undefined2 *)(param_1 + 0x7956a0) = 10;
        *(undefined2 *)(param_1 + 0x7956a6) = 0x14;
        *(undefined2 *)(param_1 + 0x7956a2) = 300;
        *(undefined2 *)(param_1 + 0x7956a4) = 200;
        *(undefined2 *)(param_1 + 0x7956a8) = 5;
        *(undefined2 *)(param_1 + 0x7956aa) = 0x19;
      }
      *(int *)(param_1 + 0x7956ac) = iVar4;
      if (2 < iVar5) {
        printk("OBSSScanParam for Dot11BssWidthChanTranDelay=%ld\n");
      }
      return 1;
    }
    iVar3 = os_str_tol(pcVar2,0,10);
    iVar4 = DebugLevel;
    uVar1 = (undefined2)iVar3;
    switch(iVar5) {
    case 0:
      if (iVar3 - 5U < 0x3e4) {
        *(undefined2 *)(param_1 + 0x79569e) = uVar1;
        if (2 < iVar4) {
          printk("OBSSScanParam for Dot11OBssScanPassiveDwell=%d\n",iVar3);
        }
      }
      else if (-1 < DebugLevel) {
        printk("Invalid OBSSScanParam for Dot11OBssScanPassiveDwell(%d), should in range 5~1000\n",
               iVar3);
      }
      break;
    case 1:
      if (iVar3 - 10U < 0x3df) {
        *(undefined2 *)(param_1 + 0x7956a0) = uVar1;
        if (2 < iVar4) {
          printk("OBSSScanParam for Dot11OBssScanActiveDwell=%d\n",iVar3);
        }
      }
      else if (-1 < DebugLevel) {
        printk("Invalid OBSSScanParam for Dot11OBssScanActiveDwell(%d), should in range 10~1000\n",
               iVar3);
      }
      break;
    case 2:
      *(undefined2 *)(param_1 + 0x7956a2) = uVar1;
      if (2 < iVar4) {
        printk("OBSSScanParam for Dot11BssWidthTriggerScanInt=%d\n",iVar3);
      }
      break;
    case 3:
      if (iVar3 - 200U < 0x2649) {
        *(undefined2 *)(param_1 + 0x7956a4) = uVar1;
        if (2 < iVar4) {
          printk("OBSSScanParam for Dot11OBssScanPassiveTotalPerChannel=%d\n",iVar3);
        }
      }
      else if (-1 < DebugLevel) {
        printk("Invalid OBSSScanParam for Dot11OBssScanPassiveTotalPerChannel(%d), should in range 200~10000\n"
               ,iVar3);
      }
      break;
    case 4:
      if (iVar3 - 0x14U < 0x26fd) {
        *(undefined2 *)(param_1 + 0x7956a6) = uVar1;
        if (2 < iVar4) {
          printk("OBSSScanParam for Dot11OBssScanActiveTotalPerChannel=%d\n",iVar3);
        }
      }
      else if (-1 < DebugLevel) {
        printk("Invalid OBSSScanParam for Dot11OBssScanActiveTotalPerChannel(%d), should in range 20~10000\n"
               ,iVar3);
      }
      break;
    case 5:
      *(undefined2 *)(param_1 + 0x7956a8) = uVar1;
      goto joined_r0x0002b31c;
    case 6:
      *(undefined2 *)(param_1 + 0x7956aa) = uVar1;
joined_r0x0002b31c:
      if (2 < iVar4) {
        printk("OBSSScanParam for Dot11BssWidthChanTranDelayFactor=%d\n",iVar3);
      }
    }
    iVar5 = iVar5 + 1;
  } while( true );
}

