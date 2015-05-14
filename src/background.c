#include "background.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_30_black;
static GBitmap *s_res_image_01d;
static GBitmap *s_res_image_02d;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_2;
static BitmapLayer *s_bitmaplayer_1;
static BitmapLayer *s_bitmaplayer_2;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, true);
  
  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  s_res_image_01d = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_01d);
  s_res_image_02d = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_02d);
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(44, 133, 100, 35));
  text_layer_set_text(s_textlayer_1, "22:00");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(22, 117, 120, 15));
  text_layer_set_text(s_textlayer_2, "23 Mar, 22°, 14kn, NW");
  text_layer_set_text_alignment(s_textlayer_2, GTextAlignmentRight);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
  
  // s_bitmaplayer_1
  s_bitmaplayer_1 = bitmap_layer_create(GRect(0, 128, 40, 40));
  bitmap_layer_set_bitmap(s_bitmaplayer_1, s_res_image_01d);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_1);
  
  // s_bitmaplayer_2
  s_bitmaplayer_2 = bitmap_layer_create(GRect(5, 70, 40, 40));
  bitmap_layer_set_bitmap(s_bitmaplayer_2, s_res_image_02d);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_2);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_textlayer_2);
  bitmap_layer_destroy(s_bitmaplayer_1);
  bitmap_layer_destroy(s_bitmaplayer_2);
  gbitmap_destroy(s_res_image_01d);
  gbitmap_destroy(s_res_image_02d);
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

