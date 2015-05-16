#include <pebble.h>
#include "background.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_30_black;
static GBitmap *s_res_image_01d;
static TextLayer *s_textlayer_time;
static TextLayer *s_textlayer_date;
static BitmapLayer *s_condition_day1;
static BitmapLayer *s_condition_day2;
static BitmapLayer *s_condition_day3;
static BitmapLayer *s_bitmaplayer_4;
static BitmapLayer *s_bitmaplayer_1;
static TextLayer *s_textlayer_day3;
static TextLayer *s_textlayer_day2;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, true);
  
  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  s_res_image_01d = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_01d);
  // s_textlayer_time
  s_textlayer_time = text_layer_create(GRect(44, 133, 100, 35));
  text_layer_set_text(s_textlayer_time, "22:00");
  text_layer_set_text_alignment(s_textlayer_time, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_time, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_time);
  
  // s_textlayer_date
  s_textlayer_date = text_layer_create(GRect(22, 113, 120, 15));
  text_layer_set_text(s_textlayer_date, "23 Mar, 22°, 14kn, NW");
  text_layer_set_text_alignment(s_textlayer_date, GTextAlignmentRight);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_date);
  
  // s_condition_day1
  s_condition_day1 = bitmap_layer_create(GRect(0, 128, 40, 40));
  bitmap_layer_set_bitmap(s_condition_day1, s_res_image_01d);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_condition_day1);
  
  // s_condition_day2
  s_condition_day2 = bitmap_layer_create(GRect(0, 65, 40, 40));
  bitmap_layer_set_bitmap(s_condition_day2, s_res_image_01d);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_condition_day2);
  
  // s_condition_day3
  s_condition_day3 = bitmap_layer_create(GRect(0, 10, 40, 40));
  bitmap_layer_set_bitmap(s_condition_day3, s_res_image_01d);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_condition_day3);
  
  // s_bitmaplayer_4
  s_bitmaplayer_4 = bitmap_layer_create(GRect(0, 60, 144, 2));
  bitmap_layer_set_background_color(s_bitmaplayer_4, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_4);
  
  // s_bitmaplayer_1
  s_bitmaplayer_1 = bitmap_layer_create(GRect(0, 110, 144, 2));
  bitmap_layer_set_background_color(s_bitmaplayer_1, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_1);
  
  // s_textlayer_day3
  s_textlayer_day3 = text_layer_create(GRect(62, 23, 80, 15));
  text_layer_set_text(s_textlayer_day3, "22°, 14kn, NW");
  text_layer_set_text_alignment(s_textlayer_day3, GTextAlignmentRight);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_day3);
  
  // s_textlayer_day2
  s_textlayer_day2 = text_layer_create(GRect(62, 77, 80, 15));
  text_layer_set_text(s_textlayer_day2, "22°, 14kn, NW");
  text_layer_set_text_alignment(s_textlayer_day2, GTextAlignmentRight);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_day2);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_time);
  text_layer_destroy(s_textlayer_date);
  bitmap_layer_destroy(s_condition_day1);
  bitmap_layer_destroy(s_condition_day2);
  bitmap_layer_destroy(s_condition_day3);
  bitmap_layer_destroy(s_bitmaplayer_4);
  bitmap_layer_destroy(s_bitmaplayer_1);
  text_layer_destroy(s_textlayer_day3);
  text_layer_destroy(s_textlayer_day2);
  gbitmap_destroy(s_res_image_01d);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_background(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_background(void) {
  window_stack_remove(s_window, true);
}

// more background functions

void update_time_layer(char *buf) {
  text_layer_set_text(s_textlayer_time, buf);
}