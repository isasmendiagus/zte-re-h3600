// module: mt7915.ko
// function: twt_ctrl_resource_status_dump @ 0x16ab68
// size: 1044 bytes
//

void twt_ctrl_resource_status_dump(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  if (param_1 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: ctrl=NULL, please check\n","twt_ctrl_resource_status_dump");
    return;
  }
  if (DebugLevel < 1) {
    iVar3 = DebugLevel;
    if (*(char *)(param_1 + 0x2c38) == '\0') goto LAB_0016ad68;
LAB_0016aba0:
    uVar2 = 0;
    iVar3 = DebugLevel;
    do {
      iVar5 = uVar2 * 0x48;
      iVar6 = param_1 + 0x2000 + iVar5;
      if ((*(char *)(iVar6 + 0xc74) == '\0') && (0 < iVar3)) {
        iVar3 = param_1 + 0x2c40 + iVar5;
        iVar7 = param_1 + 0x2c38 + iVar5;
        printk("\t**i_idx=%d,p=%p,tbl_i=%d,ste=%d,o_i=%d,b_i=%d,wcid=%d,spd=%d,f_i=%d,sp=%d,m=%d,e=%d,para=0x%x,tsf_sch=(%x,%x),\n"
               ,uVar2,param_1 + iVar5 + 0x2c40,*(undefined1 *)(iVar6 + 0xc49),
               *(undefined1 *)(iVar6 + 0xc48),*(undefined1 *)(iVar6 + 0xc4a),
               *(undefined1 *)(iVar6 + 0xc4f),*(undefined2 *)(iVar7 + 0x14),
               *(undefined1 *)(iVar6 + 0xc75),*(undefined1 *)(iVar6 + 0xc4b),
               *(undefined1 *)(iVar6 + 0xc4e),*(undefined2 *)(iVar7 + 0x38),
               *(undefined1 *)(iVar6 + 0xc72),*(undefined1 *)(iVar6 + 0xc73),
               *(undefined4 *)(iVar3 + 0x18),*(undefined4 *)(iVar3 + 0x1c));
        iVar3 = DebugLevel;
      }
      uVar2 = uVar2 + 1 & 0xff;
    } while (uVar2 < *(byte *)(param_1 + 0x2c38));
    uVar2 = 0;
    if (*(byte *)(param_1 + 0x2c38) != 0) {
      uVar1 = 0;
      do {
        iVar5 = uVar1 * 0x48;
        iVar6 = param_1 + 0x2000 + iVar5;
        if ((*(char *)(iVar6 + 0xc74) == '\x01') && (0 < iVar3)) {
          iVar3 = param_1 + 0x2c40 + iVar5;
          iVar7 = param_1 + 0x2c38 + iVar5;
          printk("\t**g_idx=%d,p=%p,tbl_i=%d,ste=%d,o_i=%d,b_i=%d,wcid=%d,spd=%d,f_i=%d,sp=%d,m=%d,e=%d,para=0x%x,tsf_sch=(%x,%x),\n\t  grp_grade=%d,grp_cnt=%d,[%d,%d,%d,%d,%d,%d,%d,%d]\n"
                 ,uVar1,param_1 + iVar5 + 0x2c40,*(undefined1 *)(iVar6 + 0xc49),
                 *(undefined1 *)(iVar6 + 0xc48),*(undefined1 *)(iVar6 + 0xc4a),
                 *(undefined1 *)(iVar6 + 0xc4f),*(undefined2 *)(iVar7 + 0x14),
                 *(undefined1 *)(iVar6 + 0xc75),*(undefined1 *)(iVar6 + 0xc4b),
                 *(undefined1 *)(iVar6 + 0xc4e),*(undefined2 *)(iVar7 + 0x38),
                 *(undefined1 *)(iVar6 + 0xc72),*(undefined1 *)(iVar6 + 0xc73),
                 *(undefined4 *)(iVar3 + 0x18),*(undefined4 *)(iVar3 + 0x1c),
                 *(undefined1 *)(iVar6 + 0xc76),*(undefined1 *)(iVar6 + 0xc77),
                 *(undefined2 *)(iVar7 + 0x40),*(undefined2 *)(iVar7 + 0x42),
                 *(undefined2 *)(iVar7 + 0x44),*(undefined2 *)(iVar7 + 0x46),
                 *(undefined2 *)(param_1 + 0x2c38 + (uVar1 + 1) * 0x48),
                 *(undefined2 *)(iVar7 + 0x4a),*(undefined2 *)(iVar7 + 0x4c),
                 *(undefined2 *)(iVar7 + 0x4e));
          iVar3 = DebugLevel;
        }
        uVar2 = (uint)*(byte *)(param_1 + 0x2c38);
        uVar1 = uVar1 + 1 & 0xff;
      } while (uVar1 < uVar2);
    }
  }
  else {
    printk("\n*** twt agrt status ***\n");
    uVar2 = 0;
    iVar3 = DebugLevel;
    if (*(char *)(param_1 + 0x2c38) != '\0') goto LAB_0016aba0;
  }
  if (0 < iVar3) {
    printk("\t*total:%d,i_free:%d,g_free:%d,sch_link=%p,usch_link=%p\n",uVar2,
           *(undefined1 *)(param_1 + 0x2c39),*(undefined1 *)(param_1 + 0x2c3a),param_1 + 0x30c0,
           param_1 + 0x30c8);
    iVar3 = DebugLevel;
  }
LAB_0016ad68:
  iVar7 = 0;
  iVar5 = param_1 + 0x30c0;
  iVar6 = param_1 + 0x30c8;
  while( true ) {
    if (0 < iVar3) {
      iVar3 = 0;
      for (piVar4 = *(int **)(iVar6 + -8); piVar4 != (int *)iVar5; piVar4 = (int *)*piVar4) {
        iVar3 = iVar3 + 1;
      }
      printk("*** twt_link[%d],len=%d ***\n",iVar7,iVar3);
    }
    iVar3 = DebugLevel;
    for (piVar4 = *(int **)(param_1 + (iVar7 + 0x91) * 8 + 0x2c38); DebugLevel = iVar3,
        piVar4 != (int *)iVar5; piVar4 = (int *)*piVar4) {
      if (0 < iVar3) {
        printk("\t**twt_node:tbl_i=%d,s=%d,wcid=%d,spd=%d,f_i=%d,tsf_t=%d,tsf_sch=(%x,%x),sp=%d,align=%d,tsf_info=(%x,%x),tsf_wish(%x,%x)\n"
               ,*(undefined1 *)((int)piVar4 + 9),*(undefined1 *)(piVar4 + 2),
               *(undefined2 *)(piVar4 + 3),*(undefined1 *)((int)piVar4 + 0x35),
               *(undefined1 *)((int)piVar4 + 0xb),*(undefined1 *)(piVar4 + 4),piVar4[6],piVar4[7],
               *(undefined1 *)((int)piVar4 + 0xe),piVar4[6] & 0x3fff,piVar4[10],piVar4[0xb],
               piVar4[8],piVar4[9]);
      }
      iVar3 = DebugLevel;
    }
    if (iVar7 == 1) break;
    iVar7 = 1;
    iVar5 = iVar6;
    iVar6 = iVar6 + 8;
  }
  return;
}

