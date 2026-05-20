// module: mt7915.ko
// function: HQA_SetStaRUSetting @ 0x279324
// size: 1036 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 HQA_SetStaRUSetting(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  int local_3c;
  uint local_38;
  int local_34;
  uint local_30 [3];
  
  local_34 = param_3 + 0xc;
  iVar13 = ((*(ushort *)(param_3 + 8) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 8) >> 8)) - 0xc;
  local_3c = 0;
  local_30[0] = 0;
  local_30[1] = 0;
  local_38 = 0;
  FUN_00276034(1,4,&local_34,&local_3c);
  FUN_00276034(1,4,&local_34,local_30);
  FUN_00276034(1,4,&local_34,local_30 + 1);
  uVar6 = local_30[0];
  if (0 < DebugLevel) {
    uVar10 = local_30[1];
    iVar2 = __aeabi_uidiv(iVar13,local_30[1] + local_30[0],DebugLevel,local_30[1],local_30[1]);
    printk("%s: Band:%d [ru_segment 0]:%d, [ru_segment 1]:%d, parameters count:%d\n",
           "HQA_SetStaRUSetting",local_3c,uVar6,uVar10,(uint)(iVar2 << 0x16) >> 0x18);
  }
  iVar2 = net_ad_wrap_service(param_1);
  uVar10 = 0;
  uVar6 = *(uint *)(local_3c * 0xd18 + iVar2 + 0x6dc);
  iVar3 = net_ad_wrap_service(param_1);
  iVar2 = local_3c * 0xd18;
  iVar4 = net_ad_wrap_service(param_1);
  iVar2 = iVar2 + iVar3 + 0x10dd;
  iVar3 = local_3c * 0xd18 + iVar4 + 0xa1c;
  os_zero_mem(iVar3,0x6c0);
  os_fill_mem(iVar2,8,0xff);
  while( true ) {
    if (local_30[uVar10] != 0) {
      uVar8 = 0;
      do {
        uVar5 = local_30[0];
        iVar4 = __aeabi_uidiv(iVar13,local_30[0] + local_30[1]);
        iVar9 = uVar5 * uVar10 + uVar8;
        uVar11 = (uint)(iVar4 << 0x16) >> 0x18;
        *(undefined1 *)(iVar3 + iVar9 * 0x6c) = 1;
        iVar4 = iVar3 + iVar9 * 0x6c;
        FUN_00276034(1,4,&local_34,&local_38);
        FUN_00276034(1,4,&local_34,&local_38);
        uVar5 = 0;
        uVar12 = 0;
        uVar8 = local_38;
        do {
          uVar7 = uVar8 & 1;
          uVar8 = uVar8 >> 4;
          uVar1 = uVar5 & 0xff;
          uVar5 = uVar5 + 1;
          uVar12 = uVar12 | uVar7 << uVar1 & 0xff;
        } while (uVar5 != 8);
        FUN_00276034(1,4,&local_34,&local_38);
        FUN_00276034(1,4,&local_34,&local_38);
        *(uint *)(iVar4 + 0xc) = uVar10 | local_38 << 1;
        mt_ate_add_allocation(iVar2,uVar12,uVar10);
        FUN_00276034(1,4,&local_34,&local_38);
        *(uint *)(iVar4 + 0x10) = local_38;
        FUN_00276034(1,4,&local_34,&local_38);
        *(uint *)(iVar4 + 0x14) = local_38;
        FUN_00276034(1,4,&local_34,&local_38);
        *(uint *)(iVar4 + 0x18) = local_38;
        FUN_00276034(1,4,&local_34,&local_38);
        *(uint *)(iVar4 + 0x1c) = local_38 - 1;
        FUN_00276034(1,4,&local_34,&local_38);
        uVar8 = local_38;
        if (local_38 < 0x19) {
          uVar8 = uVar6;
        }
        *(uint *)(iVar4 + 0x20) = uVar8;
        if (uVar11 != 9) {
          FUN_00276034(1,4,&local_34,&local_38);
          *(uint *)(iVar4 + 0x24) = local_38;
          if (uVar11 != 10) {
            FUN_00276034(1,4,&local_34,&local_38);
            *(uint *)(iVar4 + 0x28) = local_38;
          }
        }
        if (2 < DebugLevel) {
          printk("%s: ru_segment[%d][0x%x]: ru_idx:%d, rate:%x, ldpc:%d, nss:%d,\n\t\t\t\t start spatial stream:%d, mpdu length=%d, alpha:%d, ru_mu_nss=%d\n"
                 ,"HQA_SetStaRUSetting",uVar10,uVar12,*(uint *)(iVar4 + 0xc) >> 1,
                 *(undefined4 *)(iVar4 + 0x10),*(undefined4 *)(iVar4 + 0x14),
                 *(undefined4 *)(iVar4 + 0x18),*(undefined4 *)(iVar4 + 0x1c),
                 *(undefined4 *)(iVar4 + 0x20),*(undefined4 *)(iVar4 + 0x24),
                 *(undefined4 *)(iVar4 + 0x28));
        }
        uVar8 = iVar9 + 1;
      } while (uVar8 < local_30[uVar10]);
    }
    if (uVar10 == 1) break;
    uVar10 = 1;
  }
  iVar13 = 0;
  mt_ate_fill_empty_allocation(iVar2);
  do {
    if (0 < DebugLevel) {
      printk("%s: allocation[%d] = 0x%x\n","HQA_SetStaRUSetting",iVar13,
             *(undefined1 *)(iVar2 + iVar13));
    }
    iVar13 = iVar13 + 1;
  } while (iVar13 != 8);
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

