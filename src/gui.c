#include "gui.h"
#include "lvgl.h"

static void switch_to_screen(gui_t* gui, screen_id_t id)
{
	switch (id)
	{
	case HOME:
		lv_disp_load_scr(gui->screens[0].scr);
		break;
	case CHART:
		lv_disp_load_scr(gui->screens[1].scr);
		break;
	default:
		break;
	}
}


int8_t gui_init(gui_t* gui, uint16_t W, uint16_t H)
{
	gui->W = 472;
	gui->H = 270;

	gui->screens[0].id = HOME;
	gui->screens[0].scr = lv_scr_act();

	/* Initialize line meter */
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
	
	/* Chart */
	/* Create a new screen */
	gui->screens[1].id = CHART;
	gui->screens[1].scr = lv_obj_create(NULL, NULL);
	gui->chart = lv_chart_create(gui->screens[1].scr, NULL);
	lv_obj_set_size(gui->chart, 200, 150);
	lv_obj_align(gui->chart, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_chart_set_type(gui->chart, LV_CHART_TYPE_LINE);

	/* Add a faded area effect*/
	lv_obj_set_style_local_bg_opa(gui->chart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, LV_OPA_50);
	lv_obj_set_style_local_bg_grad_dir(gui->chart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_obj_set_style_local_bg_main_stop(gui->chart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 255);    
	lv_obj_set_style_local_bg_grad_stop(gui->chart, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 0);  

	lv_chart_series_t* ser1 = lv_chart_add_series(gui->chart, LV_COLOR_GREEN);

	/*Set the next points on 'ser1'*/
	lv_chart_set_next(gui->chart, ser1, 31);
	lv_chart_set_next(gui->chart, ser1, 66);
	lv_chart_set_next(gui->chart, ser1, 10);
	lv_chart_set_next(gui->chart, ser1, 89);
	lv_chart_set_next(gui->chart, ser1, 63);
	lv_chart_set_next(gui->chart, ser1, 56);
	lv_chart_set_next(gui->chart, ser1, 32);
	lv_chart_set_next(gui->chart, ser1, 35);
	lv_chart_set_next(gui->chart, ser1, 57);
	lv_chart_set_next(gui->chart, ser1, 85);
	
	gui_set_event_callbacks();

	switch_to_screen(gui, HOME);
	return GUI_SUCCESS;
}

void gui_set_event_callbacks(void)
{
	// TODO
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

int32_t gui_get_adc_value_treshold(gui_t* gui)
{
	return gui->adc_value_treshold;
}