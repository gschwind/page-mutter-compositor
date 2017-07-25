/*
 * Copyright (2017) Benoit Gschwind
 *
 * page-plugin.hxx is part of page-compositor.
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

#ifndef SRC_PAGE_PLUGIN_HXX_
#define SRC_PAGE_PLUGIN_HXX_

extern "C" {
#include <meta/meta-plugin.h>
}

#include "page-page-types.hxx"

G_BEGIN_DECLS

/*
 * NOTES: "page" is a prefix and "plugin" is the name of plugin.
 */

#define PAGE_TYPE_PLUGIN            (page_plugin_get_type ())
#define PAGE_PLUGIN(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), PAGE_TYPE_PLUGIN, PagePlugin))
#define PAGE_PLUGIN_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass),  PAGE_TYPE_PLUGIN, PagePluginClass))
#define PAGE_IS_PLUGIN(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), PAGE_PLUGIN_TYPE))
#define PAGE_IS_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),  PAGE_TYPE_PLUGIN))
#define PAGE_PLUGIN_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj),  PAGE_TYPE_PLUGIN, PagePluginClass))

#define PAGE_PLUGIN_GET_PRIVATE(obj) \
(G_TYPE_INSTANCE_GET_PRIVATE ((obj), PAGE_TYPE_PLUGIN, PagePluginPrivate))

typedef struct _PagePlugin         PagePlugin;
typedef struct _PagePluginClass    PagePluginClass;
typedef struct _PagePluginPrivate  PagePluginPrivate;

struct _PagePlugin
{
	MetaPlugin parent;
	PagePluginPrivate *priv;
};

struct _PagePluginClass
{
	MetaPluginClass parent_class;
};

struct _PagePluginPrivate
{
  MetaPluginInfo         info;
  page::page_t * core;

};

GType page_plugin_get_type(void);

G_END_DECLS

#endif /* SRC_PAGE_PLUGIN_HXX_ */
