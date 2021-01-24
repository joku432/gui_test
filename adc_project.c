#include "adc_project.h"
#include <lvgl/lvgl.h>



int8_t gui_init(gui_t* gui, uint16_t W, uint16_t H)
{
	gui->W = 472;
	gui->H = 270;
	// Initialize line meter 
	gui->line_meter = lv_linemeter_create(lv_scr_act(), NULL);
	lv_linemeter_set_range(gui->line_meter, 0, 4096);
	lv_linemeter_set_value(gui->line_meter, 3000);
	lv_linemeter_set_scale(gui->line_meter, 240, 25);
	lv_obj_set_size(gui->line_meter, 200, 200);
	lv_obj_align(gui->line_meter, NULL, LV_ALIGN_CENTER, 0, 0);

	gui->value_label = lv_label_create(gui->line_meter, NULL);
	lv_label_set_align(gui->value_label, LV_LABEL_ALIGN_CENTER);
	lv_label_set_text(gui->value_label, "0");
	lv_obj_align(gui->value_label, gui->line_meter, LV_ALIGN_CENTER, -5, 0);
	

	return GUI_SUCCESS;
}

int8_t gui_update_adc_value(gui_t* gui, uint32_t value)
{
	if (value > 4096 || value < 0) {
		return GUI_ERROR;
	}
	lv_label_set_text_fmt(gui->value_label, "%d", value);
	lv_linemeter_set_value(gui->line_meter, value);
	return GUI_SUCCESS;
}

int8_t gui_set_adc_value_treshold(gui_t* gui, uint32_t value)
{
	if (value > 4096 || value < 0) {
		return GUI_ERROR;
	}

	gui->adc_value_treshold = value;
	
	return GUI_SUCCESS;
}