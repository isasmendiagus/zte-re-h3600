// module: mt7915.ko
// function: HQA_RfRegBulkRead @ 0x26f420
// size: 424 bytes
//

int HQA_RfRegBulkRead(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  code *pcVar7;
  uint uVar8;
  uint *puVar9;
  uint local_2c [2];
  
  uVar1 = *(uint *)(param_3 + 0xc);
  iVar5 = *(int *)(param_1 + 0xa39fd4);
  uVar2 = *(uint *)(param_3 + 0x10);
  pcVar7 = *(code **)(iVar5 + 0xb0);
  uVar3 = *(uint *)(param_3 + 0x14);
  uVar8 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  uVar1 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 | uVar3 >> 0x18;
  if (pcVar7 == (code *)0x0) {
    iVar4 = 1;
  }
  else {
    if (uVar1 != 0) {
      uVar3 = 0;
      puVar9 = (uint *)(param_3 + 0xe);
      while( true ) {
        iVar6 = (-0xe - param_3) +
                (uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                uVar2 >> 0x18) + (int)puVar9;
        iVar4 = (*pcVar7)(param_1,uVar8,iVar6,local_2c);
        if (2 < DebugLevel) {
          printk("%s: Wfsel = %d, Offset = %x, Value = %x\n","HQA_RfRegBulkRead",uVar8,iVar6,
                 local_2c[0]);
        }
        if (iVar4 != 0) {
          if (-1 < DebugLevel) {
            printk("Wfsel = %d, Offset = %x, Value = %x fail\n",uVar8,iVar6,local_2c[0]);
          }
          goto LAB_0026f574;
        }
        uVar3 = uVar3 + 1;
        local_2c[0] = local_2c[0] << 0x18 | (local_2c[0] >> 8 & 0xff) << 0x10 |
                      (local_2c[0] >> 0x10 & 0xff) << 8 | local_2c[0] >> 0x18;
        *puVar9 = local_2c[0];
        if (uVar3 == uVar1) break;
        pcVar7 = *(code **)(iVar5 + 0xb0);
        puVar9 = puVar9 + 1;
      }
    }
    iVar4 = 0;
  }
LAB_0026f574:
  FUN_0026cdd0(param_3,param_2,uVar1 * 4 + 2,iVar4);
  return iVar4;
}

