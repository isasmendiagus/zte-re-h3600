// module: mt7915.ko
// function: hqa_set_ru_info @ 0x2490e4
// size: 828 bytes
//

undefined4 hqa_set_ru_info(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  undefined1 *puVar10;
  uint uVar11;
  uint uVar12;
  bool bVar13;
  byte local_39;
  uint local_38;
  int local_34;
  uint local_30;
  int local_2c [2];
  
  local_39 = *(byte *)(param_1 + 0x4cc);
  local_34 = param_2 + 0xc;
  uVar8 = 0;
  uVar1 = *(ushort *)(param_2 + 8);
  local_30 = 0;
  local_2c[0] = 0;
  local_38 = 0;
  FUN_002474f4(1,4,&local_34,&local_39);
  FUN_002474f4(1,4,&local_34,&local_30);
  FUN_002474f4(1,4,&local_34,local_2c);
  iVar9 = local_2c[0];
  uVar12 = local_30;
  if (local_2c[0] + local_30 == 0) {
    uVar7 = 0x103;
  }
  else {
    iVar2 = __aeabi_uidiv(uVar1 - 0xc);
    uVar11 = (uint)(iVar2 << 0x16) >> 0x18;
    printk("%s: Band:%d [ru_segment 0]:%d, [ru_segment 1]:%d\n","hqa_set_ru_info",local_39,uVar12,
           iVar9);
    printk("\t\tparameters count:%d\n",uVar11);
    iVar9 = param_1 + (uint)local_39 * 0xd18;
    puVar10 = (undefined1 *)(iVar9 + 0xa1c);
    uVar12 = *(uint *)(param_1 + (uint)local_39 * 0xd18 + 0x6dc);
    sys_ad_zero_mem(puVar10,0x6c0);
    sys_ad_set_mem(iVar9 + 0x10dd,8,0xff);
    for (; uVar8 < local_30 + local_2c[0]; uVar8 = uVar8 + 1) {
      bVar13 = local_30 <= uVar8;
      *puVar10 = 1;
      FUN_002474f4(1,4,&local_34,&local_38);
      FUN_002474f4(1,4,&local_34,&local_38);
      uVar6 = 0;
      uVar5 = 0;
      uVar4 = local_38;
      do {
        uVar3 = uVar4 & 1;
        uVar4 = uVar4 >> 4;
        uVar5 = uVar5 | uVar3 << (uVar6 & 0xff);
        uVar6 = uVar6 + 1;
      } while (uVar6 != 8);
      *(uint *)(puVar10 + 8) = uVar5;
      FUN_002474f4(1,4,&local_34,&local_38);
      *(uint *)(puVar10 + 4) = local_38;
      FUN_002474f4(1,4,&local_34,&local_38);
      *(uint *)(puVar10 + 0xc) = (uint)bVar13 | local_38 << 1;
      FUN_002474f4(1,4,&local_34,&local_38);
      *(uint *)(puVar10 + 0x10) = local_38;
      FUN_002474f4(1,4,&local_34,&local_38);
      *(uint *)(puVar10 + 0x14) = local_38;
      FUN_002474f4(1,4,&local_34,&local_38);
      *(uint *)(puVar10 + 0x18) = local_38;
      FUN_002474f4(1,4,&local_34,&local_38);
      *(uint *)(puVar10 + 0x1c) = local_38 - 1;
      FUN_002474f4(1,4,&local_34,&local_38);
      uVar4 = local_38;
      if (local_38 < 0x19) {
        uVar4 = uVar12;
      }
      *(uint *)(puVar10 + 0x20) = uVar4;
      if (uVar11 != 9) {
        FUN_002474f4(1,4,&local_34,&local_38);
        *(uint *)(puVar10 + 0x24) = local_38;
        if (uVar11 != 10) {
          FUN_002474f4(1,4,&local_34,&local_38);
          *(uint *)(puVar10 + 0x28) = local_38;
        }
      }
      printk("%s: ru_segment[%d][0x%x]: ru_idx:%d\n","hqa_set_ru_info",(uint)bVar13,
             *(undefined4 *)(puVar10 + 8),*(uint *)(puVar10 + 0xc) >> 1);
      printk("\t\t\t\trate:%x, ldpc:%d\n",*(undefined4 *)(puVar10 + 0x10),
             *(undefined4 *)(puVar10 + 0x14));
      printk("\t\t\t\tnss:%d, mimo nss:%d\n",*(undefined4 *)(puVar10 + 0x18),
             *(undefined4 *)(puVar10 + 0x28));
      printk("\t\t\t\t start spatial stream:%d,\n",*(undefined4 *)(puVar10 + 0x1c));
      printk("\t\t\t\tmpdu length=%d, alpha:%d\n",*(undefined4 *)(puVar10 + 0x20),
             *(undefined4 *)(puVar10 + 0x24));
      puVar10 = puVar10 + 0x6c;
    }
    uVar7 = 0;
  }
  FUN_00246b90(param_2,2,uVar7);
  return uVar7;
}

