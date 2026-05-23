// module: mt7915.ko
// function: SetATETXBFProc @ 0x266e1c
// size: 332 bytes
//

undefined4
SetATETXBFProc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = net_ad_wrap_service();
  uVar3 = (uint)*(byte *)(iVar2 + 0x4cc);
  if (0 < DebugLevel) {
    printk("%s: control_band_idx = %d\n","SetATETXBFProc",uVar3,DebugLevel,param_4);
  }
  uVar1 = simple_strtol(param_2,0,10);
  switch(uVar1) {
  case 0:
    uVar1 = 0;
    break;
  case 1:
    iVar2 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar2 + uVar3 * 0xd18 + 0x11cc) = 0;
    iVar2 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar2 + uVar3 * 0xd18 + 0x11cd) = 1;
    return 1;
  case 2:
    iVar2 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar2 + uVar3 * 0xd18 + 0x11cc) = 1;
    iVar2 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar2 + uVar3 * 0xd18 + 0x11cd) = 0;
    return 1;
  case 3:
    uVar1 = 1;
    break;
  default:
    if (-1 < DebugLevel) {
      printk("Set_ATE_TXBF_Proc: Invalid parameter %d\n");
    }
    return 0;
  }
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + uVar3 * 0xd18 + 0x11cc) = uVar1;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + uVar3 * 0xd18 + 0x11cd) = uVar1;
  return 1;
}

