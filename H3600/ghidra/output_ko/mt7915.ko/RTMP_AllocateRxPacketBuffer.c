// module: mt7915.ko
// function: RTMP_AllocateRxPacketBuffer @ 0x25ff30
// size: 636 bytes
//

uint RTMP_AllocateRxPacketBuffer
               (int param_1,int param_2,uint param_3,uint *param_4,undefined4 *param_5)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  
  cVar1 = *(char *)(param_1 + 0x1d);
  bVar2 = *(byte *)(param_1 + 0x1e);
  if (cVar1 == '\x01') {
    uVar6 = idm_skb_stack_pop(1,param_3);
    if (uVar6 == 0) {
      uVar6 = __alloc_skbuff(param_3 + 0x20,0x20,0,0xffffffff);
      if (uVar6 == 0) goto LAB_0025ff78;
      uVar3 = *(int *)(uVar6 + 0xcc) + 0x20;
      *(uint *)(uVar6 + 0xcc) = uVar3;
      g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
      *(int *)(uVar6 + 0xc0) = *(int *)(uVar6 + 0xc0) + 0x20;
      if (0x63f < param_3) {
        *(ushort *)(uVar6 + 0xbc) = *(ushort *)(uVar6 + 0xbc) & 0xff0f | 0x40;
      }
    }
    else {
      uVar3 = *(uint *)(uVar6 + 0xcc);
      *(ushort *)(uVar6 + 0xbc) = *(ushort *)(uVar6 + 0xbc) & 0xff0f | 0x40;
      g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
    }
    if (((bVar2 & 2) != 0) && (param_3 != 0)) {
      __memzero(uVar3,param_3);
      uVar3 = *(uint *)(uVar6 + 0xcc);
    }
    *param_4 = uVar3;
LAB_0025ffc8:
    if (param_2 == 0) {
      puVar7 = &arm_dma_ops;
    }
    else {
      puVar7 = *(undefined4 **)(param_2 + 0x10c);
      if (*(undefined4 **)(param_2 + 0x10c) == (undefined4 *)0x0) {
        puVar7 = &arm_dma_ops;
      }
    }
    uVar4 = (*(code *)puVar7[4])
                      (param_2,mem_map + (uVar3 + 0x40000000 >> 0xc) * 0x20,uVar3 & 0xfff,param_3,2,
                       0);
    *param_5 = uVar4;
    return uVar6;
  }
  if (cVar1 == '\0') {
    uVar6 = netdev_alloc_frag((param_3 + 0x3f & 0xffffffe0) + 0xc0);
    if (uVar6 != 0) {
      iVar5 = g_stWlanRadioStat._8_4_ + 1;
      g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
      if (((bVar2 & 2) != 0) && (iVar5 = g_stWlanRadioStat._8_4_, param_3 != 0)) {
        __memzero(uVar6 + 0x20,param_3);
        iVar5 = g_stWlanRadioStat._8_4_;
      }
      g_stWlanRadioStat._8_4_ = iVar5;
      uVar3 = uVar6 + 0x20;
      *param_4 = uVar3;
      goto LAB_0025ffc8;
    }
  }
  else if (cVar1 == '\x02') {
    uVar3 = alloc_rx_buf_1k();
    if (uVar3 != 0) {
      uVar6 = ((uint)bVar2 << 0x1e) >> 0x1f;
      if (param_3 == 0) {
        uVar6 = 0;
      }
      if (uVar6 != 0) {
        __memzero(uVar3,param_3);
      }
      *param_4 = uVar3;
      uVar6 = uVar3;
      goto LAB_0025ffc8;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: unknown allocate type %d\n","RTMP_AllocateRxPacketBuffer",cVar1);
  }
LAB_0025ff78:
  *param_4 = 0;
  *param_5 = 0;
  if (-1 < DebugLevel) {
    printk("can\'t allocate rx %ld size packet\n",param_3);
  }
  return 0;
}

