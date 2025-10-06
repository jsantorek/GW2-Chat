#ifndef GW2_CHAT
#define GW2_CHAT
#ifdef __cplusplus
extern "C" {
#endif
#define GW2_CHAT_SIGNATURE 0x67770263
#define GW2_CHAT_EVENT "EV_CHAT:Message"
#include <stdint.h>

typedef enum {
  Error = 0,
  Guild,
  GuildMotD,
  Local,
  Map,
  Party,
  Squad,
  SquadMessage,
  SquadBroadcast,
  TeamPvP,
  TeamWvW,
  Whisper,
  Emote,
  EmoteCustom
} MessageType;
typedef enum {
  None = 0,

  Guild_IsRepresented = 1 << 0,

  Local_IsFromCommander = 1 << 1,
  Local_IsFromMentor = 1 << 2,

  Map_IsFromCommander = Local_IsFromCommander,
  Map_IsFromMentor = Local_IsFromMentor,

  Squad_IsFromCommander = Local_IsFromCommander,

  SquadMessage_IsBroadcast = 1 << 3,

  Whisper_IsFromMe = 1 << 4,
} MetadataFlags;
typedef enum {
  Beckon = 0x81011505,
  Dance = 0x81074004,
  Sit = 0x810E0C2B,
} EmoteType;
typedef char *StringUTF8; // null-terminated, UTF-8 encoded string
typedef struct {
  uint32_t Data1;
  uint16_t Data2;
  uint16_t Data3;
  uint8_t Data4[8];
} GloballyUniqueIdentifier; // windows GUID
typedef struct {
  uint32_t Low;
  uint32_t High;
} Timestamp; // windows FILETIME

typedef struct {
  GloballyUniqueIdentifier Account;
  StringUTF8 CharacterName;
  StringUTF8 AccountName; // nullptr if unavailable
  StringUTF8 Content;
} GenericMessage;
typedef struct {
  GenericMessage Base; // c-style inheritance
  uint32_t MapId;
} WvWTeamMessage;
typedef struct {
  StringUTF8 CharacterName;
  StringUTF8 ActionTaken;
} CustomEmoteMessage;
typedef struct {
  StringUTF8 CharacterName;
  EmoteType ActionTaken;
} EmoteMessage;
typedef struct {
  GenericMessage Base; // c-style inheritance
  uint32_t GuildIndex;
} GuildMessage;
typedef struct {
  StringUTF8 Content;
  uint32_t GuildIndex;
} GuildMessageOfTheDay;

typedef struct {
  Timestamp DateTime;
  MessageType Type;
  MetadataFlags Flags; // according to Type
  union {              // according to Type
    GuildMessage Guild;
    GuildMessageOfTheDay GuildMotD;
    GenericMessage Local;
    GenericMessage Map;
    GenericMessage Party;
    GenericMessage Squad;
    StringUTF8 SquadMessage;
    GenericMessage TeamPvP;
    WvWTeamMessage TeamWvW;
    GenericMessage Whisper;
    EmoteMessage Emote;
    CustomEmoteMessage EmoteCustom;
  };
} Message;

#ifdef __cplusplus
}
#endif
#endif
