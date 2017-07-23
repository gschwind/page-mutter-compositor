bin_PROGRAMS = page-mutter-compositor

AM_CXXFLAGS =  \
	-rdynamic \
	-fpermissive \
	-DCLUTTER_ENABLE_EXPERIMENTAL_API	\
	-DCOGL_ENABLE_EXPERIMENTAL_API		\
	@MUTTER_CFLAGS@ \
	@GLIB_CFLAGS@ \
	-rdynamic

page_mutter_compositor_SOURCES = \
	page-plugin.hxx \
	page-plugin.cxx \
	main.cxx 

page_mutter_compositor_LDADD = \
	@MUTTER_LIBS@ \
	@GLIB_CFLAGS@ 

