#pragma once

#include <cstdint>
namespace GW2::Chat {
constexpr int Signature = 0x67770263;

constexpr auto MessageIdentifier = "EV_CHAT:Message";
enum class MessageType : uint8_t {
  Error = 0,
  Map = 1,
  Party = 2,
  Squad = 3,
  Team = 4,
  Guild = 5,
  Whisper = 6,
  Local = 7
};

struct Player {
  const char *Character = nullptr;
  const char *Account = nullptr;
};
struct GuildSource {
  Player Source;
  uint8_t Index;
  enum class GuildFlags : uint8_t {
    None = 0,
    IsActive = 1 << 0
  } Flags = GuildFlags::None;
};
struct WhisperSource {
  Player Interlocutor;
  enum class WhisperFlags : uint8_t {
    None = 0,
    SourceIsInterlocutor = 1 << 0
  } Flags = WhisperFlags::None;
};
struct TeamSource {
  Player Source;
  uint32_t MapId;
};
struct SquadSource {
  Player Source;
  enum class SquadFlags : uint8_t {
    None = 0,
    IsBroadcast = 1 << 0,
    SourceIsCommander = 1 << 1,
    SourceIsLeutanant = 1 << 2
  } Flags = SquadFlags::None;
};
struct WinFiletime { // windows FILETIME
  uint32_t LowDateTime, HighDateTime;
};
struct Message {
  const char *Content = nullptr;
  const WinFiletime Timestamp =
      WinFiletime{.LowDateTime = 0, .HighDateTime = 0};
  MessageType Type = MessageType::Error;
  union {
    Player PlayerSource;
    GuildSource Guild;
    TeamSource Team;
    WhisperSource Whisper;
    SquadSource Squad;
  };
};
} // namespace GW2::Chat
