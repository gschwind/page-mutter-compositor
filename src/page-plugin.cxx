/*
 * Copyright (2017) Benoit Gschwind
 *
 * page-plugin.cxx is part of page-compositor.
 *
 * page-compositor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * page-compositor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with page-compositor.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#include "page-plugin.hxx"
#include "page-page.hxx"

#include <clutter/clutter.h>

G_DEFINE_TYPE(PagePlugin, page_plugin, META_TYPE_PLUGIN);

namespace page_plugin {

using namespace page;

gboolean
on_rect_enter (ClutterActor *actor,
               ClutterEvent *event,
               gpointer      user_data) {
	log::printf("call %s\n", __PRETTY_FUNCTION__);
	static ClutterColor actor_color = { 255, 0, 0, 255 };
	clutter_actor_set_easing_mode (actor, CLUTTER_LINEAR);
	clutter_actor_set_easing_duration (actor, 10000);
	clutter_actor_set_background_color(actor, &actor_color);
	return TRUE;
}

gboolean
on_rect_leave (ClutterActor *actor,
               ClutterEvent *event,
               gpointer      user_data) {
	log::printf("call %s\n", __PRETTY_FUNCTION__);
	static ClutterColor actor_color = { 0, 255, 0, 255 };
	clutter_actor_set_easing_mode (actor, CLUTTER_LINEAR);
	clutter_actor_set_easing_duration (actor, 10000);
	clutter_actor_set_background_color(actor, &actor_color);
	return TRUE;
}

static gulong xxid;

gboolean
on_motion_event (ClutterActor *actor,
               ClutterEvent *event,
               gpointer      user_data) {
	log::printf("motion x=%f, y=%f\n", event->motion.x, event->motion.y);

	clutter_actor_set_easing_mode (actor, CLUTTER_LINEAR);
	clutter_actor_set_easing_duration (actor, 0);
	clutter_actor_set_position(actor, event->motion.x, event->motion.y);
	return TRUE;

}

gboolean
on_button_press_event(ClutterActor *actor,
               ClutterEvent *event,
               gpointer      user_data) {
	log::printf("call %s\n", __PRETTY_FUNCTION__);

	clutter_grab_pointer(actor);

	xxid = g_signal_connect(actor, "motion-event", G_CALLBACK(on_motion_event), NULL);

}

gboolean
on_button_release_event(ClutterActor *actor,
               ClutterEvent *event,
               gpointer      user_data) {
	log::printf("call %s\n", __PRETTY_FUNCTION__);
	g_signal_handler_disconnect(actor, xxid);
	clutter_ungrab_pointer();
}



static void start(MetaPlugin * plugin)
{
	PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_start();

//	printf("call %s\n", __PRETTY_FUNCTION__);
//	PagePlugin * self = PAGE_PLUGIN(plugin);
//	MetaScreen * screen = meta_plugin_get_screen(plugin);
//	auto stage = meta_get_stage_for_screen(screen);
//
//	ClutterColor actor_color = { 0, 255, 0, 255 };
//	auto rect = clutter_actor_new();
//	clutter_actor_set_background_color(rect, &actor_color);
//	clutter_actor_set_size(rect, 100, 100);
//	clutter_actor_set_position(rect, 100, 100);
//	clutter_actor_add_child(stage, rect);
//	clutter_actor_show(rect);
//	clutter_actor_set_rotation_angle(rect, CLUTTER_Z_AXIS, 60);
//	clutter_actor_set_reactive(rect, TRUE);
//
//	g_signal_connect(rect, "enter-event", G_CALLBACK(on_rect_enter), NULL);
//	g_signal_connect(rect, "leave-event", G_CALLBACK(on_rect_leave), NULL);
//	g_signal_connect(rect, "button-press-event", G_CALLBACK(on_button_press_event), NULL);
//	g_signal_connect(rect, "button-release-event", G_CALLBACK(on_button_release_event), NULL);
//
//	clutter_actor_show(stage);
}

static void minimize(MetaPlugin * plugin, MetaWindowActor * actor)
{
	PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_minimize(actor);
}

static void unminimize(MetaPlugin * plugin, MetaWindowActor * actor)
{
	PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_unminimize(actor);
}

static void size_change(MetaPlugin * plugin, MetaWindowActor * window_actor,
		MetaSizeChange which_change, MetaRectangle * old_frame_rect,
		MetaRectangle * old_buffer_rect)
{
	PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_size_change(window_actor, which_change, old_frame_rect, old_buffer_rect);
}

static void on_position_changed(MetaWindow * w, guint user_data) {
	log::printf("call %s\n", __PRETTY_FUNCTION__);
	meta_window_move_resize_frame(w, FALSE, 0, 0, 400, 400);
}

static void map(MetaPlugin * plugin, MetaWindowActor * window_actor)
{
	PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_map(window_actor);

//	printf("call %s\n", __PRETTY_FUNCTION__);
//	MetaWindowType type;
//	ClutterActor * actor = CLUTTER_ACTOR(window_actor);
//	MetaWindow *meta_window = meta_window_actor_get_meta_window(window_actor);
//
//	auto screen = meta_plugin_get_screen (plugin);
//	auto main_actor = meta_get_stage_for_screen(screen);
//
//	type = meta_window_get_window_type(meta_window);
//
//	if (type == META_WINDOW_NORMAL) {
//		printf("normal window\n");
//
//		g_signal_connect(meta_window, "position-changed", G_CALLBACK(on_position_changed), NULL);
//
//		//meta_window_maximize(meta_window, META_MAXIMIZE_BOTH);
//		meta_window_move_resize_frame(meta_window, FALSE, 0, 0, 400, 400);
//		meta_plugin_map_completed(plugin, window_actor);
//	} else
//		meta_plugin_map_completed(plugin, window_actor);
}


static void destroy(MetaPlugin * plugin, MetaWindowActor * actor)
{
	PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_destroy(actor);
//	printf("call %s\n", __PRETTY_FUNCTION__);
//	meta_plugin_destroy_completed(plugin, actor);
}

static void switch_workspace(MetaPlugin * plugin, gint from, gint to,
		MetaMotionDirection direction)
{
	PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_switch_workspace(from, to, direction);
}

static void show_tile_preview(MetaPlugin * plugin, MetaWindow * window,
		MetaRectangle *tile_rect, int tile_monitor_number)
{
	PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_show_tile_preview(window, tile_rect, tile_monitor_number);
}

static void hide_tile_preview(MetaPlugin * plugin)
{
	PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_hide_tile_preview();
}

static void show_window_menu(MetaPlugin * plugin, MetaWindow * window,
		MetaWindowMenuType menu, int x, int y)
{
	PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_show_window_menu(window, menu, x, y);
}

static void show_window_menu_for_rect(MetaPlugin * plugin, MetaWindow * window,
		MetaWindowMenuType menu, MetaRectangle * rect)
{
	PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_show_window_menu_for_rect(window, menu, rect);
}

static void kill_window_effects(MetaPlugin * plugin, MetaWindowActor * actor)
{
	PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_kill_window_effects(actor);
}

static void kill_switch_workspace(MetaPlugin * plugin)
{
	PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_kill_switch_workspace();
}

static gboolean xevent_filter(MetaPlugin * plugin, XEvent * event)
{
	return PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_xevent_filter(event);
}

static gboolean keybinding_filter(MetaPlugin * plugin, MetaKeyBinding * binding)
{
	return PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_keybinding_filter(binding);
}

static void confirm_display_change(MetaPlugin * plugin)
{
	PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_confirm_display_change();
}


static MetaPluginInfo const * plugin_info(MetaPlugin * plugin)
{
	return PAGE_PLUGIN(plugin)->priv->core->_handler_plugin_plugin_info();
}

}

static void
page_plugin_class_init (PagePluginClass *klass)
{
	GObjectClass * gobject_class = G_OBJECT_CLASS(klass);
	MetaPluginClass * meta_plugin_class = META_PLUGIN_CLASS(klass);

//	gobject_class->finalize = meta_default_plugin_finalize;
//	gobject_class->dispose = meta_default_plugin_dispose;
//	gobject_class->set_property = meta_default_plugin_set_property;
//	gobject_class->get_property = meta_default_plugin_get_property;

	meta_plugin_class->start = &page_plugin::start;
	meta_plugin_class->minimize = &page_plugin::minimize;
	meta_plugin_class->unminimize = &page_plugin::unminimize;
	meta_plugin_class->size_change = &page_plugin::size_change;
	meta_plugin_class->map = &page_plugin::map;
	meta_plugin_class->destroy = &page_plugin::destroy;
	meta_plugin_class->switch_workspace = &page_plugin::switch_workspace;
	meta_plugin_class->show_tile_preview = &page_plugin::show_tile_preview;
	meta_plugin_class->hide_tile_preview = &page_plugin::hide_tile_preview;
	meta_plugin_class->show_window_menu = &page_plugin::show_window_menu;
	meta_plugin_class->show_window_menu_for_rect = &page_plugin::show_window_menu_for_rect;
	meta_plugin_class->kill_window_effects = &page_plugin::kill_window_effects;
	meta_plugin_class->kill_switch_workspace = &page_plugin::kill_switch_workspace;
	meta_plugin_class->xevent_filter = &page_plugin::xevent_filter;
	meta_plugin_class->keybinding_filter = &page_plugin::keybinding_filter;
	meta_plugin_class->confirm_display_change = &page_plugin::confirm_display_change;
	meta_plugin_class->plugin_info = &page_plugin::plugin_info;

	g_type_class_add_private(gobject_class, sizeof(PagePluginPrivate));

}

static void
page_plugin_init (PagePlugin * self)
{
	  PagePluginPrivate * priv;

	  self->priv = priv = PAGE_PLUGIN_GET_PRIVATE(self);

	  priv->info.name        = "page-plugin";
	  priv->info.version     = "0.1";
	  priv->info.author      = "Benoit Gschwind <gschwind@gnu-log.net>";
	  priv->info.license     = "GPLv3";
	  priv->info.description = "Tiling window manager";

	  priv->core = new page::page_t(META_PLUGIN(self));

}
