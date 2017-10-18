bin_PROGRAMS = page-mutter-compositor

AM_CXXFLAGS =  \
	-fpermissive \
	-Ipage \
	@CAIRO_CFLAGS@ \
	@MUTTER_CFLAGS@ \
	-DCLUTTER_ENABLE_COMPOSITOR_API					\
	-DCLUTTER_ENABLE_EXPERIMENTAL_API				\
	-DCOGL_ENABLE_EXPERIMENTAL_API					\
	-DCOGL_ENABLE_EXPERIMENTAL_2_0_API                              \
	-DCOGL_ENABLE_MUTTER_API					\
	-DCLUTTER_DISABLE_DEPRECATION_WARNINGS				\
	-DCOGL_DISABLE_DEPRECATION_WARNINGS				\
	$(MUTTER_CFLAGS)						\
	$(MUTTER_NATIVE_BACKEND_CFLAGS)					\
	-I$(builddir)							\
	-I$(srcdir)/mutter							\
	-I$(srcdir)/mutter/backends						\
	-I$(srcdir)/mutter/core						\
	-I$(srcdir)/mutter/ui							\
	-I$(srcdir)/mutter/compositor						\
	-I$(top_srcdir)/mutter/src						\
	-I$(top_srcdir)/mutter/cogl						\
	-I$(top_srcdir)/mutter/cogl/cogl					\
	-I$(top_srcdir)/mutter/cogl/cogl/winsys				\
	-I$(top_builddir)/mutter/cogl/cogl					\
	-I$(top_builddir)/mutter/cogl						\
	-I$(top_srcdir)/mutter/clutter						\
	-I$(top_srcdir)/mutter/clutter/clutter					\
	-I$(top_builddir)/mutter/clutter					\
	-I$(top_builddir)/mutter/clutter/clutter				\
	-DMUTTER_LIBEXECDIR=\"$(libexecdir)\"				\
	-DMUTTER_LOCALEDIR=\"$(localedir)\"				\
	-DMUTTER_PKGDATADIR=\"$(pkgdatadir)\"				\
	-DMUTTER_DATADIR=\"$(datadir)\"					\
	-DG_LOG_DOMAIN=\"pxmutter\"					\
	-DSN_API_NOT_YET_FROZEN=1					\
	-DMUTTER_PKGLIBDIR=\"$(pkglibdir)\"				\
	-DMUTTER_PLUGIN_DIR=\"$(MUTTER_PLUGIN_DIR)\"			\
	-DGETTEXT_PACKAGE=\"$(GETTEXT_PACKAGE)\"			\
	-DXWAYLAND_PATH=\"$(XWAYLAND_PATH)\"				\
	$(NULL)

page_mutter_compositor_SOURCES = \
	page-client-managed.hxx \
	page-client-managed.cxx \
	page-dropdown-menu.hxx \
	page-dropdown-menu.cxx \
	page-popup-notebook0.hxx \
	page-popup-notebook0.cxx \
	page-popup-split.hxx \
	page-popup-split.cxx \
	page-renderable-thumbnail.hxx \
	page-renderable-thumbnail.cxx \
	page-renderable-floating-outer-gradien.hxx \
	page-renderable-floating-outer-gradien.cxx \
	page-renderable-solid.hxx \
	page-renderable-solid.cxx \
	page-view.hxx \
	page-view.cxx \
	page-view-rebased.hxx \
	page-view-rebased.cxx \
	page-view-notebook.hxx \
	page-view-notebook.cxx \
	page-view-fullscreen.hxx \
	page-view-fullscreen.cxx \
	page-view-dock.hxx \
	page-view-dock.cxx \
	page-view-floating.hxx \
	page-view-floating.cxx \
	page-view-popup.hxx \
	page-view-popup.cxx \
	page-page-component.hxx \
	page-page-component.cxx \
	page-icon-handler.hxx \
	page-icon-handler.cxx \
	page-utils.cxx \
	page-tree.cxx \
	page-grab-handlers.cxx \
	page-notebook.cxx \
	page-split.cxx \
	page-viewport.cxx \
	page-workspace.cxx \
	page-simple2-theme.cxx \
	page-tiny-theme.cxx \
	page-config-handler.cxx \
	page-popup-alt-tab.cxx \
	page-blur-image-surface.cxx \
	page-tree.hxx \
	page-blur-image-surface.hxx \
	page-notebook.hxx \
	page-compositor.hxx \
	page-config-handler.hxx \
	page-workspace.hxx \
	page-split.hxx \
	page-viewport.hxx \
	page-grab-handlers.hxx \
	page-client-not-managed.hxx \
	page-client-base.hxx \
	page-mainloop.hxx \
	page-page.hxx \
	page-page.cxx \
	page-utils.hxx \
	page-plugin.hxx \
	page-plugin.cxx \
	main.cxx 

page_mutter_compositor_LDADD = \
	$(top_builddir)/mutter/src/libpxmutter-@LIBMUTTER_API_VERSION@.la
	@CAIRO_LIBS@ \
	@MUTTER_LIBS@
page_mutter_compositor_LDFLAGS = \
	-rpath @MUTTER_TYPELIB_DIR@ 

