// module: mt7915.ko
// function: mt_engine_start_tx @ 0x25643c
// size: 1472 bytes
//

int mt_engine_start_tx(int param_1,uint *param_2,undefined4 *param_3,uint param_4)

{
  uint uVar1;
  uint *puVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  char cVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  undefined1 local_29 [5];
  
  uVar12 = (uint)*(byte *)((int)param_2 + 0xc52);
  uVar6 = (uint)(byte)param_2[0xb];
  uVar9 = param_2[1];
  uVar11 = *param_2;
  uVar10 = param_2[0x30e];
  printk("%s: band_idx=%u, ch=%u, ctrl_ch=%u, wdev_idx=%u\n","mt_engine_start_tx",param_4,
         (char)param_2[0x314],uVar12,uVar6);
  if (uVar9 == 0) {
    iVar4 = 0x301;
    goto LAB_00256588;
  }
  if ((uVar11 & 2) != 0) {
    printk("%s: already in TXFRAME mode now, tx is ongoing!\n","mt_engine_start_tx");
    return 0;
  }
  uVar12 = 1;
  iVar4 = net_ad_set_device_info(param_1,param_2,(int)param_2 + 0x111,param_4,1);
  if ((iVar4 != 0) || (iVar4 = (*(code *)*param_3)(param_1,6,0,param_4), iVar4 != 0))
  goto LAB_00256588;
  uVar9 = (uint)*(byte *)((int)param_2 + 0xc57);
  if (2 < uVar9) {
    uVar9 = 3;
  }
  if (*(char *)((int)param_2 + 0xc55) == '\n') {
    uVar6 = (uint)(byte)param_2[0x317];
    (*(code *)param_3[0x52])
              (param_1,param_4,0,1,uVar9,uVar6,*(undefined1 *)((int)param_2 + 0xc5a),
               (char)param_2[0x2ff],param_2 + 0x14f);
    uVar12 = uVar9;
  }
  net_ad_cfg_queue(param_1,0);
  net_ad_cfg_queue(param_1,1);
  uVar9 = param_2[0x305];
  local_29[0] = 0;
  if (uVar9 == 0) {
    local_38 = 1;
    local_3c = 10;
    uVar3 = 9;
    local_34 = 0;
  }
  else {
    local_38 = (uint)*(byte *)((int)param_2 + 0xc1f);
    uVar3 = *(ushort *)((int)param_2 + 0xc1a);
    local_3c = (uint)(ushort)param_2[0x307];
    local_34 = (uint)(ushort)param_2[0x308];
  }
  *(ushort *)((int)param_2 + 0xc1a) = uVar3;
  *(undefined2 *)(param_2 + 0x307) = (undefined2)local_3c;
  *(undefined1 *)((int)param_2 + 0xc1f) = (undefined1)local_38;
  *(undefined2 *)(param_2 + 0x308) = (undefined2)local_34;
  iVar4 = (*(code *)param_3[0x5f])(param_1,param_2,param_4);
  if (iVar4 != 0) goto LAB_00256588;
  uVar12 = 0x3c;
  uVar6 = param_4;
  iVar4 = (*(code *)param_3[0xc])(param_1,uVar3 & 0xff,local_3c & 0xff,2,0x3c,param_4);
  if ((iVar4 != 0) || (iVar4 = net_ad_get_wmm_idx(param_2[0xaf],local_29), iVar4 != 0))
  goto LAB_00256588;
  iVar4 = net_ad_set_wmm_param_by_qid
                    (local_29[0],*(undefined1 *)((int)param_2 + 0x2e),param_1,param_2);
  printk("%s: ipg=%d, slot_time=%d, sifs_time=%d, aifsn=%d, cw=%d\n","mt_engine_apply_ipg_param",
         uVar9,uVar3,local_3c,local_38,local_34);
  uVar12 = local_3c;
  uVar6 = local_38;
  if (iVar4 != 0) goto LAB_00256588;
  if (uVar10 != 0xffffffff) {
    if ((char)param_2[0x81] != '\x01') {
      uVar10 = uVar10 + param_2[0x30f];
    }
    param_2[0x30e] = uVar10;
  }
  uVar9 = param_2[0x305];
  uVar13 = param_2[0x304];
  *param_2 = uVar11 | 2;
  if (uVar13 != 0 || uVar9 != 0) {
    uVar12 = param_2[0x30e];
    uVar1 = *(uint *)(param_1 + 0x38) >> 1;
    if (*(char *)((int)param_2 + 0x215) == '\0') {
      iVar4 = 1;
    }
    else {
      iVar4 = 0;
      puVar7 = param_2;
      do {
        puVar2 = puVar7 + 0xd5;
        puVar7 = puVar7 + 8;
        iVar4 = iVar4 + *puVar2;
      } while (puVar7 != param_2 + ((byte)(*(char *)((int)param_2 + 0x215) - 1) + 1) * 8);
      if (iVar4 == 0) {
        iVar4 = 1;
      }
    }
    printk("%s: per round pkt(s)=%d\n","mt_engine_start_tx",iVar4,uVar12,local_3c,local_38,local_34)
    ;
    uVar5 = __aeabi_uidiv(uVar1,iVar4);
    if (uVar12 <= uVar5) {
      uVar5 = uVar12;
    }
    uVar12 = local_3c;
    uVar6 = local_38;
    if ((*(byte *)((int)param_2 + 0xc55) - 0xb < 2) && ((char)param_2[0x309] != '\0')) {
      if ((((code *)param_3[0x36] != (code *)0x0) &&
          (iVar4 = (*(code *)param_3[0x36])(param_1,param_2[0xaf],uVar10), uVar12 = local_3c,
          uVar6 = local_38, iVar4 != 0)) ||
         (((code *)param_3[0x37] != (code *)0x0 &&
          (iVar4 = (*(code *)param_3[0x37])(param_1,param_2[0xaf],1), iVar4 != 0))))
      goto LAB_00256588;
      uVar5 = 1;
    }
    local_40 = 0;
    printk("%s: repeat=%d, token_limit=%d, ","mt_engine_start_tx",uVar5,uVar1,uVar12,uVar6,local_34)
    ;
    printk("pkt_tx_time=%d, ipg=%d\n",uVar13,uVar9);
    for (; local_40 != uVar5; local_40 = local_40 + 1) {
      for (uVar9 = 0; uVar10 = uVar9 & 0xff, uVar10 < *(byte *)((int)param_2 + 0x215);
          uVar9 = uVar9 + 1) {
        for (cVar8 = (char)param_2[uVar10 * 8 + 0xd5]; cVar8 != '\0'; cVar8 = cVar8 + -1) {
          uVar12 = param_2[uVar10 + 0xbf];
          net_ad_enq_pkt(param_1,*(undefined2 *)((int)param_2 + 0x2e),param_2[uVar10 + 0x9f],
                         param_2[uVar10 + 0xaf],uVar12);
          param_2[0x310] = param_2[0x310] + 1;
        }
      }
    }
    *(undefined1 *)((int)param_2 + 0x216) = 0;
  }
  uVar9 = (uint)*(byte *)((int)param_2 + 0xc55);
  if (uVar9 - 0xb < 2) {
    if ((char)param_2[0x309] == '\0') {
      uVar12 = param_2[0xbf];
      net_ad_enq_pkt(param_1,*(undefined2 *)((int)param_2 + 0x2e),param_2[0x9f],param_2[0xaf],uVar12
                    );
      uVar9 = (uint)*(byte *)((int)param_2 + 0xc55);
      goto LAB_002566a8;
    }
  }
  else {
LAB_002566a8:
    if (uVar9 == 10) {
      uVar12 = 0;
      uVar6 = 0;
      (*(code *)param_3[0x52])(param_1,param_4,1,1,0,0,0,0,0);
      uVar9 = (uint)*(byte *)((int)param_2 + 0xc55);
    }
  }
  if (((10 < uVar9) || (iVar4 = net_ad_post_tx(param_1,param_2,param_4,0), iVar4 == 0)) &&
     (iVar4 = (*(code *)*param_3)(param_1,1,1,param_4), iVar4 == 0)) {
    if ((uVar11 & 4) == 0) {
      return 0;
    }
    iVar4 = (*(code *)*param_3)(param_1,6,1,param_4);
    if (iVar4 == 0) {
      return 0;
    }
  }
LAB_00256588:
  printk("%s: err=0x%08x, wdev_idx=%x\n","mt_engine_start_tx",iVar4,(char)param_2[0xb],uVar12,uVar6)
  ;
  return iVar4;
}

