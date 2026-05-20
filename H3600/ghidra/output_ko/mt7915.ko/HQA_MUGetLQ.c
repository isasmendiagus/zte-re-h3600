// module: mt7915.ko
// function: HQA_MUGetLQ @ 0x279d1c
// size: 380 bytes
//

undefined4 HQA_MUGetLQ(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int local_84;
  int local_80;
  undefined4 local_7c [4];
  undefined4 local_6c;
  undefined4 auStack_68 [20];
  
  local_80 = param_3 + 0xc;
  iVar2 = 0;
  local_84 = 0;
  os_zero_mem(local_7c,0x14);
  os_zero_mem(auStack_68,0x50);
  FUN_00276034(1,4,&local_80,&local_84);
  if (local_84 == 0) {
    uVar1 = hqa_wifi_test_su_get_lq(param_1,local_7c);
    iVar2 = 0;
    do {
      if (0 < DebugLevel) {
        printk("DWORD%d:%08x\n",iVar2,local_7c[iVar2]);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 != 5);
    *(undefined4 *)(param_3 + 0xe) = local_7c[0];
    *(undefined4 *)(param_3 + 0x12) = local_7c[1];
    *(undefined4 *)(param_3 + 0x16) = local_7c[2];
    *(undefined4 *)(param_3 + 0x1e) = local_6c;
    *(undefined4 *)(param_3 + 0x1a) = local_7c[3];
    FUN_0026cdd0(param_3,param_2,0x16,uVar1);
  }
  else {
    uVar1 = hqa_wifi_test_mu_get_lq(param_1,auStack_68);
    do {
      if (0 < DebugLevel) {
        printk("DWORD%d:%08x\n",iVar2,auStack_68[iVar2]);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 != 0x14);
    memcpy((void *)(param_3 + 0xe),auStack_68,0x50);
    FUN_0026cdd0(param_3,param_2,0x52,uVar1);
  }
  if (0 < DebugLevel) {
    printk(&_LC11,"HQA_MUGetLQ");
  }
  return uVar1;
}

