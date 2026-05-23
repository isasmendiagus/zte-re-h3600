// module: idmfdb.ko
// function: idm_fdb_hook_xmit @ 0x103f4
// size: 308 bytes
//

void idm_fdb_hook_xmit(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  if ((*(ushort *)(param_1 + 0xbc) & 0x10) != 0) {
    return;
  }
  if ((ifd_debug & 1) != 0) {
    printk(&_LC17,"idm_fdb_hook_xmit");
    if (*(int *)(param_1 + 0x18) != 0) {
      printk("skb->dev->name:%s\n");
    }
    printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%p\nskb->cloned:\t%d\nref:\t%d\n",
           *(undefined4 *)(param_1 + 200),*(undefined4 *)(param_1 + 0xcc),
           *(undefined2 *)(param_1 + 0xaa),*(byte *)(param_1 + 0x72) & 1,
           *(undefined4 *)(*(int *)(param_1 + 0xc4) + 0x20));
    if (*(int *)(param_1 + 100) != 0) {
      uVar2 = 0;
      printk("%02x ",**(undefined1 **)(param_1 + 0xcc));
      while (uVar2 = uVar2 + 1, uVar2 < *(uint *)(param_1 + 100)) {
        printk("%02x ",*(undefined1 *)(*(int *)(param_1 + 0xcc) + uVar2));
        uVar1 = uVar2 & 0x8000000f;
        if ((int)uVar1 < 0) {
          uVar1 = ~(~((uVar1 - 1) * 0x10000000) >> 0x1c) + 1;
        }
        if (uVar1 == 0xf) {
          printk(&_LC14);
        }
      }
    }
    printk(&_LC14);
  }
  if (*(int *)(param_1 + 0x18) == 0) {
    return;
  }
  ffe_learn_skb(param_1,3);
  return;
}

