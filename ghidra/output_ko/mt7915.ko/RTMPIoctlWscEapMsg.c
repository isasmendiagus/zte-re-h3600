// module: mt7915.ko
// function: RTMPIoctlWscEapMsg @ 0x3cc28
// size: 912 bytes
//

undefined4 RTMPIoctlWscEapMsg(int *param_1,int param_2)

{
  int *piVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  char *__haystack;
  undefined4 uVar8;
  int iVar9;
  uint local_48;
  uint local_44;
  int *local_40;
  uint local_3c;
  int local_38;
  int local_34;
  int *local_2c [2];
  
  iVar9 = *param_1;
  local_2c[0] = (int *)0x0;
  if (2 < DebugLevel) {
    printk("WSC::RT_OID_WSC_EAPMSG, wrq->u.data.length=%d, ioctl_if=%d\n",
           *(undefined2 *)(param_2 + 0x14),*(undefined4 *)(iVar9 + 0x3c));
  }
  uVar7 = (uint)*(ushort *)(param_2 + 0x14);
  os_alloc_mem(param_1,local_2c,uVar7);
  if (local_2c[0] == (int *)0x0) {
    uVar8 = 0xffffffea;
    goto LAB_0003cd38;
  }
  if (uVar7 == 0) {
    uVar3 = *(uint *)(param_2 + 0x10);
    uVar5 = *(uint *)(((uint)&local_48 & 0xffffe000) + 8);
    if (uVar3 <= uVar5) {
      uVar5 = 0;
    }
    if (uVar5 == 0) {
LAB_0003cdb8:
      __copy_from_user(local_2c[0],uVar3,uVar7);
    }
  }
  else {
    __memzero(local_2c[0],uVar7);
    uVar3 = *(uint *)(param_2 + 0x10);
    uVar6 = *(uint *)(((uint)&local_48 & 0xffffe000) + 8);
    uVar4 = uVar3 + uVar7;
    uVar5 = uVar4;
    if (!CARRY4(uVar3,uVar7)) {
      uVar5 = uVar4 - (uVar6 + 1);
    }
    if (!CARRY4(uVar3,uVar7) && uVar4 <= uVar6) {
      uVar6 = 0;
    }
    if (uVar6 == 0) goto LAB_0003cdb8;
    __memzero(local_2c[0],uVar7,uVar5);
  }
  piVar1 = local_2c[0];
  uVar5 = wdev_search_by_address(param_1,local_2c[0] + 1);
  if (uVar5 == 0) {
    if (-1 < DebugLevel) {
      local_48 = (uint)*(byte *)((int)piVar1 + 6);
      local_44 = (uint)*(byte *)((int)piVar1 + 7);
      local_40 = (int *)(uint)*(byte *)(piVar1 + 2);
      local_3c = (uint)*(byte *)((int)piVar1 + 9);
      printk("%s:: cannot find wdev by addr(%02x:%02x:%02x:%02x:%02x:%02x).\n","RTMPIoctlWscEapMsg",
             (char)piVar1[1],*(undefined1 *)((int)piVar1 + 5));
    }
    os_free_mem(local_2c[0]);
    return 0xffffffea;
  }
  uVar8 = *(undefined4 *)((int)piVar1 + 10);
  if (2 < DebugLevel) {
    printk("RT_OID_WSC_EAPMSG++++++++\n\n");
  }
  hex_dump("MAC::",piVar1 + 4,6);
  if (2 < DebugLevel) {
    printk("RT_OID_WSC_EAPMSG++++++++\n\n");
  }
  if ((*(char *)(uVar5 + 0x12ec) == '\x01') &&
     ((*(char *)(uVar5 + 0x3e14) != '\0' || (*(char *)(uVar5 + 0x3e15) == '\0')))) {
    __haystack = (char *)((int)local_2c[0] + 0x29);
    local_38 = uVar5 + 0x1000;
    local_34 = uVar5 + 0x3000;
    pcVar2 = strstr(__haystack,"SimpleConfig");
    if ((pcVar2 == (char *)0x0) ||
       ((*(char *)(local_38 + 0x1f36) != '\0' || (*(char *)(local_34 + 0xa70) != '\0')))) {
      uVar3 = uVar7 - 0x29 & 0xffff;
      iVar9 = WscRxMsgTypeFromUpnp(param_1,__haystack,uVar3);
      if ((iVar9 == 5) &&
         ((*(char *)(local_38 + 0x1f36) == '\0' && (*(char *)(local_34 + 0xa70) == '\0')))) {
        iVar9 = WscCheckEnrolleeNonceFromUpnp(param_1,__haystack,uVar3);
        if (iVar9 != 0) {
          WscGetConfWithoutTrigger(param_1,uVar5 + 0x12e4,1);
          *(undefined4 *)(local_38 + 0x2f4) = 0xd;
        }
      }
    }
    else {
      WscInit(param_1,0,*(undefined1 *)(iVar9 + 0x3c));
      *(undefined1 *)(local_38 + 0x6fc) = 1;
    }
  }
  local_48 = 0x24;
  local_44 = uVar7;
  local_40 = local_2c[0];
  local_3c = uVar5;
  iVar9 = MlmeEnqueueForWsc(param_1,*piVar1,uVar8,0x11);
  if ((iVar9 == 0) && (*piVar1 != 0)) {
    if (DebugLevel < 3) {
      uVar8 = 0xffffffea;
    }
    else {
      uVar8 = 0xffffffea;
      printk("MlmeEnqueuForWsc return False and envID=0x%x!\n");
    }
  }
  else {
    uVar8 = 0;
  }
  os_free_mem(local_2c[0]);
LAB_0003cd38:
  if (2 < DebugLevel) {
    printk("RT_OID_WSC_EAPMSG finished!\n");
  }
  return uVar8;
}

