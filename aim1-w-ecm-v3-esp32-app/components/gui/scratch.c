/* new new start */
    // lv_obj_t *voc_box = lv_obj_create(lv_scr_act(), NULL);
    // lv_obj_set_size(voc_box, 230, 57.5);
    // lv_obj_align(voc_box, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 5, 5);
    // static lv_style_t voc_box_style;
    // lv_style_init(&voc_box_style);
    // lv_style_set_bg_color(&voc_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_style_set_border_color(&voc_box_style, LV_STATE_DEFAULT, box_border_color);
    // lv_obj_add_style(voc_box, LV_OBJ_PART_MAIN, &voc_box_style);

    // lv_obj_t *voc_icon_box = lv_obj_create(voc_box, NULL);
    // lv_obj_set_size(voc_icon_box, 57.5, 57.5);
    // lv_obj_align(voc_icon_box, voc_box, LV_ALIGN_IN_LEFT_MID, 0, 0);
    // static lv_style_t voc_icon_box_style;
    // lv_style_init(&voc_icon_box_style);
    // lv_style_set_bg_color(&voc_icon_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_style_set_border_color(&voc_icon_box_style, LV_STATE_DEFAULT, box_border_color);
    // lv_obj_add_style(voc_icon_box, LV_OBJ_PART_MAIN, &voc_icon_box_style);

    // lv_obj_t *voc_icon = lv_img_create(voc_icon_box, NULL);
    // lv_img_set_src(voc_icon, &voc_img_src);
    // lv_obj_align(voc_icon, voc_icon_box, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    // // lv_obj_t *voc_icon = lv_img_create(voc_icon_box, NULL);
    // // lv_img_set_src(voc_icon, LV_SYMBOL_OK);
    // // lv_img_set_auto_size(voc_icon, true);
    // // lv_obj_set_size(voc_icon, 57, 57);
    // // lv_obj_align(voc_icon, voc_icon_box, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // lv_obj_t *voc_label_box = lv_obj_create(voc_box, NULL);
    // lv_obj_set_size(voc_label_box, 230 - 57.5, 57.5/3);
    // lv_obj_align(voc_label_box, voc_box, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
    // static lv_style_t voc_label_box_style;
    // lv_style_init(&voc_label_box_style);
    // lv_style_set_bg_color(&voc_label_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_style_set_border_color(&voc_label_box_style, LV_STATE_DEFAULT, box_border_color);
    // lv_obj_add_style(voc_label_box, LV_OBJ_PART_MAIN, &voc_icon_box_style);

    // lv_obj_t *voc_label = lv_label_create(voc_label_box, NULL);
    // lv_label_set_text(voc_label, "VOC");
    // lv_obj_align(voc_label, voc_label_box, LV_ALIGN_IN_LEFT_MID, 50, 4);
    // static lv_style_t voc_label_style;
    // lv_style_init(&voc_label_style);
    // lv_style_set_text_font(&voc_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_18);
    // lv_style_set_text_color(&voc_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    // lv_obj_add_style(voc_label, LV_OBJ_PART_MAIN, &voc_label_style);

    // lv_obj_t *voc_bar = lv_bar_create(voc_label_box, NULL);
    // lv_obj_set_size(voc_bar, 40, 6);
    // lv_obj_align(voc_bar, voc_label_box, LV_ALIGN_IN_LEFT_MID, 5, 0);
    // lv_bar_set_value(voc_bar, 100, LV_ANIM_OFF);
    // lv_style_init(&voc_bar_style);
    // lv_style_set_bg_color(&voc_bar_style, LV_STATE_DEFAULT, LV_COLOR_GREEN);
    // lv_obj_add_style(voc_bar, LV_BAR_PART_INDIC, &voc_bar_style);

    // lv_obj_t *voc_value_box = lv_obj_create(voc_box, NULL);
    // lv_obj_set_size(voc_value_box, 230 - 57.5,  38.33333333333333);
    // lv_obj_align(voc_value_box, voc_box, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);
    // static lv_style_t voc_value_box_style;
    // lv_style_init(&voc_value_box_style);
    // lv_style_set_bg_color(&voc_value_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_style_set_border_color(&voc_value_box_style, LV_STATE_DEFAULT, box_border_color);
    // lv_obj_add_style(voc_value_box, LV_OBJ_PART_MAIN, &voc_value_box_style);

    // lv_obj_t *voc_value = lv_label_create(voc_value_box, NULL);
    // lv_obj_align(voc_value, voc_value_box, LV_ALIGN_IN_TOP_LEFT, 5, 0);
    // lv_label_set_text(voc_value, "89");
    // lv_style_init(&voc_value_style);
    // lv_style_set_text_font(&voc_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_30);
    // lv_style_set_text_color(&voc_value_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    // lv_obj_add_style(voc_value, LV_OBJ_PART_MAIN, &voc_value_style);

    /* voc */
    /* new start */
    // lv_obj_t *voc_box = lv_obj_create(lv_scr_act(), NULL);
    // lv_obj_set_size(voc_box, 115, 75);
    // lv_obj_align(voc_box, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 5, 5);
    // lv_style_init(&voc_box_style);
    // lv_style_set_bg_color(&voc_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_style_set_border_color(&voc_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_obj_add_style(voc_box, LV_OBJ_PART_MAIN, &voc_box_style);

    // lv_obj_t *voc_label = lv_label_create(voc_box, NULL);
    // lv_label_set_text(voc_label, "VOC");
    // lv_obj_align(voc_label, voc_box, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
    // lv_style_init(&voc_label_style);
    // lv_style_set_text_font(&voc_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_16);
    // lv_style_set_text_color(&voc_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    // lv_obj_add_style(voc_label, LV_OBJ_PART_MAIN, &voc_label_style);

    // lv_obj_t *voc_bar = lv_bar_create(voc_box, NULL);
    // lv_obj_set_size(voc_bar, 110, 5);
    // lv_bar_set_type(voc_bar, LV_BAR_TYPE_SYMMETRICAL);
    // lv_obj_align(voc_bar, voc_box, LV_ALIGN_CENTER, 0, 0);
    // lv_style_init(&voc_bar_style);

    // lv_obj_t *voc_value = lv_label_create(voc_box, NULL);
    // lv_obj_align(voc_value, voc_box, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
    // lv_style_init(&voc_value_style);
    // lv_style_set_text_font(&voc_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    // lv_style_set_text_color(&voc_value_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    // lv_obj_add_style(voc_value, LV_OBJ_PART_MAIN, &voc_value_style);

    // /* co2 */
    // lv_obj_t *co2_box = lv_obj_create(lv_scr_act(), NULL);
    // lv_obj_set_size(co2_box, 115, 75);
    // lv_obj_align(co2_box, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 115+5, 5);
    // lv_style_init(&co2_box_style);
    // lv_style_set_bg_color(&co2_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_style_set_border_color(&co2_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_obj_add_style(co2_box, LV_OBJ_PART_MAIN, &co2_box_style);

    // lv_obj_t *co2_label = lv_label_create(co2_box, NULL);
    // lv_label_set_text(co2_label, "CO2");
    // lv_obj_align(co2_label, co2_box, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
    // lv_style_init(&co2_label_style);
    // lv_style_set_text_font(&co2_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
    // lv_style_set_text_color(&co2_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    // lv_obj_add_style(co2_label, LV_OBJ_PART_MAIN, &co2_label_style);

    // lv_obj_t *co2_bar = lv_bar_create(co2_box, NULL);
    // lv_obj_set_size(co2_bar, 110, 5);
    // lv_bar_set_type(co2_bar, LV_BAR_TYPE_SYMMETRICAL);
    // lv_obj_align(co2_bar, co2_box, LV_ALIGN_CENTER, 0, 0);
    // lv_style_init(&co2_bar_style);

    // lv_obj_t *co2_value = lv_label_create(co2_box, NULL);
    // lv_obj_align(co2_value, co2_box, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
    // lv_style_init(&co2_value_style);
    // lv_style_set_text_font(&co2_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_28);
    // lv_style_set_text_color(&co2_value_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    // lv_obj_add_style(co2_value, LV_OBJ_PART_MAIN, &co2_value_style);
    /* new end */
    
    // static lv_style_t pm2_5_label_style;
    // static lv_style_t pm10_label_style;
    // lv_style_init(&pm2_5_label_style);
    // lv_style_init(&pm10_label_style);
    
    
    
    // lv_style_init(&voc_label_style);
    
    // lv_style_init(&co2_box_style);
    // lv_style_init(&co2_label_style);
    // lv_style_init(&co2_value_style);
    // lv_style_init(&co2_led_style);
    // lv_style_init(&temp_value_style);
    // lv_style_init(&temp_box_style);
    // lv_style_init(&hum_value_style);
    // lv_style_init(&hum_box_style);

    // /* changing font size of label_style */
    // // lv_style_set_text_font(&pm2_5_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    // // lv_style_set_text_font(&pm10_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    // lv_style_set_text_font(&temp_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    // lv_style_set_text_font(&hum_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    
    
    // lv_style_set_text_font(&co2_label_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
    // lv_style_set_text_font(&co2_value_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);

    // lv_style_set_text_color(&temp_value_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    // lv_style_set_text_color(&hum_value_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    // lv_style_set_text_color(&voc_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    
    // lv_style_set_text_color(&co2_label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    // lv_style_set_text_color(&co2_value_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    // // lv_obj_t *pm2_5_label = lv_label_create(lv_scr_act(), NULL);
    // // lv_obj_t *pm10_label = lv_label_create(lv_scr_act(), NULL);

    // /* screen creation */
    // lv_obj_t *screen = lv_obj_create(NULL, NULL);
    // lv_scr_load(screen);
    // lv_style_set_bg_color(&screen_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    // /* voc related objects */
    // lv_obj_t *voc_box = lv_obj_create(lv_scr_act(), NULL);
    // lv_obj_set_size(voc_box, 240, 40);
    // lv_obj_align(voc_box, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);
    // lv_style_set_bg_color(&voc_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_style_set_border_color(&voc_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    // lv_obj_t *voc_label = lv_label_create(voc_box, NULL);
    // lv_label_set_text(voc_label, "VOC");
    // lv_obj_align(voc_label, voc_box, LV_ALIGN_IN_LEFT_MID, 8, 0);

    // lv_obj_t *voc_bar = lv_bar_create(voc_box, NULL);
    // lv_obj_set_size(voc_bar, 100, 12);
    // lv_bar_set_type(voc_bar, LV_BAR_TYPE_SYMMETRICAL);
    // lv_obj_align(voc_bar, voc_box, LV_ALIGN_IN_RIGHT_MID, -8, 0);

    // lv_obj_t *voc_value = lv_label_create(voc_box, NULL);
    // lv_obj_align(voc_value, voc_box, LV_ALIGN_CENTER, -16, 0);

    // /* co2 related objects */
    // lv_obj_t *co2_box = lv_obj_create(lv_scr_act(), NULL);
    // lv_obj_set_size(co2_box, 240, 40);
    // lv_obj_set_pos(co2_box, 0, 40);
    // lv_style_set_bg_color(&co2_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_style_set_border_color(&co2_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    // lv_obj_t *co2_label = lv_label_create(co2_box, NULL);
    // lv_label_set_text(co2_label, "CO2");
    // lv_obj_align(co2_label, co2_box, LV_ALIGN_IN_LEFT_MID, 8, 0);

    // lv_obj_t *co2_led = lv_led_create(co2_box, NULL);
    // lv_obj_set_size(co2_led, 25, 25);   
    // lv_obj_align(co2_led, co2_box, LV_ALIGN_IN_RIGHT_MID, -8, 0);
    // lv_led_set_bright(co2_led, LV_LED_BRIGHT_MAX);
    // lv_style_set_bg_color(&co2_led_style, LV_STATE_DEFAULT, LV_COLOR_GREEN);
    // lv_led_on(co2_led);
    // // lv_led_off(co2_led);
    

    // lv_obj_t *co2_value = lv_label_create(co2_box, NULL);
    // lv_obj_align(co2_value, co2_box, LV_ALIGN_IN_BOTTOM_MID, -15, -3);

    // /* temp related objects */
    // lv_obj_t *temp_box = lv_obj_create(lv_scr_act(), NULL);
    // lv_obj_set_size(temp_box, 120, 80);
    // lv_obj_set_pos(temp_box, 0, 160);
    // lv_style_set_bg_color(&temp_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_style_set_border_color(&temp_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    // lv_obj_t *temp_value = lv_label_create(temp_box, NULL);
    // lv_obj_align(temp_value, temp_box, LV_ALIGN_IN_LEFT_MID, 0, 0);

    // // lv_obj_t *temp_gauge = lv_gauge_create(temp_box, NULL);
    // // lv_color_t temp_gauge_needle_color[] = {LV_COLOR_WHITE};
    // // lv_gauge_set_needle_count(temp_gauge, 1, temp_gauge_needle_color);
    // // lv_obj_set_size(temp_gauge, 80, 80);
    // // lv_gauge_set_value(temp_gauge, 0, 24);

    // /* hum related objects */
    // lv_obj_t *hum_box = lv_obj_create(lv_scr_act(), NULL);
    // lv_obj_set_size(hum_box, 120, 80);
    // lv_obj_set_pos(hum_box, 120, 160);
    // lv_style_set_bg_color(&hum_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_style_set_border_color(&hum_box_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    // lv_obj_t *hum_value = lv_label_create(hum_box, NULL);
    // lv_obj_align(hum_value, hum_box, LV_ALIGN_IN_LEFT_MID, 0, 0);

    // /* linking a label to a style */
    // // lv_obj_add_style(pm2_5_label, LV_OBJ_PART_MAIN, &pm2_5_label_style);
    // // lv_obj_add_style(pm10_label, LV_OBJ_PART_MAIN, &pm10_label_style);
    

    
    // lv_obj_add_style(co2_box, LV_OBJ_PART_MAIN, &co2_box_style);
    // lv_obj_add_style(temp_box, LV_OBJ_PART_MAIN, &temp_box_style);
    // lv_obj_add_style(hum_box, LV_OBJ_PART_MAIN, &hum_box_style);

    // lv_obj_add_style(temp_value, LV_OBJ_PART_MAIN, &temp_value_style);
    // lv_obj_add_style(hum_value, LV_OBJ_PART_MAIN, &hum_value_style);
    
    
    // lv_obj_add_style(co2_label, LV_OBJ_PART_MAIN, &co2_label_style);
    // lv_obj_add_style(co2_value, LV_OBJ_PART_MAIN, &co2_value_style);

    