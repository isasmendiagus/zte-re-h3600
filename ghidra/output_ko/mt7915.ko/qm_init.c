// module: mt7915.ko
// function: qm_init @ 0xd37a0
// size: 240 bytes
//

int qm_init(int param_1)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  undefined1 *puVar4;
  
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  cVar2 = *(char *)(iVar3 + 0x158);
  if (cVar2 == '\0') {
    puVar4 = ge_qm_ops;
    *(undefined1 **)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14) = ge_qm_ops;
  }
  else if (cVar2 == '\x01') {
    puVar4 = fp_qm_ops;
    *(undefined1 **)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14) = fp_qm_ops;
  }
  else if (cVar2 == '\x02') {
    puVar4 = ge_fair_qm_ops;
    *(undefined1 **)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14) = ge_fair_qm_ops;
  }
  else if (cVar2 == '\x03') {
    puVar4 = fp_fair_qm_ops;
    *(undefined1 **)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14) = fp_fair_qm_ops;
  }
  else {
    puVar4 = *(undefined1 **)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  }
  iVar3 = (**(code **)puVar4)(param_1);
  if (iVar3 == 0) {
    *(code **)("Get_RBIST_IQ_Data" + param_1) = qm_for_wsys_notify_handle;
    *(int *)("Get_RBIST_IQ_Data" + param_1 + 0xc) = param_1;
    pcVar1 = "Get_RBIST_IQ_Data" + param_1 + 8;
    pcVar1[0] = '\x01';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    register_wsys_notifier(param_1 + 0xa7bed4,"Get_RBIST_IQ_Data" + param_1);
  }
  return iVar3;
}

