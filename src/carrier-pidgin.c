#define PURPLE_PLUGINS

#include <glib.h>

#ifndef G_GNUC_NULL_TERMINATED
#  if __GNUC__ >= 4
#    define G_GNUC_NULL_TERMINATED __attribute__((__sentinel__))
#  else
#    define G_GNUC_NULL_TERMINATED
#  endif /* __GNUC__ >= 4 */
#endif /* G_GNUC_NULL_TERMINATED */

#include "libpurple/plugin.h"
#include "libpurple/version.h"

#include "twilio.h"

static gboolean load(PurplePlugin *plugin);
static gboolean unload(PurplePlugin *plugin);

static PurplePluginInfo info = {
  PURPLE_PLUGIN_MAGIC,
  PURPLE_MAJOR_VERSION,
  PURPLE_MINOR_VERSION,
  PURPLE_PLUGIN_STANDARD, //PURPLE_PLUGIN_PROTOCOL,
  NULL,
  0,
  NULL,
  PURPLE_PRIORITY_DEFAULT,
  "prpl-gpetters-carrier_sms",
  "Carrier SMS",
  "0.0",
  "Twilio and VOIP.ms SMS Plugin",
  "Twilio and VOIP.ms SMS Plugin",
  "George Petterson <gpetters@protonmail.com",
  "", // TODO: Put website here
  load,
  unload,
  NULL,
  NULL,
  NULL, // TODO: Protocol info struct
  NULL, // TODO: Configuration UI
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};

static gboolean load(PurplePlugin *plugin) {
  return TRUE;
}

static gboolean unload(PurplePlugin *plugin) {
  return TRUE;
}

static void init_plugin(PurplePlugin *plugin) {
  // TODO: Set up plugin
}

PURPLE_INIT_PLUGIN(carrier_sms, init_plugin, info)
