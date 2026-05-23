// module: mt7915.ko
// function: chip_write_txbf_profile_data @ 0x178844
// size: 676 bytes
//

char chip_write_txbf_profile_data(int param_1,ushort *param_2)

{
  ushort uVar1;
  ushort uVar2;
  char cVar3;
  int iVar4;
  uint local_78;
  uint uStack_74;
  uint uStack_70;
  uint uStack_6c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  
  iVar4 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = *param_2;
  uVar2 = param_2[1];
  os_zero_mem(param_1 + 0xa78734,0x84);
  os_zero_mem(&local_58,0x38);
  os_zero_mem(&local_78,0x20);
  local_58 = (uint)param_2[2];
  local_54 = (uint)param_2[3];
  local_50 = (uint)param_2[4];
  local_4c = (uint)param_2[5];
  local_48 = (uint)param_2[6];
  local_44 = (uint)param_2[7];
  if ((*(code **)(iVar4 + 0x16c) == (code *)0x0) ||
     (cVar3 = (**(code **)(iVar4 + 0x16c))(*(undefined4 *)(param_1 + 0xa797a0),1,0,&local_58),
     cVar3 == '\0')) {
    if (-1 < DebugLevel) {
      printk("set_txbf_angle failed for nc:%d\n",0);
    }
  }
  else {
    os_zero_mem(&local_58,0x38);
    local_58 = (uint)param_2[8];
    local_54 = (uint)param_2[9];
    local_50 = (uint)param_2[10];
    local_4c = (uint)param_2[0xb];
    if ((*(code **)(iVar4 + 0x16c) == (code *)0x0) ||
       (cVar3 = (**(code **)(iVar4 + 0x16c))(*(undefined4 *)(param_1 + 0xa797a0),1,1,&local_58),
       cVar3 != '\0')) {
      os_zero_mem(&local_58,0x38);
      local_58 = (uint)param_2[0xc];
      local_54 = (uint)param_2[0xd];
      if ((*(code **)(iVar4 + 0x16c) == (code *)0x0) ||
         (cVar3 = (**(code **)(iVar4 + 0x16c))(*(undefined4 *)(param_1 + 0xa797a0),1,2,&local_58),
         cVar3 != '\0')) {
        local_78 = (uint)param_2[0xe];
        uStack_74 = (uint)param_2[0xf];
        uStack_70 = (uint)param_2[0x10];
        uStack_6c = (uint)param_2[0x11];
        if ((*(code **)(iVar4 + 0x170) == (code *)0x0) ||
           (cVar3 = (**(code **)(iVar4 + 0x170))(*(undefined4 *)(param_1 + 0xa797a0),1,&local_78),
           cVar3 != '\0')) {
          if (*(code **)(iVar4 + 0x174) == (code *)0x0) {
            return cVar3;
          }
          cVar3 = (**(code **)(iVar4 + 0x174))
                            (*(undefined4 *)(param_1 + 0xa797a0),uVar1 & 0xff,uVar2,1);
          if (cVar3 != '\0') {
            return cVar3;
          }
          if (-1 < DebugLevel) {
            printk("write_txbf_pfmu_data failed for pfmu_id:%u and subcarrier:%u\n",uVar1 & 0xff,
                   uVar2);
          }
        }
        else if (-1 < DebugLevel) {
          printk("set_txbf_dsnr failed\n");
        }
      }
      else if (-1 < DebugLevel) {
        printk("set_txbf_angle failed for nc:%d\n",2);
      }
    }
    else if (-1 < DebugLevel) {
      printk("set_txbf_angle failed for nc:%d\n",1);
    }
  }
  return '\0';
}

