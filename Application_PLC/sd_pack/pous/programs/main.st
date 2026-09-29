(* Melacs SEAS. Adresserna följer register_map.json.
   H1_DIS och H2_DIS ska vara TRUE så länge bryggorna ska vara av.
   TRUE på spärren håller JP18 och JP19 av. *)

PROGRAM main
  VAR
    dio0 AT %IX0.0 : BOOL;
    dio1 AT %IX0.1 : BOOL;
    dio2 AT %IX0.2 : BOOL;
    dio3 AT %IX0.3 : BOOL;
    sd_ok AT %IX1.0 : BOOL;
    logger_ok AT %IX1.1 : BOOL;
    plc_loaded AT %IX1.2 : BOOL;
    plc_running AT %IX1.3 : BOOL;
    ad0 AT %IW0 : WORD;
    ad1 AT %IW1 : WORD;
    ad2 AT %IW2 : WORD;
    ad3 AT %IW3 : WORD;
    ad4 AT %IW4 : WORD;
    ad5 AT %IW5 : WORD;
    ad6 AT %IW6 : WORD;
    ad7 AT %IW7 : WORD;
    ai10 AT %IW10 : WORD;
    ai11 AT %IW11 : WORD;
    ai12 AT %IW12 : WORD;
    ai13 AT %IW13 : WORD;
    ai14 AT %IW14 : WORD;
    ai15 AT %IW15 : WORD;
    error_code AT %IW20 : WORD;
    t_board AT %IW30 : WORD;
    p_value AT %IW31 : WORD;
    t1 AT %IW32 : WORD;
    t2 AT %IW33 : WORD;
    value AT %IW34 : WORD;
    dio4 AT %QX0.0 : BOOL;
    dio5 AT %QX0.1 : BOOL;
    dio6 AT %QX0.2 : BOOL;
    dio7 AT %QX0.3 : BOOL;
    sip0 AT %QX4.0 : BOOL;
    sip1 AT %QX4.1 : BOOL;
    sip2 AT %QX4.2 : BOOL;
    sip3 AT %QX4.3 : BOOL;
    sip4 AT %QX4.4 : BOOL;
    sip5 AT %QX4.5 : BOOL;
    sip6 AT %QX4.6 : BOOL;
    sip7 AT %QX4.7 : BOOL;
    h1_dis AT %QX5.0 : BOOL;
    h1_ali AT %QX5.1 : BOOL;
    h1_bli AT %QX5.2 : BOOL;
    h2_dis AT %QX5.3 : BOOL;
    h2_ali AT %QX5.4 : BOOL;
    h2_bli AT %QX5.5 : BOOL;
    ao0 AT %QW0 : WORD;
    ao1 AT %QW1 : WORD;
    ao2 AT %QW2 : WORD;
    h1_ahi AT %QW10 : WORD;
    h1_bhi AT %QW11 : WORD;
    h2_ahi AT %QW12 : WORD;
    h2_bhi AT %QW13 : WORD;
    note AT %QW14 : WORD;
    safe_mode AT %MW0 : WORD;
    log_period_s AT %MW1 : WORD;
    rtc_year AT %MW2 : WORD;
    rtc_month AT %MW3 : WORD;
    rtc_day AT %MW4 : WORD;
    rtc_hour AT %MW5 : WORD;
    rtc_minute AT %MW6 : WORD;
    rtc_second AT %MW7 : WORD;
    rtc_weekday AT %MW8 : WORD;
    rtc_set AT %MW9 : WORD;
  END_VAR

  h1_dis := TRUE;
  h2_dis := TRUE;
END_PROGRAM
