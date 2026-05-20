// module: mt7915.ko
// function: RssiUpdate @ 0x135774
// size: 492 bytes
//

void RssiUpdate(int param_1)

{
  ushort *puVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int local_30;
  undefined1 auStack_2c [4];
  undefined1 auStack_28 [12];
  
  if (*(short *)(param_1 + 0x285920) == 0) {
    return;
  }
  __memzero(auStack_28);
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    os_alloc_mem(param_1,&local_30,0x78);
    if (local_30 != 0) {
      uVar2 = 0;
      __memzero(local_30,0x78);
      uVar7 = 0;
      while( true ) {
        uVar6 = uVar2 & 0xffff;
        uVar4 = HcGetMaxStaNum(param_1);
        if (uVar4 <= uVar6) break;
        if ((param_1 + uVar6 * 0x14c0 + 0xa1d20 != 0) &&
           (iVar3 = param_1 + uVar6 * 0x14c0, *(int *)(iVar3 + 0xa1d20) != 0)) {
          iVar5 = uVar7 * 6;
          uVar7 = uVar7 + 1 & 0xffff;
          *(undefined2 *)(local_30 + iVar5) = *(undefined2 *)(iVar3 + 0xa1e00);
        }
        if (uVar7 == 0x14) {
LAB_001358f8:
          iVar3 = 0;
          MtCmdMultiRssi(param_1,local_30,uVar7);
          uVar4 = 0;
          do {
            uVar4 = uVar4 + 1;
            iVar5 = local_30 + iVar3;
            puVar1 = (ushort *)(local_30 + iVar3);
            iVar3 = iVar3 + 6;
            FUN_00131a14(param_1,(uint)*puVar1 * 0x14c0 + param_1 + 0xa1d20,iVar5 + 2,auStack_28);
          } while ((uVar4 & 0xffff) < uVar7);
LAB_0013594c:
          uVar7 = 0;
        }
        else {
          iVar3 = HcGetMaxStaNum(param_1);
          if (uVar6 == iVar3 - 1U) {
            if (uVar7 != 0) goto LAB_001358f8;
            goto LAB_0013594c;
          }
        }
        uVar2 = uVar2 + 1;
      }
      os_free_mem(local_30);
    }
  }
  else {
    uVar7 = 0;
    while( true ) {
      uVar2 = HcGetMaxStaNum(param_1);
      uVar4 = uVar7 & 0xffff;
      uVar7 = uVar7 + 1;
      iVar3 = uVar4 * 0x14c0;
      iVar5 = param_1 + iVar3;
      if (uVar2 <= uVar4) break;
      iVar3 = param_1 + iVar3 + 0xa1d20;
      if ((iVar3 != 0) && (*(int *)(iVar5 + 0xa1d20) != 0)) {
        chip_get_rssi(param_1,*(undefined2 *)(iVar5 + 0xa1e00),auStack_2c);
        FUN_00131a14(param_1,iVar3,local_30 + 2,auStack_28);
      }
    }
  }
  return;
}

