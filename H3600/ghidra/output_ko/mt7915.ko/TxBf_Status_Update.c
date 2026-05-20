// module: mt7915.ko
// function: TxBf_Status_Update @ 0x87f88
// size: 444 bytes
//

void TxBf_Status_Update(undefined4 param_1,undefined1 *param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *__src;
  int iVar3;
  size_t __n;
  uint uVar4;
  void *local_1c;
  
  iVar1 = net_ad_wrap_service();
  uVar4 = (uint)*(byte *)(iVar1 + 0x4cc);
  iVar1 = net_ad_wrap_service(param_1);
  iVar3 = uVar4 * 0xd18;
  local_1c = *(void **)(iVar1 + iVar3 + 0x11d0);
  iVar1 = net_ad_wrap_service(param_1);
  if ((*(uint *)(iVar1 + iVar3 + 0x4e0) & 0x400) != 0) {
    iVar1 = net_ad_wrap_service(param_1);
    *(undefined4 *)(iVar1 + iVar3 + 0x11d4) = 0;
    os_alloc_mem(param_1,&local_1c,param_3);
    if (local_1c == (void *)0x0) {
      uVar2 = 3;
    }
    else {
      os_zero_mem(local_1c,param_3);
      iVar1 = net_ad_wrap_service(param_1);
      __src = param_2 + 8;
      *(undefined4 *)(iVar1 + iVar3 + 0x11d4) = param_3;
      switch(*param_2) {
      case 0x10:
        if (param_2[4] == '\0') {
          __n = 0x10;
        }
        else {
          __n = 0x1c;
        }
        memmove(local_1c,__src,__n);
        iVar1 = net_ad_wrap_service(param_1);
        uVar2 = 0;
        *(size_t *)(uVar4 * 0xd18 + iVar1 + 0x11d4) = __n;
        break;
      case 0x11:
        memmove(local_1c,__src,0x14);
        iVar1 = net_ad_wrap_service(param_1);
        uVar2 = 0;
        *(undefined4 *)(uVar4 * 0xd18 + iVar1 + 0x11d4) = 0x14;
        break;
      default:
        uVar2 = 0;
        break;
      case 0x15:
        iVar1 = net_ad_wrap_service(param_1);
        uVar2 = 0;
        *(undefined1 *)(uVar4 * 0xd18 + iVar1 + 0x11d8) = param_2[4];
        break;
      case 0x16:
        memmove(local_1c,__src,0x38);
        iVar1 = net_ad_wrap_service(param_1);
        uVar2 = 0;
        *(undefined4 *)(uVar4 * 0xd18 + iVar1 + 0x11d4) = 0x38;
      }
    }
    if (2 < DebugLevel) {
      printk("%s(%x)\n","TxBf_Status_Update",uVar2);
    }
  }
  return;
}

