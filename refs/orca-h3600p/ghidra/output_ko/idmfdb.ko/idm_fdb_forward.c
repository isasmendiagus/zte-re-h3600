// module: idmfdb.ko
// function: idm_fdb_forward @ 0x10190
// size: 628 bytes
//

undefined4 idm_fdb_forward(uint param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  if (param_2 == 0) {
    return 0xffffffff;
  }
  if (param_1 < 2) {
    uVar5 = (uint)*(byte *)(param_2 + 0xbf);
    bVar1 = **(byte **)(param_2 + 0xd4);
    uVar3 = bVar1 & 1;
    if ((bVar1 & 1) == 0) {
      if (uVar5 < 8) {
        iVar2 = uVar5 + param_1 * 8;
        iVar4 = (&DAT_000135bc)[iVar2 * 0x4a];
        if (iVar4 == 0) {
          bVar1 = 0;
        }
        else {
          bVar1 = (&fdb_list)[iVar2 * 0x128] & 1;
        }
        if ((bVar1 != 0) && ((*(uint *)(iVar4 + 0x30) & 1) != 0)) {
          *(int *)(param_2 + 0x18) = iVar4;
          if ((ifd_debug & 9) == 9) {
            printk("%s:from idm:%d ssid%d, send to %s\n","idm_fdb_forward",param_1,uVar5,
                   (&DAT_000135bc)[iVar2 * 0x4a]);
            printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%u\nskb->cloned:\t%d\nref:\t%d\n"
                   ,*(undefined4 *)(param_2 + 0xd0),*(undefined4 *)(param_2 + 0xd4),
                   *(undefined2 *)(param_2 + 0xb2),*(byte *)(param_2 + 0x72) & 1,
                   *(undefined4 *)(*(int *)(param_2 + 0xcc) + 0x20));
            if (*(int *)(param_2 + 100) != 0) {
              printk("%02x ",**(undefined1 **)(param_2 + 0xd4));
              while (uVar3 = uVar3 + 1, uVar3 < *(uint *)(param_2 + 100)) {
                printk("%02x ",*(undefined1 *)(*(int *)(param_2 + 0xd4) + uVar3));
                if ((uVar3 & 0xf) == 0xf) {
                  printk(&_LC14);
                }
              }
            }
            printk(&_LC14);
          }
          iVar4 = (**(code **)(*(int *)(iVar4 + 300) + 0x10))(param_2,iVar4);
          if (iVar4 == 0) {
            iVar2 = iVar2 * 0x128;
            uVar3 = *(uint *)(&DAT_000135c0 + iVar2);
            uVar5 = *(uint *)(&DAT_000135c8 + iVar2);
            *(uint *)(&DAT_000135c0 + iVar2) = uVar3 + 1;
            *(uint *)(&DAT_000135c4 + iVar2) =
                 *(int *)(&DAT_000135c4 + iVar2) + (uint)(0xfffffffe < uVar3);
            uVar3 = *(uint *)(param_2 + 100);
            *(uint *)(&DAT_000135c8 + iVar2) = uVar5 + uVar3;
            *(uint *)(&DAT_000135cc + iVar2) =
                 *(int *)(&DAT_000135cc + iVar2) + (uint)CARRY4(uVar5,uVar3);
            return 0;
          }
          iVar2 = iVar2 * 0x128;
          uVar5 = *(uint *)(&DAT_00013668 + iVar2);
          uVar3 = *(uint *)(&DAT_00013670 + iVar2);
          *(uint *)(&DAT_00013668 + iVar2) = uVar5 + 1;
          *(uint *)(&DAT_0001366c + iVar2) =
               *(int *)(&DAT_0001366c + iVar2) + (uint)(0xfffffffe < uVar5);
          uVar5 = *(uint *)(param_2 + 100);
          *(uint *)(&DAT_00013670 + iVar2) = uVar3 + uVar5;
          *(uint *)(&DAT_00013674 + iVar2) =
               *(int *)(&DAT_00013674 + iVar2) + (uint)CARRY4(uVar3,uVar5);
          __dev_kfree_skb_any(param_2,1);
          return 0;
        }
        if (iVar2 * 0x128 != -0x135a8) {
          iVar2 = iVar2 * 0x128;
          uVar3 = *(uint *)(&DAT_00013668 + iVar2);
          uVar5 = *(uint *)(&DAT_00013670 + iVar2);
          *(uint *)(&DAT_00013668 + iVar2) = uVar3 + 1;
          *(uint *)(&DAT_0001366c + iVar2) =
               *(int *)(&DAT_0001366c + iVar2) + (uint)(0xfffffffe < uVar3);
          uVar3 = *(uint *)(param_2 + 100);
          *(uint *)(&DAT_00013670 + iVar2) = uVar5 + uVar3;
          *(uint *)(&DAT_00013674 + iVar2) =
               *(int *)(&DAT_00013674 + iVar2) + (uint)CARRY4(uVar5,uVar3);
        }
        goto LAB_000101b0;
      }
    }
    else if (bVar1 == 0xff) {
      uVar3 = 2;
    }
    else {
      uVar3 = 1;
    }
    idm_fdb_multi_send_handle(param_1,uVar5,param_2,uVar3);
  }
  else {
LAB_000101b0:
    __dev_kfree_skb_any(param_2,1);
  }
  return 0;
}

