// module: mt7915.ko
// function: AsicAdjustTxPower @ 0x144f84
// size: 796 bytes
//

void AsicAdjustTxPower(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  uint uVar8;
  char local_50;
  char local_4f;
  char local_4e;
  char local_4d;
  uint local_4c;
  undefined4 local_48;
  uint local_44 [10];
  
  local_50 = '\0';
  local_4f = '\0';
  local_4e = '\0';
  local_4d = '\0';
  local_4c = 0;
  local_48 = 0;
  local_44[0] = 0;
  local_44[1] = 0;
  local_44[2] = 0;
  local_44[3] = 0;
  local_44[4] = 0;
  local_44[5] = 0;
  local_44[6] = 0;
  local_44[7] = 0;
  local_44[8] = 0;
  uVar2 = HcGetRadioChannel();
  if ((*(uint *)(param_1 + 0xa39f84) & 0x40000000) == 0) {
    iVar3 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar3 == 2) {
      if (0 < DebugLevel) {
        printk("%s(): Not finish for HIF_MT yet!\n","AsicAdjustTxPower");
      }
    }
    else {
      if (*(byte *)(param_1 + 0x794ab8) != 0) {
        pcVar4 = &DAT_0036e600 + param_1;
        iVar3 = 0;
        do {
          iVar3 = iVar3 + 1;
          if (((*pcVar4 != '\0') && (pcVar4[0x211a18] != '\0')) &&
             ((*(uint *)(param_1 + 0xa39f84) & 0x4000) != 0)) {
            return;
          }
          pcVar4 = pcVar4 + 0x2137b0;
        } while (iVar3 < (int)(uint)*(byte *)(param_1 + 0x794ab8));
      }
      iVar3 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
      if ((*(char *)(iVar3 + 0x90) != '\x01') && ((*(uint *)(param_1 + 0xa39f84) & 0x40000000) == 0)
         ) {
        if ((*(char *)(param_1 + 0x286285) == '\0') &&
           ((*(uint *)(&DAT_0057ffbc + param_1) & 1) != 0)) {
          cVar1 = RTMPMaxRssi(param_1,(int)(char)(&DAT_00580d24)[param_1],
                              (int)(char)(&DAT_00580d25)[param_1],
                              (int)(char)(&DAT_00580d26)[param_1]);
        }
        else {
          cVar1 = -0x7f;
        }
        iVar3 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
        if (*(code **)(iVar3 + 100) != (code *)0x0) {
          (**(code **)(iVar3 + 100))(param_1,&local_4c);
        }
        iVar3 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
        if (*(code **)(iVar3 + 0x60) != (code *)0x0) {
          (**(code **)(iVar3 + 0x60))(param_1,&local_50,&local_4d,&local_4f,&local_4e,uVar2);
        }
        if (3 < DebugLevel) {
          printk("%s(): DeltaPwr=%d, TotalDeltaPower=%d, TxAgcCompensate=%d, DeltaPowerByBbpR1=%d\n"
                 ,"AsicAdjustTxPower",(int)local_50,(int)local_4d,(int)local_4f,(int)local_4e);
        }
        AsicPercentageDeltaPower(param_1,(int)cVar1,&local_50,&local_4e);
        local_4d = local_4e + local_4d + local_50;
        AsicCompensatePowerViaBBP(param_1,&local_4d);
        if ((*(uint *)(param_1 + 0x82921c) & 3) == 0) {
          uVar5 = local_4c & 0xff;
          if (uVar5 != 0) {
            puVar7 = &local_4c;
            iVar3 = 0;
            do {
              uVar8 = puVar7[2];
              if (uVar8 != 0xffffffff) {
                uVar5 = 0;
                do {
                  uVar6 = (uint)(char)(local_4d + ((byte)(uVar8 >> (uVar5 & 0xff)) & 0xf));
                  if (0xb < (int)uVar6) {
                    uVar6 = 0xc;
                  }
                  uVar8 = uVar8 & ~(0xf << (uVar5 & 0xff)) |
                          (uVar6 & ~((int)uVar6 >> 0x1f)) << (uVar5 & 0xff);
                  uVar5 = uVar5 + 4;
                } while (uVar5 != 0x20);
                uVar2 = *(undefined4 *)(param_1 + 0xa797a0);
                puVar7[2] = uVar8;
                mac_io_write32(uVar2,(short)puVar7[1],uVar8);
                uVar5 = local_4c & 0xff;
              }
              iVar3 = iVar3 + 1;
              puVar7 = puVar7 + 2;
            } while (iVar3 < (int)uVar5);
          }
          iVar3 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
          if (*(code **)(iVar3 + 0x68) != (code *)0x0) {
            (**(code **)(iVar3 + 0x68))(param_1);
          }
        }
      }
    }
  }
  return;
}

