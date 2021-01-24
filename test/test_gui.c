#include "unity.h"
#include "mock_lv_linemeter.h"
#include "mock_lv_obj.h"
#include "mock_lv_label.h"
#include "mock_lv_disp.h"
#include "mock_lv_hal_disp.h"
#include "gui.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static gui_t gui;

void test_gui_update_adc_value_ok_value(void)
{
    const uint32_t value = 1500;
	lv_label_set_text_fmt_Expect(NULL, "%d");
	lv_label_set_text_fmt_IgnoreArg_label();
	lv_linemeter_set_value_Expect(NULL, value);
	lv_linemeter_set_value_IgnoreArg_lmeter();
    int8_t retval = gui_update_adc_value(&gui, value);
	TEST_ASSERT_EQUAL_INT8(0, retval);
}

void gui_set_adc_value_treshold_ok_value(void)
{
	const uint32_t value = 1500;
    int8_t retval = gui_set_adc_value_treshold(&gui, value);
	TEST_ASSERT_EQUAL_INT8(0, retval);
}

void gui_get_adc_value_treshold_returns_correct_value(void)
{
	int8_t retval = gui_set_adc_value_treshold(&gui, 3456);
	TEST_ASSERT_EQUAL_INT8(0, retval);

	TEST_ASSERT_EQUAL_UINT32(3456, gui_get_adc_value_treshold(&gui));
}