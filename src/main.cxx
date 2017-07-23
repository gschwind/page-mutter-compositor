
extern "C" {
#include <meta/main.h>
#include <meta/util.h>
}

#include "page-plugin.hxx"

static gboolean
print_version (const gchar    *option_name,
               const gchar    *value,
               gpointer        data,
               GError        **error)
{
	// TODO
	return true;
}

GOptionEntry mutter_options[] = {
  { NULL }
};

int main(int argc, char ** argv)
{
	GOptionContext *ctx;
	GError *error = NULL;

	ctx = meta_get_option_context();
	g_option_context_add_main_entries(ctx, mutter_options, NULL);
	if (!g_option_context_parse(ctx, &argc, &argv, &error)) {
		g_printerr("mutter: %s\n", error->message);
		return 1;
	}
	g_option_context_free(ctx);

	meta_plugin_manager_set_plugin_type(page_plugin_get_type());
	meta_set_wm_name("page-mutter-compositor");
	meta_init();
	meta_register_with_session();
	return meta_run();
}

