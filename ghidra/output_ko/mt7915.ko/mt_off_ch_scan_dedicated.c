// module: mt7915.ko
// function: mt_off_ch_scan_dedicated @ 0x22f1b0
// size: 924 bytes
//

void mt_off_ch_scan_dedicated(int param_1,int param_2,int param_3)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  byte bVar12;
  byte local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  
  bVar2 = *(byte *)(param_1 + 0xa79754);
  uVar3 = DfsGetBgndParameter(param_1,4);
  uVar4 = DfsGetBgndParameter(param_1,5);
  uVar1 = (uint)(bVar2 >> 4);
  if (uVar1 == 0) {
    bVar2 = DfsGetBgndParameter(param_1,0);
    uVar6 = 2;
LAB_0022f38c:
    uVar8 = DfsGetBgndParameter(param_1,uVar6);
    uVar8 = uVar8 & 0xff;
  }
  else {
    if (uVar1 == 1) {
      bVar2 = DfsGetBgndParameter(param_1,1);
      uVar6 = 3;
      goto LAB_0022f38c;
    }
    uVar8 = 0;
    bVar2 = 0;
  }
  os_zero_mem(&local_38);
  if (param_3 == 0) {
    uVar5 = param_1 + uVar1 * 0x14;
    uVar3 = (uint)*(byte *)(param_1 + 0xa7905c);
    uVar4 = (uint)*(byte *)(param_1 + 0xa78ad0);
    bVar2 = *(byte *)(uVar5 + 0xa795e8);
    uVar7 = (uint)*(byte *)(uVar5 + 0xa795ea);
    uVar8 = (uint)*(byte *)(uVar5 + 0xa795eb);
    if (uVar3 < 0xf) {
      uVar5 = 0;
    }
    uVar10 = (uint)*(byte *)(param_1 + 0xa7905d);
    if (0xe < uVar3) {
      uVar5 = 1;
    }
LAB_0022f264:
    local_2b = (undefined1)uVar5;
    uVar9 = uVar3;
    uVar11 = uVar10;
    if (param_2 == 7) goto LAB_0022f2c8;
LAB_0022f26c:
    local_38 = bVar2;
    local_37 = (undefined1)uVar7;
    local_36 = (undefined1)uVar8;
    local_2b = (undefined1)uVar5;
    if (param_2 == 8) {
      bVar2 = *(byte *)(param_1 + uVar1 * 0x14 + 0xa795ed);
      if (bVar2 == 0) {
        local_34 = 0;
      }
      else {
        bVar12 = 0;
        uVar4 = 0;
        do {
          uVar3 = (uint)bVar12;
          bVar12 = bVar12 + 1;
          uVar4 = uVar4 | 1 << uVar3 & 0xffU;
          local_34 = (undefined1)uVar4;
        } while (bVar12 < bVar2);
      }
      local_35 = *(undefined1 *)(param_1 + uVar1 * 0x14 + 0xa795ec);
      local_2e = 0;
      local_2c = 2;
      if (2 < DebugLevel) {
        printk("%s: work_prim_ch:%d work_bw:%d work_central_ch:%d\n","mt_off_ch_scan_dedicated",
               local_38,uVar8,uVar7);
      }
      goto LAB_0022f368;
    }
    if (param_2 != 6) {
      if (-1 < DebugLevel) {
        printk("%s ERROR reason=%d\n","mt_off_ch_scan_dedicated",param_2);
      }
      return;
    }
    local_33 = (undefined1)uVar9;
    local_32 = (undefined1)uVar11;
    local_31 = (undefined1)uVar4;
    local_2e = 1;
    local_2c = 2;
    if ((DebugLevel < 3) ||
       (printk("%s: mntr_ch:%d mntr_bw:%d mntr_central_ch:%d\n","mt_off_ch_scan_dedicated",uVar9,
               uVar4,uVar11), DebugLevel < 3)) goto LAB_0022f368;
    printk("%s: work_prim_ch:%d work_bw:%d work_central_ch:%d\n","mt_off_ch_scan_dedicated",local_38
           ,local_36,local_37);
  }
  else {
    if (param_3 == 1) {
      uVar7 = DfsPrimToCent(bVar2,uVar8);
      uVar10 = DfsPrimToCent(uVar3,uVar4);
      uVar5 = (uint)(0xe < uVar3);
      goto LAB_0022f264;
    }
    uVar5 = 0;
    local_2b = 0;
    uVar10 = 0;
    uVar3 = 0;
    uVar7 = uVar5;
    uVar8 = uVar5;
    uVar9 = uVar5;
    uVar4 = uVar5;
    uVar11 = uVar5;
    bVar2 = 0;
    if (param_2 != 7) goto LAB_0022f26c;
LAB_0022f2c8:
    local_33 = (undefined1)uVar3;
    local_32 = (undefined1)uVar10;
    local_31 = (undefined1)uVar4;
    local_2e = 2;
    local_2c = 2;
    if (DebugLevel < 3) goto LAB_0022f368;
    printk("%s: mntr_ch:%d mntr_bw:%d mntr_central_ch:%d\n","mt_off_ch_scan_dedicated",uVar3,uVar4,
           uVar10);
  }
  if (2 < DebugLevel) {
    printk("%s: dbdc_idx:%d scan_mode:%d is_aband:%d\n","mt_off_ch_scan_dedicated",local_2d,local_2e
           ,local_2b);
  }
LAB_0022f368:
  mt_cmd_off_ch_scan(param_1,&local_38);
  return;
}

