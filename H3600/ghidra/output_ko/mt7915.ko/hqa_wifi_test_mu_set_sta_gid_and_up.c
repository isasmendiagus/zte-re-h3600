// module: mt7915.ko
// function: hqa_wifi_test_mu_set_sta_gid_and_up @ 0x8a924
// size: 484 bytes
//

undefined4 hqa_wifi_test_mu_set_sta_gid_and_up(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_48 = 0x3c;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0x1c);
  if (iVar1 == 0) {
    uVar3 = 1;
    uVar2 = 0xffffffff;
    goto LAB_0008aa04;
  }
  local_30 = *param_2;
  local_2c = param_2[1];
  local_28 = param_2[2];
  local_24 = param_2[3];
  local_20 = param_2[4];
  local_1c = param_2[5];
  if (-1 < DebugLevel) {
    printk("%s: MU_STRUCT_MU_STA_PARAM\n","hqa_wifi_test_mu_set_sta_gid_and_up");
    if (DebugLevel < 0) {
LAB_0008aac4:
      if (-1 < DebugLevel) {
        printk("up[2] = %u\n",local_20);
        if (-1 < DebugLevel) {
          printk("up[3] = %u\n",local_1c);
        }
      }
    }
    else {
      printk("gid[0] = %u\n",local_30);
      if (-1 < DebugLevel) {
        printk("gid[1] = %u\n",local_2c);
        if (-1 < DebugLevel) {
          printk("up[0] = %u\n",local_28);
          if (-1 < DebugLevel) {
            printk("up[1] = %u\n",local_24);
            goto LAB_0008aac4;
          }
        }
      }
    }
  }
  uVar3 = 0;
  local_44 = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_44));
  local_40 = CONCAT31(local_40._1_3_,10);
  AndesInitCmdMsg(iVar1,local_44,local_40,local_3c,local_38,local_34);
  AndesAppendCmdMsg(iVar1,&local_48,4);
  AndesAppendCmdMsg(iVar1,&local_30,0x18);
  AndesSendCmdMsg(param_1,iVar1);
  uVar2 = 0;
LAB_0008aa04:
  if (-1 < DebugLevel) {
    printk("%s:(Ret = %d_\n","hqa_wifi_test_mu_set_sta_gid_and_up",uVar2);
  }
  return uVar3;
}

