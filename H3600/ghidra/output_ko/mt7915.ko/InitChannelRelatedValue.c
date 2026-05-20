// module: mt7915.ko
// function: InitChannelRelatedValue @ 0x74db8
// size: 352 bytes
//

void InitChannelRelatedValue(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined *puVar4;
  undefined1 uVar5;
  undefined1 uStack_21;
  undefined1 local_20;
  undefined1 local_1e;
  undefined1 local_1d;
  
  iVar3 = GetStaCfgByWdev();
  bVar1 = *(byte *)(iVar3 + 0x4167);
  if (iVar3 == 0) {
    printk(&_LC1,0x11aa);
    dump_stack();
    return;
  }
  bbp_set_rxpath(param_1,"SetPartProfileParameters"[param_1 + 0x18] & 0xf);
  bVar2 = *(byte *)(iVar3 + 0x4165);
  *(byte *)(param_2 + 0x1a) = bVar2;
  if (bVar2 < bVar1) {
    if ((*(byte *)(iVar3 + 0x4190) & 2) == 0) goto LAB_00074e10;
    uVar5 = 1;
LAB_00074e8c:
    os_zero_mem(&uStack_21,9);
    local_1d = *(undefined1 *)(param_2 + 0x1a);
    local_20 = 1;
    local_1e = uVar5;
    wlan_operate_set_phy(param_2,&uStack_21);
    if (DebugLevel < 3) goto LAB_00074e50;
    puVar4 = &_LC87;
  }
  else {
    if ((bVar1 < bVar2) && ((*(byte *)(iVar3 + 0x4190) & 2) != 0)) {
      uVar5 = 3;
      goto LAB_00074e8c;
    }
LAB_00074e10:
    os_zero_mem(&uStack_21,9);
    local_1d = *(undefined1 *)(param_2 + 0x1a);
    local_20 = 0;
    local_1e = 0;
    wlan_operate_set_phy(param_2,&uStack_21);
    if (DebugLevel < 3) goto LAB_00074e50;
    puVar4 = &_LC88;
  }
  printk("%s():BW_%s, CtrlChannel=%d, CentralChannel=%d\n","InitChannelRelatedValue",puVar4,
         *(undefined1 *)(param_2 + 0x1a),bVar1);
LAB_00074e50:
  bbp_get_agc(param_1,"rtmp_read_dot11v_mbssid_cfg_from_file" + param_1 + 0x1b,1);
  return;
}

