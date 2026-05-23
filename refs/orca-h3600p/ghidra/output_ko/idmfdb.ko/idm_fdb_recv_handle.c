// module: idmfdb.ko
// function: idm_fdb_recv_handle @ 0x10000
// size: 400 bytes
//

undefined4 idm_fdb_recv_handle(char *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_2 == 0 || param_1 == (char *)0x0) {
    return 0xffffffff;
  }
  iVar1 = ffe_get_npu_enable();
  if (iVar1 != 0) {
    *(char *)(param_2 + 0xbf) = param_1[3];
    uVar4 = *(uint *)(param_1 + 0xa8);
    uVar3 = *(uint *)(param_1 + 0xb0);
    *(uint *)(param_1 + 0xa8) = uVar4 + 1;
    *(uint *)(param_1 + 0xac) = *(int *)(param_1 + 0xac) + (uint)(0xfffffffe < uVar4);
    uVar4 = *(uint *)(param_2 + 100);
    *(uint *)(param_1 + 0xb0) = uVar3 + uVar4;
    *(uint *)(param_1 + 0xb4) = *(int *)(param_1 + 0xb4) + (uint)CARRY4(uVar3,uVar4);
    uVar4 = ifd_debug;
    if (((*param_1 != '\0') && (*(int *)(param_1 + 0x10) != 0)) && (*(int *)(param_1 + 8) == 0)) {
      *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(param_1 + 0x14);
      if ((uVar4 & 0x11) == 0x11) {
        printk("%s:from dev:%s, would forward to %s\n","wlan_recv_idm_handle",
               *(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x10));
        printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%u\nskb->cloned:\t%d\nref:\t%d\n",
               *(undefined4 *)(param_2 + 0xd0),*(undefined4 *)(param_2 + 0xd4),
               *(undefined2 *)(param_2 + 0xb2),*(byte *)(param_2 + 0x72) & 1,
               *(undefined4 *)(*(int *)(param_2 + 0xcc) + 0x20));
        if (*(int *)(param_2 + 100) != 0) {
          printk("%02x ",**(undefined1 **)(param_2 + 0xd4));
          uVar4 = 0;
          while (uVar4 = uVar4 + 1, uVar4 < *(uint *)(param_2 + 100)) {
            printk("%02x ",*(undefined1 *)(*(int *)(param_2 + 0xd4) + uVar4));
            uVar3 = uVar4 & 0x8000000f;
            if ((int)uVar3 < 0) {
              uVar3 = ~(~((uVar3 - 1) * 0x10000000) >> 0x1c) + 1;
            }
            if (uVar3 == 0xf) {
              printk(&_LC14);
            }
          }
        }
        printk(&_LC14);
      }
                    /* WARNING: Could not recover jumptable at 0x000100b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 300) + 0x10))(param_2);
      return uVar2;
    }
  }
  return 0xffffffff;
}

