// module: mt7915.ko
// function: RTMPRepeaterReconnectionCheck @ 0x824a0
// size: 692 bytes
//

void RTMPRepeaterReconnectionCheck(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 extraout_r1;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  void *__s2;
  byte *pbVar8;
  int *piVar9;
  int iVar10;
  undefined4 *puVar11;
  uint auStack_54 [3];
  undefined1 auStack_48 [36];
  
  if ((&DAT_0036790d)[param_1] == '\0') {
    return;
  }
  if ((&DAT_00367910)[param_1] != '\x02') {
    return;
  }
  __s2 = (void *)(param_1 + 0x580e3a);
  piVar9 = (int *)(param_1 + 0x367904);
  pbVar8 = &DAT_003678fd + param_1;
  iVar10 = 0;
  while( true ) {
    if (*(char *)((int)__s2 + -0x21283a) != '\0') {
      puVar11 = (undefined4 *)((int)__s2 + -0x2132e2);
      iVar1 = get_scan_ctrl_by_wdev(param_1,puVar11);
      iVar2 = RtmpOSNetDevIsUp(*puVar11);
      if (((iVar2 == 1) && (*(char *)((int)__s2 + 0x53) != '\0')) &&
         (*(char *)(iVar1 + 0x17c) != '\x01')) {
        if (3 < DebugLevel) {
          uVar4 = scan_in_run_state(param_1,puVar11);
          uVar3 = (uint)*(byte *)((int)__s2 + 0xae);
          uVar5 = *(undefined4 *)((int)__s2 + 0xaa);
          uVar6 = (uint)*pbVar8;
          __aeabi_uidivmod(*(undefined4 *)(param_1 + 0x82921c),0x17);
          printk(" %s(): i=%d,%d,%d,%d,%d,%d\n","RTMPRepeaterReconnectionCheck",iVar10,uVar4,uVar3,
                 uVar5,uVar6,extraout_r1);
        }
        iVar2 = scan_in_run_state(param_1,puVar11);
        if (((iVar2 == 0) && (*(char *)((int)__s2 + 0xae) == '\0')) &&
           (*(char *)((int)__s2 + 0x74) != '\0')) {
          uVar6 = (uint)*(byte *)((int)__s2 + 0x20);
          iVar2 = GetAssociatedAPByWdev(param_1,puVar11);
          if (((iVar2 == 0) ||
              ((uVar6 < 0x21 &&
               (iVar2 = memcmp((void *)((int)__s2 + -0xedc),__s2,uVar6), iVar2 != 0)))) &&
             (*(char *)((int)__s2 + 0x20) != '\0')) {
            uVar3 = *piVar9 - *(int *)(param_1 + 0x7960e8);
            if ((int)uVar3 < 0) {
              auStack_54[iVar10] = *(int *)(param_1 + 0x7960e8) - *piVar9;
            }
            else {
              auStack_54[iVar10] = uVar3;
            }
            uVar7 = auStack_54[iVar10];
            uVar3 = RTMPMsecsToJiffies(23000);
            if (uVar3 < uVar7) {
              if (-1 < DebugLevel) {
                uVar4 = GetAssociatedAPByWdev(param_1,puVar11);
                printk(" %s(): Scan channels for AP (%s), pApEntry(%p)\n",
                       "RTMPRepeaterReconnectionCheck",__s2,uVar4);
              }
              *(undefined1 *)((int)__s2 + 0xae) = 1;
              if (*pbVar8 != 0) {
                pbVar8[2] = 1;
                *(undefined1 *)(iVar1 + 0x17c) = 1;
                *(undefined4 **)(iVar1 + 0x1bc) = puVar11;
              }
              auStack_54[2] = uVar6;
              memcpy(auStack_48,__s2,uVar6);
              *piVar9 = jiffies;
              ApSiteSurvey_by_wdev(param_1,auStack_54 + 2,0,0,puVar11);
            }
          }
        }
      }
    }
    piVar9 = piVar9 + 1;
    __s2 = (void *)((int)__s2 + 0x2137b0);
    pbVar8 = pbVar8 + 1;
    if (iVar10 == 1) break;
    iVar10 = 1;
  }
  return;
}

