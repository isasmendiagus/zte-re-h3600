// module: mt7915.ko
// function: SendSCSDataProc_CONNAC3 @ 0xbe41c
// size: 852 bytes
//

undefined4 SendSCSDataProc_CONNAC3(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  undefined4 local_48;
  undefined1 local_44;
  undefined1 local_43;
  undefined2 local_42;
  undefined1 local_40;
  undefined1 local_3f;
  char local_3e;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  uVar5 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_48 = 0;
  if (param_1 != -0xa7c240) {
    iVar4 = param_1 + 0xa7c000;
    iVar2 = iVar4 + param_2;
    if (*(char *)(iVar2 + 0x241) == '\x01') {
      iVar3 = param_1 + param_2 * 4;
      if ((uint)(*(int *)(iVar3 + 0xa7c250) * 9) < *(uint *)(iVar3 + 0xa7c258)) {
        *(undefined1 *)(iVar2 + 0x2dc) = 1;
        local_40 = 1;
        local_3f = 1;
        uVar7 = uVar5;
      }
      else {
        uVar7 = 0;
        for (uVar8 = 1; uVar1 = HcGetMaxStaNum(param_1), uVar8 < uVar1; uVar8 = uVar8 + 1 & 0xffff)
        {
          iVar2 = uVar8 * 0x14c0 + param_1;
          if ((*(int *)(iVar2 + 0xa1d28) != 0) && (iVar3 = HcGetBandByWdev(), iVar3 == param_2)) {
            iVar3 = *(int *)(iVar2 + 0xa1d20);
            if (iVar3 == 0x20001) {
              if (*(int *)(iVar2 + 0xa1e1c) == 2) goto LAB_000be614;
            }
            else {
              uVar1 = (uint)(iVar3 << 0x1d) >> 0x1f;
              if (iVar3 == 0x4001) {
                uVar1 = 1;
              }
              if (uVar1 != 0) {
LAB_000be614:
                iVar2 = uVar8 * 0x14c0 + param_1;
                uVar1 = *(int *)(iVar2 + 0xa307c) + *(int *)(iVar2 + 0xa3078);
                if (uVar1 < 0x3d091) {
                  if (uVar5 == 1) {
                    if (*(ushort *)(iVar4 + param_2 * 2 + 0x2e2) == uVar8) goto LAB_000be6d8;
                    goto LAB_000be6a4;
                  }
                }
                else {
                  uVar5 = uVar5 + 1 & 0xff;
                  *(short *)(iVar4 + param_2 * 2 + 0x2e2) = (short)uVar8;
                  if (uVar5 == 1) {
LAB_000be6d8:
                    uVar7 = uVar1 >> 0x11;
                    *(undefined1 *)(iVar4 + param_2 + 0x2dc) = 0;
LAB_000be6a4:
                    uVar5 = 1;
                    goto LAB_000be5a0;
                  }
                }
                iVar2 = DebugLevel;
                *(undefined1 *)(iVar4 + param_2 + 0x2dc) = 1;
                if (iVar2 < 4) {
                  uVar7 = 0;
                }
                else {
                  uVar7 = 0;
                  printk("Band%u:  Wcid %u, ActiveSTA %u, eTput %u\n",param_2,uVar8,uVar5,0);
                }
              }
            }
          }
LAB_000be5a0:
        }
        local_40 = 0;
        local_3f = *(undefined1 *)(iVar4 + param_2 + 0x2dc);
      }
    }
    else {
      local_3f = *(undefined1 *)(iVar2 + 0x2dc);
      local_40 = 0;
      uVar7 = 0;
    }
    local_44 = (undefined1)param_2;
    local_3e = *(char *)(iVar4 + param_2 + 0x245);
    local_43 = (undefined1)uVar5;
    local_42 = (undefined2)uVar7;
    if (3 < DebugLevel) {
      iVar2 = param_1 + param_2 * 4;
      printk("[CMD to FW] Band%u: ActiveSTA %u, eTput %u, fgRxOnly %u, PDreset %u, SCSMinRssi %d, OneSecTxByteCount %u, OneSecRxByteCount %u\n"
             ,param_2,uVar5,uVar7,local_40,local_3f,(int)local_3e,*(undefined4 *)(iVar2 + 0xa7c250),
             *(undefined4 *)(iVar2 + 0xa7c258));
    }
    iVar2 = AndesAllocCmdMsg(param_1,0xc);
    if (iVar2 != 0) {
      local_3c = CONCAT13(0x82,CONCAT12(0xed,(undefined2)local_3c));
      local_38 = CONCAT31(local_38._1_3_,10);
      uVar6 = 1;
      AndesInitCmdMsg(iVar2,local_3c,local_38,local_34,local_30,local_2c);
      AndesAppendCmdMsg(iVar2,&local_48,4);
      AndesAppendCmdMsg(iVar2,&local_44,8);
      AndesSendCmdMsg(param_1,iVar2);
      goto LAB_000be52c;
    }
  }
  uVar6 = 0;
LAB_000be52c:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SendSCSDataProc_CONNAC3",uVar6);
  }
  return uVar6;
}

