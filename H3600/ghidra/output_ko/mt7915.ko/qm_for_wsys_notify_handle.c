// module: mt7915.ko
// function: qm_for_wsys_notify_handle @ 0xcfdcc
// size: 120 bytes
//

undefined4 qm_for_wsys_notify_handle(int param_1,int param_2,int *param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 0xc);
  iVar3 = *param_3;
  iVar2 = *(int *)("Get_RBIST_Raw_Data_Proc" + iVar1 + 0x14);
  if (2 < DebugLevel) {
    printk("%s(): event_id: %d, wdev=%d\n","qm_for_wsys_notify_handle",param_2,
           *(undefined1 *)(iVar3 + 0xc),param_4);
  }
  if ((param_2 == 1) && (*(code **)(iVar2 + 0x10) != (code *)0x0)) {
    (**(code **)(iVar2 + 0x10))(iVar1,iVar3);
  }
  return 1;
}

