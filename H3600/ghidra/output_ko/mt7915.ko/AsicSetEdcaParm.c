// module: mt7915.ko
// function: AsicSetEdcaParm @ 0x132c7c
// size: 1284 bytes
//

void AsicSetEdcaParm(int param_1,undefined1 *param_2,int param_3)

{
  byte bVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined1 *__src;
  int *piVar10;
  void *__dest;
  undefined4 local_5d;
  undefined2 local_59;
  undefined1 local_57;
  undefined4 local_56;
  undefined4 local_52;
  undefined1 local_4e;
  undefined4 local_4d;
  undefined4 local_49;
  undefined2 local_45;
  undefined1 local_43;
  undefined4 local_42;
  undefined4 local_3e;
  undefined2 local_3a;
  undefined1 local_38;
  undefined4 local_37;
  undefined4 local_33;
  undefined4 local_2f;
  undefined2 local_2b;
  undefined1 local_29;
  
  bVar1 = *(byte *)(param_3 + 0x8d7);
  iVar7 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar8 = GetStaCfgByWdev(param_1,param_3);
  if (3 < bVar1) {
    if (-1 < DebugLevel) {
      printk("%s(): EdcaIdx >= 4\n","AsicSetEdcaParm");
      return;
    }
    return;
  }
  __src = param_2 + 4;
  __dest = (void *)(param_1 + (uint)bVar1 * 0x24 + 0x795084);
  if ((__src == (undefined1 *)0x0) || (param_2[4] == '\0')) {
    if (2 < DebugLevel) {
      printk("%s(): NoEDCAParam\n","AsicSetEdcaParm");
    }
    piVar10 = (int *)(param_1 + 0xa1d28);
    *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) & 0xfffffeff;
    iVar8 = 0;
    while( true ) {
      iVar9 = HcGetMaxStaNum(param_1);
      if (iVar9 <= iVar8) break;
      if ((piVar10[-2] == 2 || (piVar10[-2] - 0x20001U & 0xfffdffff) == 0) && (*piVar10 == param_3))
      {
        piVar10[0x2b] = piVar10[0x2b] & 0xfffffffe;
      }
      piVar10 = piVar10 + 0x530;
      iVar8 = iVar8 + 1;
    }
    os_zero_mem(__dest,0x24);
    goto LAB_00132d9c;
  }
  *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) | 0x100;
  os_move_mem(__dest,__src,0x24);
  if ((((((*(uint *)(param_1 + 0x795124) & 2) == 0) && (2 < DebugLevel)) &&
       (printk("EDCA [#%d]: AIFSN CWmin CWmax  TXOP(us)  ACM, WMM Set: %d, BandIdx: %d\n",
               param_2[10],param_2[3],*param_2), 2 < DebugLevel)) &&
      ((printk("     AC_BE      %2d     %2d     %2d      %4d     %d\n",param_2[0xb],param_2[0xf],
               param_2[0x13],(uint)*(ushort *)(param_2 + 0x18) << 5,param_2[0x20]), 2 < DebugLevel
       && (printk("     AC_BK      %2d     %2d     %2d      %4d     %d\n",param_2[0xc],param_2[0x10]
                  ,param_2[0x14],(uint)*(ushort *)(param_2 + 0x1a) << 5,param_2[0x21]),
          2 < DebugLevel)))) &&
     (printk("     AC_VI      %2d     %2d     %2d      %4d     %d\n",param_2[0xd],param_2[0x11],
             param_2[0x15],(uint)*(ushort *)(param_2 + 0x1c) << 5,param_2[0x22]), 2 < DebugLevel)) {
    printk("     AC_VO      %2d     %2d     %2d      %4d     %d\n",param_2[0xe],param_2[0x12],
           param_2[0x16],(uint)*(ushort *)(param_2 + 0x1e) << 5,param_2[0x23]);
  }
  if ((iVar8 == 0 || *(char *)(param_1 + 0xa7cc54) == '\0') || (*(int *)(param_3 + 0x14) != 2))
  goto LAB_00132d9c;
  local_56 = 0x2a286742;
  local_52 = 0x38374a5e;
  local_4d = 0x2d315041;
  local_49 = 0x2e322e35;
  local_4e = 0;
  local_37 = 0x2d544856;
  local_33 = 0x2e322e35;
  local_2f = 0x412d3136;
  local_45 = 0x3334;
  local_42 = 0x2d544856;
  local_2b = 0x3150;
  local_29 = 0;
  local_43 = 0;
  local_3e = 0x2e322e35;
  local_3a = 0x3832;
  cVar2 = *(char *)(iVar8 + 0x213302);
  local_38 = 0;
  local_5d = 0x2e322e35;
  local_59 = 0x3333;
  local_57 = 0;
  if (cVar2 == '\b') {
    iVar8 = memcmp((void *)(iVar8 + 0x2132e2),&local_56,8);
    bVar6 = false;
    bVar5 = iVar8 == 0;
LAB_00133024:
    bVar3 = false;
    if (bVar5) {
LAB_00132f60:
      if (param_2[0xf] == '\x04') {
        param_2[0xf] = 5;
      }
    }
  }
  else if (cVar2 == '\n') {
    iVar9 = memcmp((void *)(iVar8 + 0x2132e2),&local_4d,10);
    iVar8 = memcmp((void *)(iVar8 + 0x2132e2),&local_42,10);
    bVar3 = iVar8 == 0;
    bVar6 = false;
    if (iVar9 == 0) {
      bVar6 = false;
      goto LAB_00132f60;
    }
  }
  else {
    if (cVar2 == '\x0e') {
      iVar8 = memcmp((void *)(iVar8 + 0x2132e2),&local_37,0xe);
      bVar4 = iVar8 == 0;
    }
    else {
      bVar5 = false;
      bVar4 = false;
      if (cVar2 == '\x06') {
        iVar8 = memcmp((void *)(iVar8 + 0x2132e2),&local_5d,6);
        bVar6 = iVar8 == 0;
        goto LAB_00133024;
      }
    }
    bVar3 = false;
    bVar6 = bVar3;
    if (bVar4) {
      param_2[0xb] = 7;
      param_2[0xf] = param_2[0xf] + '\x02';
      bVar6 = false;
    }
  }
  if ((bVar6 || bVar3) && (param_2[0x11] == '\x03')) {
    param_2[0x11] = 4;
    param_2[0x15] = param_2[0x15] + '\x01';
  }
LAB_00132d9c:
  vow_update_om_wmm(param_1,param_3,param_2[3],__src);
  if (*(code **)(iVar7 + 0x90) == (code *)0x0) {
    AsicNotSupportFunc(param_1,"AsicSetEdcaParm");
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00132dd4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar7 + 0x90))(param_1,param_2[3],param_2[2],__src);
  return;
}

