// module: mt7915.ko
// function: set_txcmd_sxn_dw @ 0x99cbc
// size: 740 bytes
//

undefined4 set_txcmd_sxn_dw(undefined4 param_1,char *param_2)

{
  byte *pbVar1;
  byte bVar2;
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
  char *local_34 [2];
  uint *local_2c [2];
  
  local_34[0] = param_2;
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
            pcVar4 = strsep(local_34,"-");
            if ((pcVar4 == (char *)0x0) || (*pcVar4 == '\0')) {
LAB_00099e2c:
              bVar3 = 0;
            }
            else {
              bVar3 = os_str_tol(pcVar4,0,0x10);
              if (1 < bVar3) {
                if (-1 < DebugLevel) {
                  printk("%s: invalid txcmd_entry_idx : %d. Set to 0\n","set_txcmd_sxn_dw",bVar3);
                }
                goto LAB_00099e2c;
              }
            }
            uVar5 = uVar5 & 0xff;
            if (uVar5 < 7) {
              uVar12 = (uint)*(ushort *)(&DAT_00292d44 + uVar5 * 2);
              bVar2 = (&DAT_00292d54)[uVar5];
            }
            else {
              uVar12 = 0;
              bVar2 = 0xff;
            }
            iVar13 = uVar12 * 2 + 4;
            iVar10 = os_alloc_mem(param_1,local_2c,iVar13);
            uVar11 = 1;
            if (iVar10 != 1) {
              os_zero_mem(local_2c[0],iVar13);
              uVar6 = uVar6 & 0xff;
              iVar10 = uVar12 + uVar6 * 4 + 4;
              *(byte *)local_2c[0] = (byte)*local_2c[0] & 0xc0 | bVar2 & 0x3f;
              uVar5 = *local_2c[0];
              *local_2c[0] = uVar5 & 0xffc0003f | (uVar12 * 2 & 0xffff) << 6;
              *(byte *)((int)local_2c[0] + 3) =
                   (byte)((uVar5 & 0xffc0003f) >> 0x18) & 0x1f | bVar3 << 5;
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
            }
            goto LAB_00099d08;
          }
        }
      }
    }
  }
  set_dw_usage(0);
  uVar11 = 1;
LAB_00099d08:
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","set_txcmd_sxn_dw",uVar11);
  }
  return uVar11;
}

