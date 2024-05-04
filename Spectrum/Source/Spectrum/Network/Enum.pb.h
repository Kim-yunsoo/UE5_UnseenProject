// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Enum.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Enum_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Enum_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Enum_2eproto;
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

enum CreatureType : int {
  CREATURE_TYPE_NONE = 0,
  CREATURE_TYPE_PLAYER = 1,
  CREATURE_TYPE_THING = 2,
  CreatureType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  CreatureType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool CreatureType_IsValid(int value);
constexpr CreatureType CreatureType_MIN = CREATURE_TYPE_NONE;
constexpr CreatureType CreatureType_MAX = CREATURE_TYPE_THING;
constexpr int CreatureType_ARRAYSIZE = CreatureType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* CreatureType_descriptor();
template<typename T>
inline const std::string& CreatureType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, CreatureType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function CreatureType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    CreatureType_descriptor(), enum_t_value);
}
inline bool CreatureType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, CreatureType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<CreatureType>(
    CreatureType_descriptor(), name, value);
}
enum PlayerType : int {
  PLAYER_TYPE_GREEN_MAN = 0,
  PLAYER_TYPE_GREEN_WOMAN = 1,
  PLAYER_TYPE_PURPLE_MAN = 2,
  PLAYER_TYPE_PURPLE_WOMAN = 3,
  PLAYER_TYPE_ORANGE_MAN = 4,
  PLAYER_TYPE_ORANGE_WOMAN = 5,
  PLAYER_TYPE_NONE = 6,
  PlayerType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  PlayerType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool PlayerType_IsValid(int value);
constexpr PlayerType PlayerType_MIN = PLAYER_TYPE_GREEN_MAN;
constexpr PlayerType PlayerType_MAX = PLAYER_TYPE_NONE;
constexpr int PlayerType_ARRAYSIZE = PlayerType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* PlayerType_descriptor();
template<typename T>
inline const std::string& PlayerType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, PlayerType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function PlayerType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    PlayerType_descriptor(), enum_t_value);
}
inline bool PlayerType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, PlayerType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<PlayerType>(
    PlayerType_descriptor(), name, value);
}
enum SchoolType : int {
  SCHOOL_TYPE_GREEN = 0,
  SCHOOL_TYPE_PURPLE = 1,
  SCHOOL_TYPE_ORANGE = 2,
  SchoolType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  SchoolType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool SchoolType_IsValid(int value);
constexpr SchoolType SchoolType_MIN = SCHOOL_TYPE_GREEN;
constexpr SchoolType SchoolType_MAX = SCHOOL_TYPE_ORANGE;
constexpr int SchoolType_ARRAYSIZE = SchoolType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* SchoolType_descriptor();
template<typename T>
inline const std::string& SchoolType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, SchoolType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function SchoolType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    SchoolType_descriptor(), enum_t_value);
}
inline bool SchoolType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, SchoolType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<SchoolType>(
    SchoolType_descriptor(), name, value);
}
enum MoveState : int {
  MOVE_STATE_NONE = 0,
  MOVE_STATE_IDLE = 1,
  MOVE_STATE_RUN = 2,
  MOVE_STATE_JUMP = 3,
  MoveState_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  MoveState_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool MoveState_IsValid(int value);
constexpr MoveState MoveState_MIN = MOVE_STATE_NONE;
constexpr MoveState MoveState_MAX = MOVE_STATE_JUMP;
constexpr int MoveState_ARRAYSIZE = MoveState_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MoveState_descriptor();
template<typename T>
inline const std::string& MoveState_Name(T enum_t_value) {
  static_assert(::std::is_same<T, MoveState>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function MoveState_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    MoveState_descriptor(), enum_t_value);
}
inline bool MoveState_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, MoveState* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<MoveState>(
    MoveState_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::Protocol::CreatureType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::CreatureType>() {
  return ::Protocol::CreatureType_descriptor();
}
template <> struct is_proto_enum< ::Protocol::PlayerType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::PlayerType>() {
  return ::Protocol::PlayerType_descriptor();
}
template <> struct is_proto_enum< ::Protocol::SchoolType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::SchoolType>() {
  return ::Protocol::SchoolType_descriptor();
}
template <> struct is_proto_enum< ::Protocol::MoveState> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::MoveState>() {
  return ::Protocol::MoveState_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto
