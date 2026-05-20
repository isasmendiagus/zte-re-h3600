// module: mt7915.ko
// function: mt_agent_hqa_cmd_string_parser @ 0x24f1e0
// size: 1380 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 mt_agent_hqa_cmd_string_parser(char *param_1,undefined1 *param_2)

{
  ushort uVar1;
  size_t sVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  uint uVar9;
  char *pcVar10;
  char cVar11;
  undefined2 uVar12;
  int local_f4;
  int local_f0 [2];
  undefined1 *local_e8;
  undefined2 local_e2;
  undefined2 local_e0;
  undefined2 local_de;
  undefined4 local_dc [20];
  undefined1 auStack_8c [104];
  
  local_f0[0] = 0;
  memset(local_dc,0,0x50);
  iVar8 = 0;
  iVar6 = 0;
  memset(auStack_8c,0,100);
  local_e2 = 0;
  local_e0 = 0;
  local_de = 0;
  local_f0[1] = 0;
  local_e8 = (undefined1 *)0x0;
  while( true ) {
    pcVar7 = *(char **)((int)&DAT_002a45b4 + iVar8);
    iVar8 = iVar8 + 0x1c;
    sVar2 = strlen(pcVar7);
    iVar3 = strncasecmp(param_1,pcVar7,sVar2);
    if (iVar3 == 0) break;
    iVar6 = iVar6 + 1;
    if (iVar6 == 0xb) {
      return 0x105;
    }
  }
  pcVar7 = strchr(param_1,0x3d);
  if (pcVar7 == (char *)0x0) {
LAB_0024f594:
    sVar2 = 0;
    param_2[4] = 0;
    param_2[5] = 0;
    uVar12 = 0;
    uVar1 = (&DAT_002a45b8)[iVar6 * 0xe];
    *param_2 = 0x18;
  }
  else {
    pcVar7 = pcVar7 + 1;
    if (pcVar7 == (char *)0x0) {
      printk("parameter is NULL: %p, %p, %p\n",0,local_f0,local_dc);
    }
    else {
      sVar2 = strnlen(pcVar7,0x200);
      if (sVar2 < 0x200) {
        iVar8 = 0;
        pcVar5 = (char *)0x0;
        local_f0[0] = 0;
LAB_0024f2c4:
        if (iVar8 == 0) {
switchD_0024f2e0_caseD_9:
          pcVar5 = pcVar7;
          cVar11 = *pcVar5;
          iVar3 = (int)cVar11;
          pcVar7 = pcVar5 + 1;
          switch(iVar3) {
          case 0:
          case 10:
            break;
          default:
            pcVar4 = pcVar5;
            pcVar10 = pcVar5;
LAB_0024f558:
            if (iVar3 == 0xd) goto LAB_0024f6b4;
            if (iVar3 < 0xe) {
              if (iVar3 == 9) goto LAB_0024f6b4;
              if (iVar3 == 10) {
                pcVar7 = pcVar10 + 1;
                iVar8 = 2;
                goto LAB_0024f6a4;
              }
              pcVar7 = pcVar10;
              if (iVar3 == 0) goto LAB_0024f6a4;
            }
            else {
              pcVar7 = pcVar10;
              if (iVar3 == 0x22) {
                while( true ) {
                  cVar11 = pcVar7[1];
                  if (cVar11 == '\0') goto switchD_0024f2e0_caseD_0;
                  if (cVar11 == '\"') break;
                  *pcVar4 = cVar11;
                  pcVar4 = pcVar4 + 1;
                  pcVar7 = pcVar7 + 1;
                }
                pcVar10 = pcVar7 + 2;
                cVar11 = pcVar7[2];
                iVar3 = (int)cVar11;
                goto LAB_0024f558;
              }
              if (iVar3 < 0x23) {
                if (iVar3 != 0x20) goto LAB_0024f57c;
                goto LAB_0024f6b4;
              }
              if (iVar3 == 0x2c) goto LAB_0024f6b4;
              if (iVar3 == 0x5c) {
                cVar11 = pcVar10[1];
                pcVar7 = pcVar10 + 1;
                if (cVar11 == '\\') {
                  *pcVar4 = '\\';
                  pcVar4 = pcVar4 + 1;
                  cVar11 = pcVar10[1];
                  iVar3 = (int)cVar11;
                  pcVar10 = pcVar7;
                  goto LAB_0024f558;
                }
                if ('\\' < cVar11) {
                  if (cVar11 == 'r') {
                    cVar11 = '\r';
                  }
                  else {
                    if (cVar11 != 't') {
                      if (cVar11 != 'n') goto LAB_0024f684;
                      *pcVar4 = '\n';
                      pcVar4 = pcVar4 + 1;
                      cVar11 = pcVar10[1];
                      iVar3 = (int)cVar11;
                      pcVar10 = pcVar7;
                      goto LAB_0024f558;
                    }
                    cVar11 = '\t';
                  }
                  *pcVar4 = cVar11;
                  pcVar4 = pcVar4 + 1;
                  cVar11 = pcVar10[1];
                  iVar3 = (int)cVar11;
                  pcVar10 = pcVar7;
                  goto LAB_0024f558;
                }
                if (cVar11 == '\n') {
                  pcVar10 = pcVar10 + 2;
                  cVar11 = *pcVar10;
                  iVar3 = (int)cVar11;
                  if (iVar3 == 0x20 || iVar3 == 9) {
                    do {
                      pcVar10 = pcVar10 + 1;
                      cVar11 = *pcVar10;
                      iVar3 = (int)cVar11;
                    } while (iVar3 == 0x20 || iVar3 == 9);
                  }
                }
                else if (cVar11 == '\r') {
                  cVar11 = pcVar10[2];
                  iVar3 = (int)cVar11;
                  pcVar10 = pcVar10 + 2;
                }
                else {
                  if (cVar11 == '\0') goto LAB_0024f6a4;
LAB_0024f684:
                  *pcVar4 = cVar11;
                  cVar11 = pcVar10[2];
                  pcVar4 = pcVar4 + 1;
                  iVar3 = (int)cVar11;
                  pcVar10 = pcVar10 + 2;
                }
                goto LAB_0024f558;
              }
            }
LAB_0024f57c:
            *pcVar4 = cVar11;
            cVar11 = pcVar10[1];
            pcVar4 = pcVar4 + 1;
            iVar3 = (int)cVar11;
            pcVar10 = pcVar10 + 1;
            goto LAB_0024f558;
          case 9:
          case 0xd:
          case 0x20:
          case 0x2c:
            goto switchD_0024f2e0_caseD_9;
          case 0x23:
            do {
              pcVar5 = pcVar5 + 1;
            } while (*pcVar5 != '\n' && *pcVar5 != '\0');
          }
        }
        else {
          if (iVar8 == 1) {
            iVar8 = 0;
            goto LAB_0024f538;
          }
          if (iVar8 != 2) {
            iVar8 = 0;
            goto switchD_0024f2e0_caseD_9;
          }
        }
switchD_0024f2e0_caseD_0:
      }
      else {
        printk("cmd_line >= 512\n");
      }
    }
    if (local_f0[0] < 1) {
      if (local_f0[0] == 0) goto LAB_0024f594;
      sVar2 = 0;
      local_f4 = iVar6 << 3;
    }
    else {
      cVar11 = '\0';
      do {
        cVar11 = cVar11 + '\x01';
      } while (cVar11 < local_f0[0]);
      local_f4 = iVar6 * 8;
      iVar8 = 0;
      local_e8 = auStack_8c;
      sVar2 = 0;
      cVar11 = '\0';
      do {
        uVar9 = (uint)(byte)(&DAT_002a45ba)[iVar6 * 0x1c + iVar8];
        sVar2 = sVar2 + uVar9 & 0xffff;
        if (uVar9 == 6) {
          uVar9 = sscanf((char *)local_dc[iVar8],"%02x:%02x:%02x:%02x:%02x:%02x",&local_e2,
                         (int)&local_e2 + 1,&local_e0,(int)&local_e0 + 1,&local_de,
                         (int)&local_de + 1);
          if ((uVar9 & 0xffff) != 0) {
            FUN_00246ac8(0,6,&local_e2,&local_e8);
          }
        }
        else {
          if (uVar9 == 4) {
            kstrtouint(local_dc[iVar8],0,local_f0 + 1);
          }
          else {
            if (uVar9 != 2) {
              kstrtou8(local_dc[iVar8],0,local_f0 + 1);
              FUN_00246ac8(1,uVar9,local_f0 + 1,&local_e8);
              goto LAB_0024f420;
            }
            kstrtou16(local_dc[iVar8],0,local_f0 + 1);
          }
          FUN_00246ac8(1,uVar9,local_f0 + 1,&local_e8);
        }
LAB_0024f420:
        cVar11 = cVar11 + '\x01';
        iVar8 = (int)cVar11;
      } while (iVar8 < local_f0[0]);
    }
    uVar12 = (undefined2)sVar2;
    *param_2 = 0x18;
    param_2[4] = 0;
    param_2[5] = 0;
    uVar1 = (&DAT_002a45b8)[(local_f4 - iVar6) * 2];
  }
  param_2[1] = 0x14;
  param_2[2] = 0x28;
  param_2[3] = 0x80;
  *(undefined2 *)(param_2 + 8) = uVar12;
  *(ushort *)(param_2 + 6) = uVar1 << 8 | uVar1 >> 8;
  param_2[10] = 0;
  param_2[0xb] = 0;
  memcpy(param_2 + 0xc,auStack_8c,sVar2);
  return 0;
LAB_0024f6b4:
  pcVar7 = pcVar10 + 1;
LAB_0024f6a4:
  *pcVar4 = '\0';
LAB_0024f538:
  if (local_f0[0] < 0x14) {
    local_dc[local_f0[0]] = pcVar5;
    local_f0[0] = local_f0[0] + 1;
  }
  goto LAB_0024f2c4;
}

