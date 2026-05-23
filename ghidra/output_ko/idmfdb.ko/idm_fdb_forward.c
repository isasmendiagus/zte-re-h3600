// module: idmfdb.ko
// function: idm_fdb_forward @ 0x10190
// size: 608 bytes
//

undefined4 idm_fdb_forward(uint param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  undefined1 *in_r12;
  
  if (param_2 == 0) {
    return 0xffffffff;
  }
  if (param_1 < 2) {
    uVar2 = (uint)*(byte *)(param_2 + 0xb7);
    bVar3 = **(byte **)(param_2 + 0xcc);
    uVar1 = bVar3 & 1;
    if ((bVar3 & 1) == 0) {
      if (uVar2 < 8) {
        iVar4 = uVar2 + param_1 * 8;
        in_r12 = &fdb_list + iVar4 * 0x128;
        iVar5 = (&DAT_0001341c)[iVar4 * 0x4a];
        if (iVar5 == 0) {
          bVar3 = 0;
        }
        else {
          bVar3 = (&fdb_list)[iVar4 * 0x128] & 1;
        }
        if ((bVar3 != 0) && ((*(uint *)(iVar5 + 0x30) & 1) != 0)) {
          *(int *)(param_2 + 0x18) = iVar5;
          if ((ifd_debug & 9) == 9) {
            printk("%s:from idm:%d ssid%d, send to %s\n","idm_fdb_forward",param_1,uVar2,
                   (&DAT_0001341c)[iVar4 * 0x4a]);
            printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%p\nskb->cloned:\t%d\nref:\t%d\n"
                   ,*(undefined4 *)(param_2 + 200),*(undefined4 *)(param_2 + 0xcc),
                   *(undefined2 *)(param_2 + 0xaa),*(byte *)(param_2 + 0x72) & 1,
                   *(undefined4 *)(*(int *)(param_2 + 0xc4) + 0x20));
            if (*(int *)(param_2 + 100) != 0) {
              printk("%02x ",**(undefined1 **)(param_2 + 0xcc));
              while (uVar1 = uVar1 + 1, uVar1 < *(uint *)(param_2 + 100)) {
                printk("%02x ",*(undefined1 *)(*(int *)(param_2 + 0xcc) + uVar1));
                if ((uVar1 & 0xf) == 0xf) {
                  printk(&_LC14);
                }
              }
            }
            printk(&_LC14);
          }
          iVar5 = (**(code **)(*(int *)(iVar5 + 300) + 0x10))(param_2,iVar5);
          if (iVar5 == 0) {
            iVar4 = iVar4 * 0x128;
            uVar1 = *(uint *)(&DAT_00013420 + iVar4);
            uVar2 = *(uint *)(&DAT_00013428 + iVar4);
            *(uint *)(&DAT_00013420 + iVar4) = uVar1 + 1;
            *(uint *)(&DAT_00013424 + iVar4) =
                 *(int *)(&DAT_00013424 + iVar4) + (uint)(0xfffffffe < uVar1);
            uVar1 = *(uint *)(param_2 + 100);
            *(uint *)(&DAT_00013428 + iVar4) = uVar2 + uVar1;
            *(uint *)(&DAT_0001342c + iVar4) =
                 *(int *)(&DAT_0001342c + iVar4) + (uint)CARRY4(uVar2,uVar1);
            return 0;
          }
          iVar4 = iVar4 * 0x128;
          uVar2 = *(uint *)(&DAT_000134c8 + iVar4);
          uVar1 = *(uint *)(&DAT_000134d0 + iVar4);
          *(uint *)(&DAT_000134c8 + iVar4) = uVar2 + 1;
          *(uint *)(&DAT_000134cc + iVar4) =
               *(int *)(&DAT_000134cc + iVar4) + (uint)(0xfffffffe < uVar2);
          uVar2 = *(uint *)(param_2 + 100);
          *(uint *)(&DAT_000134d0 + iVar4) = uVar1 + uVar2;
          *(uint *)(&DAT_000134d4 + iVar4) =
               *(int *)(&DAT_000134d4 + iVar4) + (uint)CARRY4(uVar1,uVar2);
          __dev_kfree_skb_any(param_2,1);
          return 0;
        }
        goto LAB_000101b0;
      }
    }
    else if (bVar3 == 0xff) {
      uVar1 = 2;
    }
    else {
      uVar1 = 1;
    }
    idm_fdb_multi_send_handle(param_1,uVar2,param_2,uVar1);
  }
  else {
LAB_000101b0:
    if (in_r12 != (undefined1 *)0x0) {
      uVar1 = *(uint *)(in_r12 + 0xc0);
      uVar2 = *(uint *)(in_r12 + 200);
      *(uint *)(in_r12 + 0xc0) = uVar1 + 1;
      *(uint *)(in_r12 + 0xc4) = *(int *)(in_r12 + 0xc4) + (uint)(0xfffffffe < uVar1);
      uVar1 = *(uint *)(param_2 + 100);
      *(uint *)(in_r12 + 200) = uVar2 + uVar1;
      *(uint *)(in_r12 + 0xcc) = *(int *)(in_r12 + 0xcc) + (uint)CARRY4(uVar2,uVar1);
    }
    __dev_kfree_skb_any(param_2,1);
  }
  return 0;
}

