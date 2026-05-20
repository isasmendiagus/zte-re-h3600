// module: mt7915.ko
// function: Set_MeasureReq_Proc @ 0x13fed4
// size: 684 bytes
//

undefined4 Set_MeasureReq_Proc(int param_1,char *param_2)

{
  byte bVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  char *local_54;
  void *local_50;
  int local_4c;
  int local_48;
  byte local_43 [35];
  
  local_54 = param_2;
  uVar3 = RandomByte();
  local_50 = (void *)0x0;
  iVar4 = os_alloc_mem(param_1,&local_50,0x900);
  if (iVar4 == 0) {
    bVar2 = 1;
    iVar4 = 1;
    uVar7 = 1;
    bVar1 = 0;
    while (pcVar5 = strsep(&local_54,"-"), pcVar5 != (char *)0x0) {
      if (iVar4 == 2) {
        bVar1 = os_str_tol(pcVar5,0,0x10);
        if (3 < bVar1) {
          if (-1 < DebugLevel) {
            printk("%s: unknow MeasureReqType(%d)\n","Set_MeasureReq_Proc",bVar1);
          }
          goto LAB_0013ff20;
        }
      }
      else if (iVar4 == 3) {
        bVar2 = os_str_tol(pcVar5,0,0x10);
      }
      else if (iVar4 == 1) {
        uVar7 = os_str_tol(pcVar5,0,0x10);
        uVar7 = uVar7 & 0xffff;
      }
      iVar4 = iVar4 + 1;
    }
    if (2 < DebugLevel) {
      printk("%s::wcid = %d, MeasureReqType=%d MeasureCh=%d\n","Set_MeasureReq_Proc",uVar7,bVar1,
             bVar2);
    }
    uVar6 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (uVar7 < uVar6) {
      MeasureReqInsert(param_1,uVar3);
      MgtMacHeaderInit(param_1,local_43 + 0xb,0xd,0,uVar7 * 0x14c0 + param_1 + 0xa1e0c,
                       param_1 + 0x794b5b,param_1 + 0x794b5b);
      memmove(local_50,local_43 + 0xb,0x18);
      local_4c = 0x18;
      MakeMeasurementReqFrame(param_1,local_50,&local_4c,3,5,0,uVar3,2,bVar1,1);
      local_43[1] = 0;
      local_43[2] = 0;
      local_43[3] = 0;
      local_43[4] = 0;
      local_43[5] = 0;
      local_43[6] = 0;
      local_43[7] = 0;
      local_43[8] = 0;
      local_43[9] = 0xd0;
      local_43[10] = 7;
      local_43[0] = bVar2;
      MakeOutgoingFrame((int)local_50 + local_4c,&local_48,0xb,local_43,0xffffffff);
      local_4c = local_48 + local_4c;
      MiniportMMRequest(param_1,1,local_50);
    }
    else if (-1 < DebugLevel) {
      printk("%s: unknow sta of wcid(%d)\n","Set_MeasureReq_Proc",uVar7);
    }
  }
  else if (2 < DebugLevel) {
    printk("%s() allocate memory failed\n","Set_MeasureReq_Proc");
  }
LAB_0013ff20:
  os_free_mem(local_50);
  return 1;
}

