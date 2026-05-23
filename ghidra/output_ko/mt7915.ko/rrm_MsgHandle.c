// module: mt7915.ko
// function: rrm_MsgHandle @ 0x2215c8
// size: 600 bytes
//

undefined4 rrm_MsgHandle(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 auStack_18 [4];
  undefined1 *local_14 [2];
  
  local_14[0] = (undefined1 *)0x0;
  os_alloc_mem(0,local_14,*(undefined2 *)(param_2 + 0x14));
  if (local_14[0] == (undefined1 *)0x0) {
    if (DebugLevel < 1) {
      return 1;
    }
    printk("!!!(%s) : no memory!!!\n","rrm_MsgHandle");
    return 1;
  }
  uVar2 = (uint)*(ushort *)(param_2 + 0x14);
  uVar3 = *(uint *)(((uint)auStack_18 & 0xffffe000) + 8);
  if (!CARRY4(*(uint *)(param_2 + 0x10),uVar2) && *(uint *)(param_2 + 0x10) + uVar2 <= uVar3) {
    uVar3 = 0;
  }
  if (uVar3 == 0) {
    iVar1 = __copy_from_user(local_14[0]);
    if (iVar1 != 0) goto LAB_00221674;
  }
  else if (uVar2 != 0) {
    __memzero(local_14[0],uVar2);
LAB_00221674:
    if (-1 < DebugLevel) {
      printk("!!!(%s) : copy_from_user fail!!!\n","rrm_MsgHandle");
    }
    os_free_mem(local_14[0]);
    return 1;
  }
  iVar1 = DebugLevel;
  switch(*local_14[0]) {
  case 1:
    if (*(int *)(local_14[0] + 1) == 1) {
      uVar4 = Set_Dot11kRRM_Enable(param_1,local_14[0][5]);
      break;
    }
    goto LAB_00221734;
  case 2:
    if (*(int *)(local_14[0] + 1) == 8) {
      uVar4 = set_rrm_capabilities(param_1,local_14[0] + 5);
      break;
    }
LAB_00221734:
    if (DebugLevel < 1) {
      uVar4 = 1;
    }
    else {
      uVar4 = 1;
      printk("Unexpected command len (%d)");
    }
    break;
  case 3:
    uVar4 = rrm_send_beacon_req(param_1,local_14[0] + 5,*(undefined4 *)(local_14[0] + 1));
    break;
  default:
    goto switchD_0022163c_caseD_4;
  case 5:
    uVar4 = rrm_send_beacon_req_param(param_1,local_14[0] + 5,*(undefined4 *)(local_14[0] + 1));
    break;
  case 6:
    uVar4 = rrm_send_nr_rsp_ie(param_1,local_14[0] + 5,*(undefined4 *)(local_14[0] + 1));
    break;
  case 7:
    uVar4 = rrm_send_nr_rsp_param(param_1,local_14[0] + 5,*(undefined4 *)(local_14[0] + 1));
    break;
  case 8:
    (&DAT_0036daa0)[param_1] = local_14[0][5] != '\0';
    if (2 < iVar1) {
      uVar4 = 0;
      printk("%s, HandleNRReqbyUplayer(%d)!\n","rrm_set_handle_nr_req_flag");
      break;
    }
    goto switchD_0022163c_caseD_4;
  }
LAB_002216dc:
  os_free_mem(local_14[0]);
  return uVar4;
switchD_0022163c_caseD_4:
  uVar4 = 0;
  goto LAB_002216dc;
}

