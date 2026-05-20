// module: mt7915.ko
// function: HQA_RfRegBulkWrite @ 0x26f284
// size: 408 bytes
//

int HQA_RfRegBulkWrite(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  int iVar8;
  
  iVar8 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_RfRegBulkWrite");
  }
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = *(uint *)(param_3 + 0x10);
  uVar5 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  uVar1 = *(uint *)(param_3 + 0x14);
  uVar2 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  if (*(int *)(iVar8 + 0xac) == 0) {
    iVar4 = 1;
  }
  else {
    if (uVar1 != 0) {
      uVar7 = 0;
      puVar6 = (uint *)(param_3 + 0x18);
      do {
        uVar3 = *puVar6;
        uVar7 = uVar7 + 1;
        puVar6 = puVar6 + 1;
        uVar3 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                uVar3 >> 0x18;
        if (2 < DebugLevel) {
          printk("%s: Wfsel = %d, Offset = %x, Value = %x\n","HQA_RfRegBulkWrite",uVar5,uVar2,uVar3)
          ;
        }
        iVar4 = (**(code **)(iVar8 + 0xac))(param_1,uVar5,uVar2,uVar3);
        if (iVar4 != 0) {
          if (-1 < DebugLevel) {
            printk("Wfsel = %d, Offset = %x, Value = %x fail\n",uVar5,uVar2,uVar3);
          }
          goto LAB_0026f38c;
        }
        uVar2 = uVar2 + 4;
      } while (uVar7 != uVar1);
    }
    iVar4 = 0;
  }
LAB_0026f38c:
  FUN_0026cdd0(param_3,param_2,2,iVar4);
  return iVar4;
}

