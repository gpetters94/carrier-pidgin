#define PURPLE_PLUGINS

#include <glib.h>
#include <string.h>

#ifndef G_GNUC_NULL_TERMINATED
#  if __GNUC__ >= 4
#    define G_GNUC_NULL_TERMINATED __attribute__((__sentinel__))
#  else
#    define G_GNUC_NULL_TERMINATED
#  endif /* __GNUC__ >= 4 */
#endif /* G_GNUC_NULL_TERMINATED */

#include "libpurple/version.h"
#include "libpurple/prpl.h"
#include "libpurple/plugin.h"
#include "libpurple/account.h"
#include "libpurple/blist.h"
#include "libpurple/buddyicon.h"
#include "libpurple/debug.h"
#include "libpurple/accountopt.h"

#include "twilio.h"

static gboolean load(PurplePlugin *plugin);
static gboolean unload(PurplePlugin *plugin);
const gchar *list_icon(PurpleAccount *account, PurpleBuddy *buddy);
void login(PurpleAccount *account);
void close(PurpleConnection *pc);
int chat_send(PurpleConnection *pc, int id, const char *message, PurpleMessageFlags flags);

static PurplePluginProtocolInfo proto_info = {
	(PurpleProtocolOptions) (OPT_PROTO_CHAT_TOPIC),// options
	NULL,                     // user_splits
	NULL,                     // protocol_options
	{"png,jpeg",0,0,64,64,0,PURPLE_ICON_SCALE_DISPLAY},// icon_spec
	list_icon, //steamworks_list_icon,     // list_icon
	NULL, //steamworks_list_emblem,   // list_emblem
  NULL, //steamworks_status_text,   // status_text
	NULL, //steamworks_tooltip_text,  // tooltip_text
	NULL, //steamworks_status_types,  // status_types
	NULL,                     // blist_node_menu
	NULL, //steamworks_chat_info,     // chat_info
	NULL, //steamworks_chat_defaults, // chat_info_defaults
	login, //steamworks_login,         // login
	close, //steamworks_close,         // close
	NULL, //steamworks_send_im,       // send_im
	NULL,                     // set_info
	NULL, //steamworks_send_typing,   // send_typing
	NULL,                     // get_info
	NULL, //steamworks_set_status,    // set_status
	NULL,                     // set_idle
	NULL,                     // change_passwd
	NULL, //steamworks_add_buddy,     // add_buddy
	NULL,                     // add_buddies
	NULL, //steamworks_remove_buddy,  // remove_buddy
	NULL,                     // remove_buddies
	NULL,                     // add_permit
	NULL, //steamworks_ignore_buddy,  // add_deny
	NULL,                     // rem_permit
	NULL, //steamworks_unignore_buddy,// rem_deny
	NULL,                     // set_permit_deny
	NULL, //steamworks_join_chat,     // join_chat
	NULL, //steamworks_reject_chat,   // reject_chat
	NULL, //steamworks_get_chat_name, // get_chat_name
	NULL, //steamworks_chat_invite,   // chat_invite
	NULL, //steamworks_chat_leave,    // chat_leave
	NULL,                     // chat_whisper
	chat_send, // chat_send
	NULL,                     // keepalive
	NULL,                     // register_user
	NULL,                     // get_cb_info
	NULL,                     // get_cb_away
	NULL, //steamworks_alias_buddy,   // alias_buddy
	NULL,                     // group_buddy
	NULL,                     // rename_group
	NULL,                     // buddy_free
	NULL,                     // convo_closed
	NULL, //purple_normalize_nocase,  // normalize
	NULL,                     // set_buddy_icon
	NULL,                     // remove_group
	NULL,                     // get_cb_real_name
	NULL,                     // set_chat_topic
	NULL,                     // find_blist_chat
	NULL,                     // roomlist_get_list
	NULL,                     // roomlist_cancel
	NULL,                     // roomlist_expand_category
	NULL,                     // can_receive_file
	NULL,                     // send_file
	NULL,                     // new_xfer
	NULL,                     // offline_message
	NULL,                     // whiteboard_prpl_ops
	NULL,                     // send_raw
	NULL,                     // roomlist_room_serialize
	NULL,                     // unregister_user
	NULL,                     // send_attention
	NULL,                     // get_attention_types
	sizeof(PurplePluginProtocolInfo), // struct_size
	NULL,                     // account_text_table
	NULL,                     // initiate_media
	NULL,                     // media_caps
	NULL,                     // get_moods
	NULL,                     // set_public_alias
	NULL                      // get_public_alias
};

static PurplePluginInfo info = {
  PURPLE_PLUGIN_MAGIC,
  PURPLE_MAJOR_VERSION,
  PURPLE_MINOR_VERSION,
  PURPLE_PLUGIN_PROTOCOL,
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
  &proto_info, // TODO: Protocol info struct
  NULL, // TODO: Configuration UI
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};

static gboolean load(PurplePlugin *plugin) {
	purple_debug_info("carrier", "Loaded successfully\n");
  return TRUE;
}

static gboolean unload(PurplePlugin *plugin) {
  return TRUE;
}

static void init_plugin(PurplePlugin *plugin) {
  PurpleAccountOption *did_option = purple_account_option_string_new("DID", "did", "");
  proto_info.protocol_options = g_list_append(proto_info.protocol_options, did_option);
	purple_debug_info("carrier", "Added DID option\n");

	PurpleKeyValuePair *voip = malloc(sizeof(PurpleKeyValuePair));
	PurpleKeyValuePair *twilio = malloc(sizeof(PurpleKeyValuePair));
	voip->key = "VOIP.ms";
	voip->value = "voip";
	twilio->key = "Twilio";
	twilio->value = "twilio";

	GList *server_list = NULL;
	server_list = g_list_append(server_list, twilio);
	server_list = g_list_append(server_list, voip);
	PurpleAccountOption *server_option = purple_account_option_list_new("Server", "server", server_list);
  proto_info.protocol_options = g_list_append(proto_info.protocol_options, server_option);
	purple_debug_info("carrier", "Added server option\n");
}

const gchar *list_icon(PurpleAccount *account, PurpleBuddy *buddy) {
	return "carrier";
}

void login(PurpleAccount *account) {
	
}

void close(PurpleConnection *pc) {

}

int chat_send(PurpleConnection *pc, int id, const char *message, PurpleMessageFlags flags) {
	// TODO: properly send a message
	return 0;
}

PURPLE_INIT_PLUGIN(carrier_twilio, init_plugin, info)
