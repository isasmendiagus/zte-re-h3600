// module: mt7915.ko
// function: IterateOnBssTab2 @ 0x74b08
// size: 412 bytes
//

void IterateOnBssTab2(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined1 uStack_30;
  undefined1 local_2f;
  undefined1 local_2d;
  undefined1 local_2c;
  
  iVar2 = GetStaCfgByWdev();
  if (iVar2 != 0) {
    uVar4 = *(uint *)(iVar2 + 0x211e44);
    if (uVar4 < *(uint *)(iVar2 + 0x162a38)) {
      if (2 < DebugLevel) {
        printk("CNTL - iterate BSS %ld of %d\n",uVar4);
      }
      iVar5 = iVar2 + uVar4 * 0xaf4;
      *(undefined1 *)(param_2 + 0x1a) = *(undefined1 *)(iVar5 + 0x162a4c);
      wlan_operate_set_prim_ch(param_2);
      AssocParmFill(param_1,&uStack_30,iVar5 + 0x162a46,*(undefined2 *)(iVar5 + 0x162aca),300,
                    *(undefined2 *)(iVar2 + 0x2124a6));
      MlmeEnqueueWithWdev(param_1,1,1,0x10,&uStack_30,0,param_2);
      cntl_fsm_state_transition(param_2,5,"IterateOnBssTab2");
    }
    else {
      os_zero_mem(&uStack_30,9);
      local_2c = *(undefined1 *)(param_2 + 0x1a);
      local_2d = 0;
      local_2f = 0;
      wlan_operate_set_phy(param_2,&uStack_30);
      if (2 < DebugLevel) {
        uVar1 = *(undefined1 *)(param_2 + 0x1a);
        uVar3 = wlan_operate_get_cen_ch_1(param_2);
        printk("%s():CNTL - All roaming failed, restore to Channel(Ctrl=%d, Central = %d)\n",
               "IterateOnBssTab2",uVar1,uVar3);
      }
    }
    cntl_fsm_state_transition(param_2,0,"IterateOnBssTab2");
    return;
  }
  printk(&_LC1,0x1135);
  dump_stack();
  return;
}

