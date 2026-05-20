// module: mt7915.ko
// function: WPAConstructEapolKeyData @ 0x11cf5c
// size: 1028 bytes
//

void WPAConstructEapolKeyData
               (int param_1,uint param_2,int param_3,uint *param_4,int param_5,int param_6)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  size_t sVar7;
  void *__src;
  void *__src_00;
  int iVar8;
  bool bVar9;
  int local_34;
  size_t local_30;
  size_t local_2c [2];
  
  if (param_2 == 1 || (param_2 & 0xfd) == 4) {
    return;
  }
  bVar9 = (*param_4 & 0x18) == 0;
  os_alloc_mem(0,&local_34,0x5dc);
  if (local_34 == 0) {
    return;
  }
  if ((*param_4 & 0x30000) == 0) {
    if ((char)param_4[0xa1] == '\x02') {
      iVar8 = 0x18;
    }
    else {
      iVar8 = 0x10;
    }
  }
  else {
    iVar8 = 0x18;
  }
  __src_00 = (void *)(local_34 + 3U & 0xfffffffc);
  __src = (void *)((int)__src_00 + 0x200);
  iVar4 = param_6 + iVar8 + 0x48;
  __memzero(__src,0x200);
  uVar5 = 0;
  *(undefined1 *)(param_6 + iVar8 + 0x51) = 0;
  *(undefined1 *)(iVar4 + 10) = 0;
  local_30 = 0;
  if (param_2 - 2 < 2) {
    if (bVar9) {
      iVar3 = 2;
    }
    else {
      iVar3 = 1;
    }
    if (*(int *)(param_5 + 0x598) == iVar3) {
LAB_0011d324:
      iVar3 = param_5 + uVar5 * 0xff + 0x5a4;
      uVar5 = (uint)*(byte *)(param_5 + uVar5 + 0x5a2);
    }
    else {
      if (*(int *)(param_5 + 0x59c) == iVar3) {
        uVar5 = 1;
        goto LAB_0011d324;
      }
      iVar3 = 0;
    }
    WPAInsertRSNIE(__src,&local_30,iVar3,uVar5,0,0);
  }
  sVar7 = local_30;
  if (param_2 != 5 && (param_2 != 3 || !bVar9)) {
    memmove((void *)(iVar4 + 0xb),__src,local_30);
    goto LAB_0011d050;
  }
  uVar5 = *(uint *)(param_5 + 0x228);
  if ((uVar5 & 0x10) == 0) {
    if ((uVar5 & 0x20) == 0) {
      if ((uVar5 & 0x40) != 0) goto LAB_0011d204;
      if ((uVar5 & 0x80) != 0) goto LAB_0011d0c4;
      if ((uVar5 & 0x100) != 0) goto LAB_0011d204;
      sVar7 = 0;
    }
    else {
LAB_0011d0c4:
      sVar7 = 0x10;
    }
  }
  else {
LAB_0011d204:
    sVar7 = 0x20;
  }
  if (bVar9) {
    WPAConstructKdeHdr(1,sVar7 + 2,(int)__src + local_30);
    *(byte *)((int)__src + local_30 + 6) = *(byte *)(param_5 + 0x22c) & 3;
    *(undefined1 *)((int)__src + local_30 + 7) = 0;
    local_30 = local_30 + 8;
    memmove((void *)((int)__src + local_30),(void *)(param_5 + 0x24d),sVar7);
    local_30 = sVar7 + local_30;
    if (*(char *)(param_1 + 0x562) == '\x01') {
      if (1 < DebugLevel) {
        printk("[PMF]:%s - Insert IGTK\n","WPAConstructEapolKeyData");
      }
      PMF_InsertIGTKKDE(*(undefined4 *)(param_1 + 0xc),*(undefined1 *)(param_1 + 0xe4),
                        (int)__src + local_30,&local_30);
    }
  }
  else {
    memmove((void *)((int)__src + local_30),(void *)(param_5 + 0x24d),sVar7);
    local_30 = sVar7 + local_30;
  }
  if (param_3 == 2 || (param_3 == 0 || param_3 == 3)) {
    local_2c[0] = 0;
    if (((*param_4 & 0x30000) == 0) && ((char)param_4[0xa1] != '\x02')) {
      uVar6 = 0x10;
      iVar3 = 0x10;
    }
    else {
      uVar6 = 0x20;
      iVar3 = 0x18;
    }
    if ((local_30 & 7) != 0) {
      *(undefined1 *)((int)__src + local_30) = 0xdd;
      uVar5 = 8 - (local_30 & 7) & 0xff;
      if (uVar5 != 1) {
        uVar1 = 1;
        do {
          uVar2 = uVar1 + 1;
          *(undefined1 *)((int)__src + local_30 + uVar1) = 0;
          uVar1 = uVar2;
        } while (uVar2 != uVar5);
      }
      local_30 = uVar5 + local_30;
    }
    AES_Key_Wrap(__src,local_30,(int)param_4 + iVar3 + 0x1ce,uVar6,__src_00,local_2c);
    local_30 = local_2c[0];
  }
  else {
    TKIP_GTK_KEY_WRAP((int)param_4 + 0x1de,param_6 + 0x31,__src,local_30,__src_00);
  }
  sVar7 = local_30;
  memmove((void *)(iVar4 + 0xb),__src_00,local_30);
LAB_0011d050:
  *(char *)(param_6 + iVar8 + 0x51) = (char)((sVar7 & 0xffff) >> 8);
  *(char *)(iVar4 + 10) = (char)sVar7;
  uVar5 = (sVar7 & 0xffff) +
          (uint)CONCAT11(*(undefined1 *)(param_6 + 2),*(undefined1 *)(param_6 + 3)) & 0xffff;
  *(char *)(param_6 + 3) = (char)uVar5;
  *(char *)(param_6 + 2) = (char)(uVar5 >> 8);
  os_free_mem(local_34);
  return;
}

