// module: mt7915.ko
// function: set_txcmd_sxn_user_dw @ 0x99fa4
// size: 968 bytes
//

undefined4 set_txcmd_sxn_user_dw(undefined4 param_1,char *param_2)

{
  byte *pbVar1;
  undefined1 uVar2;
  byte bVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  uint uVar12;
  int iVar13;
  byte bVar14;
  int iVar15;
  char *local_34 [2];
  uint *local_2c [2];
  
  local_34[0] = param_2;
  pcVar4 = strsep(local_34,"-");
  if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
    uVar2 = os_str_tol(pcVar4,0,10);
    pcVar4 = strsep(local_34,"-");
    if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
      uVar5 = os_str_tol(pcVar4,0,10);
      pcVar4 = strsep(local_34,"-");
      if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
        uVar6 = os_str_tol(pcVar4,0,10);
        pcVar4 = strsep(local_34,"-");
        if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
          uVar7 = os_str_tol(pcVar4,0,10);
          pcVar4 = strsep(local_34,"-");
          if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
            uVar8 = os_str_tol(pcVar4,0,10);
            pcVar4 = strsep(local_34,"-");
            if ((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) {
              iVar9 = os_str_tol(pcVar4,0,0x10);
              uVar12 = uVar5 & 0xff;
              pcVar4 = strsep(local_34,"-");
              if ((pcVar4 == (char *)0x0) || (*pcVar4 == '\0')) {
                bVar3 = 0;
LAB_0009a14c:
                switch(uVar2) {
                case 1:
switchD_0009a158_caseD_1:
                  if (uVar12 < 0x10) {
                    bVar14 = 4;
                    iVar13 = 2;
LAB_0009a1b0:
                    iVar15 = iVar13 * 2 + 4;
                    iVar10 = os_alloc_mem(param_1,local_2c,iVar15);
                    if (iVar10 != 1) {
                      uVar6 = uVar6 & 0xff;
                      os_zero_mem(local_2c[0],iVar15);
                      iVar10 = iVar13 + uVar6 * 4 + 4;
                      *(byte *)local_2c[0] = (byte)*local_2c[0] & 0xc0 | bVar14;
                      uVar12 = *local_2c[0];
                      *local_2c[0] = uVar12 & 0xffc0003f | iVar13 << 7;
                      uVar5 = (uVar12 & 0xffc0003f) >> 0x10 & 0xffffe03f | (uVar5 & 0x7f) << 6;
                      *(short *)((int)local_2c[0] + 2) = (short)uVar5;
                      *(byte *)((int)local_2c[0] + 3) = (byte)(uVar5 >> 8) & 0x1f | bVar3 << 5;
                      local_2c[0][uVar6 + 1] = local_2c[0][uVar6 + 1] | iVar9 << (uVar7 & 0xff);
                      if ((uVar8 & 0xff) < 0x20) {
                        *(uint *)((int)local_2c[0] + iVar10) =
                             *(uint *)((int)local_2c[0] + iVar10) |
                             ~(-1 << (uVar8 & 0xff)) << (uVar7 & 0xff);
                      }
                      else {
                        pbVar1 = (byte *)((int)local_2c[0] + iVar10);
                        pbVar1[0] = 0xff;
                        pbVar1[1] = 0xff;
                        pbVar1[2] = 0xff;
                        pbVar1[3] = 0xff;
                      }
                      uVar11 = send_cmd_msg(param_1,local_2c[0],0);
                      os_free_mem(local_2c[0]);
                      goto LAB_00099ff0;
                    }
                    goto switchD_0009a33c_caseD_4;
                  }
                  break;
                case 2:
switchD_0009a158_caseD_2:
                  if (uVar12 < 0x10) {
                    bVar14 = 6;
                    iVar13 = 0x20;
                    goto LAB_0009a1b0;
                  }
                  break;
                case 3:
switchD_0009a158_caseD_3:
                  if (uVar12 < 0x10) {
                    bVar14 = 8;
                    iVar13 = 0x10;
                    goto LAB_0009a1b0;
                  }
                  break;
                case 5:
switchD_0009a158_caseD_5:
                  if (uVar12 < 0x10) {
                    bVar14 = 0xb;
                    iVar13 = 6;
                    goto LAB_0009a1b0;
                  }
                  break;
                case 6:
switchD_0009a158_caseD_6:
                  if (uVar12 < 0x10) {
                    bVar14 = 0xd;
                    iVar13 = 8;
                    goto LAB_0009a1b0;
                  }
                  break;
                case 7:
switchD_0009a158_caseD_7:
                  if (uVar12 < 0x10) {
                    bVar14 = 0xe;
                    iVar13 = 0x40;
                    goto LAB_0009a1b0;
                  }
                }
                if (-1 < DebugLevel) {
                  printk("%s: index exceed than %d\n","set_txcmd_sxn_user_dw",0x10);
                  uVar11 = 1;
                  goto LAB_00099ff0;
                }
              }
              else {
                bVar3 = os_str_tol(pcVar4,0,0x10);
                if (bVar3 < 2) goto LAB_0009a14c;
                if (-1 < DebugLevel) {
                  printk("%s: invalid txcmd_entry_idx : %d. Set to 0\n","set_txcmd_sxn_user_dw",
                         bVar3);
                  bVar3 = 0;
                  goto LAB_0009a14c;
                }
                switch(uVar2) {
                case 1:
                  bVar3 = 0;
                  goto switchD_0009a158_caseD_1;
                case 2:
                  bVar3 = 0;
                  goto switchD_0009a158_caseD_2;
                case 3:
                  bVar3 = 0;
                  goto switchD_0009a158_caseD_3;
                case 5:
                  bVar3 = 0;
                  goto switchD_0009a158_caseD_5;
                case 6:
                  bVar3 = 0;
                  goto switchD_0009a158_caseD_6;
                case 7:
                  bVar3 = 0;
                  goto switchD_0009a158_caseD_7;
                }
              }
switchD_0009a33c_caseD_4:
              uVar11 = 1;
              goto LAB_00099ff0;
            }
          }
        }
      }
    }
  }
  set_dw_usage(1);
  uVar11 = 1;
LAB_00099ff0:
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","set_txcmd_sxn_user_dw",uVar11);
  }
  return uVar11;
}

