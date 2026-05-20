// module: idmfdb.ko
// function: register_idm_led @ 0x12710
// size: 140 bytes
//

undefined4 register_idm_led(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1 * 0x40;
  *(int *)(&led_handle + param_1 * 0x40) = param_1;
  *(undefined4 *)(&DAT_00017e78 + iVar1) = param_2;
  (&DAT_00017e74)[iVar1] = 1;
  *(undefined4 *)(&DAT_00017e7c + iVar1) = param_3;
  *(undefined4 *)(&DAT_00017eac + iVar1) = param_4;
  (&DAT_00017ea4)[param_1 * 0x10] = 0;
  init_timer_key(&DAT_00017e88 + iVar1,0,0,0);
  iVar2 = jiffies;
  *(code **)(&DAT_00017e98 + iVar1) = idm_led_timer_handle;
  *(undefined1 **)(&DAT_00017e9c + iVar1) = &led_handle + iVar1;
  mod_timer(&DAT_00017e88 + iVar1,iVar2 + 500);
  create_led_proc_file(&led_handle + iVar1);
  return 0;
}

