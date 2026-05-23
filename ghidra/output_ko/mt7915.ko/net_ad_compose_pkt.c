// module: mt7915.ko
// function: net_ad_compose_pkt @ 0x25c518
// size: 484 bytes
//

undefined4
net_ad_compose_pkt(int param_1,int param_2,int param_3,int param_4,int param_5,size_t param_6)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  void *pvVar6;
  undefined1 *__dest;
  uint uVar7;
  undefined1 *puVar8;
  size_t __n;
  
  iVar3 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar3 != 0) {
    bVar1 = *(byte *)(param_1 + 0x3c);
    iVar3 = param_2 + param_3 * 6;
    if (param_5 == 0) {
      printk("%s: tx length can\'t be 0!!\n","net_ad_compose_pkt");
      return 0x609;
    }
    sys_ad_zero_mem(param_4,0x33ff);
    pvVar6 = (void *)(param_4 + (uint)bVar1);
    sys_ad_move_mem(pvVar6,(void *)(param_2 + 0x31),param_6);
    sys_ad_move_mem((void *)((int)pvVar6 + 4),(void *)(iVar3 + 0x51),6);
    sys_ad_move_mem((void *)((int)pvVar6 + 10),(void *)(iVar3 + 0xb1),6);
    sys_ad_move_mem((void *)((int)pvVar6 + 0x10),(void *)(iVar3 + 0x111),6);
    iVar3 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
    if (iVar3 != 0) {
      iVar4 = *(int *)(param_2 + 0x200);
      __n = *(size_t *)(param_2 + 0x1f8);
      uVar7 = param_5 - param_6;
      __dest = (undefined1 *)((int)pvVar6 + param_6);
      printk("%s: len=%d, pl_len=%u, policy=%x\n","net_ad_init_payload",uVar7,__n,iVar4);
      if (iVar4 == 2) {
        puVar8 = __dest + uVar7;
        for (; __dest != puVar8; __dest = __dest + 1) {
          uVar2 = RandomByte(iVar3);
          *__dest = uVar2;
        }
      }
      else {
        pvVar6 = (void *)(param_2 + 0x171);
        if (pvVar6 == (void *)0x0) {
          return 0x607;
        }
        printk("%s: payload=%x\n","net_ad_init_payload",*(undefined1 *)(param_2 + 0x171));
        if (__n == 0) {
          printk("%s: payload length can\'t be 0!!\n","net_ad_init_payload");
          return 0x609;
        }
        if (iVar4 == 0) {
          sys_ad_zero_mem(__dest,uVar7);
          sys_ad_move_mem(__dest,pvVar6,__n);
          return 0;
        }
        if (iVar4 == 1) {
          for (uVar5 = 0; uVar5 < uVar7; uVar5 = uVar5 + __n) {
            sys_ad_move_mem(__dest + uVar5,pvVar6,__n);
          }
        }
      }
      return 0;
    }
  }
  return 0x606;
}

