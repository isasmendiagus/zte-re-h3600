// module: mt7915.ko
// function: MT_MPSTxStart @ 0x28a8b4
// size: 308 bytes
//

undefined4 MT_MPSTxStart(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  uVar6 = (uint)*(byte *)(param_1 + 0xa3ae36);
  iVar5 = *(int *)(param_1 + 0xa39fd4);
  iVar1 = net_ad_wrap_service();
  iVar1 = iVar1 + uVar6 * 0xd18;
  iVar7 = *(int *)(iVar1 + 0x11cc);
  iVar2 = net_ad_wrap_service(param_1);
  iVar8 = *(int *)(iVar1 + 0x11b8);
  uVar4 = *(uint *)(iVar2 + uVar6 * 0xd18 + 0x4e0);
  if (0 < DebugLevel) {
    printk("%s: control_band_idx:%u, items:%u\n","MT_MPSTxStart",uVar6,iVar8);
  }
  if (((iVar8 != 0 && iVar7 != 0) && ((uVar4 & 0x42) == 0)) && (*(char *)(iVar1 + 0x11c4) == '\0'))
  {
    iVar2 = net_ad_wrap_service(param_1);
    *(uint *)(uVar6 * 0xd18 + iVar2 + 0x4e0) = uVar4 | 0x40;
    *(undefined4 *)(iVar1 + 0x11c8) = 1;
    *(undefined1 *)(iVar1 + 0x11c4) = 1;
    MT_SetATEMPSDump(param_1,uVar6);
    FUN_00286a70(param_1,uVar6);
    (**(code **)(iVar5 + 8))(param_1);
                    /* WARNING: Could not recover jumptable at 0x0028a9a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar3 = (**(code **)(iVar5 + 0x10))(param_1);
    return uVar3;
  }
  if (-1 < DebugLevel) {
    printk("%s error, mode:0x%x, mps_cnt:%x, MPS_SETTING: %p\n","MT_MPSTxStart",uVar4,iVar8,iVar7);
  }
  return 0;
}

