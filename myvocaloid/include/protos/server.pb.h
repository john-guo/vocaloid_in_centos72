// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/server.proto

#ifndef PROTOBUF_INCLUDED_protos_2fserver_2eproto
#define PROTOBUF_INCLUDED_protos_2fserver_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_protos_2fserver_2eproto 

namespace protobuf_protos_2fserver_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[5];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_protos_2fserver_2eproto
namespace MyVocaloid {
class Note;
class NoteDefaultTypeInternal;
extern NoteDefaultTypeInternal _Note_default_instance_;
class ReplyChunk;
class ReplyChunkDefaultTypeInternal;
extern ReplyChunkDefaultTypeInternal _ReplyChunk_default_instance_;
class ReplyHeader;
class ReplyHeaderDefaultTypeInternal;
extern ReplyHeaderDefaultTypeInternal _ReplyHeader_default_instance_;
class SingReply;
class SingReplyDefaultTypeInternal;
extern SingReplyDefaultTypeInternal _SingReply_default_instance_;
class SingRequest;
class SingRequestDefaultTypeInternal;
extern SingRequestDefaultTypeInternal _SingRequest_default_instance_;
}  // namespace MyVocaloid
namespace google {
namespace protobuf {
template<> ::MyVocaloid::Note* Arena::CreateMaybeMessage<::MyVocaloid::Note>(Arena*);
template<> ::MyVocaloid::ReplyChunk* Arena::CreateMaybeMessage<::MyVocaloid::ReplyChunk>(Arena*);
template<> ::MyVocaloid::ReplyHeader* Arena::CreateMaybeMessage<::MyVocaloid::ReplyHeader>(Arena*);
template<> ::MyVocaloid::SingReply* Arena::CreateMaybeMessage<::MyVocaloid::SingReply>(Arena*);
template<> ::MyVocaloid::SingRequest* Arena::CreateMaybeMessage<::MyVocaloid::SingRequest>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace MyVocaloid {

// ===================================================================

class Note : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MyVocaloid.Note) */ {
 public:
  Note();
  virtual ~Note();

  Note(const Note& from);

  inline Note& operator=(const Note& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Note(Note&& from) noexcept
    : Note() {
    *this = ::std::move(from);
  }

  inline Note& operator=(Note&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Note& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Note* internal_default_instance() {
    return reinterpret_cast<const Note*>(
               &_Note_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Note* other);
  friend void swap(Note& a, Note& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Note* New() const final {
    return CreateMaybeMessage<Note>(NULL);
  }

  Note* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Note>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Note& from);
  void MergeFrom(const Note& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Note* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 note = 1;
  void clear_note();
  static const int kNoteFieldNumber = 1;
  ::google::protobuf::int32 note() const;
  void set_note(::google::protobuf::int32 value);

  // int32 start = 2;
  void clear_start();
  static const int kStartFieldNumber = 2;
  ::google::protobuf::int32 start() const;
  void set_start(::google::protobuf::int32 value);

  // int32 duration = 3;
  void clear_duration();
  static const int kDurationFieldNumber = 3;
  ::google::protobuf::int32 duration() const;
  void set_duration(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:MyVocaloid.Note)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 note_;
  ::google::protobuf::int32 start_;
  ::google::protobuf::int32 duration_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_protos_2fserver_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class SingRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MyVocaloid.SingRequest) */ {
 public:
  SingRequest();
  virtual ~SingRequest();

  SingRequest(const SingRequest& from);

  inline SingRequest& operator=(const SingRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  SingRequest(SingRequest&& from) noexcept
    : SingRequest() {
    *this = ::std::move(from);
  }

  inline SingRequest& operator=(SingRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const SingRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SingRequest* internal_default_instance() {
    return reinterpret_cast<const SingRequest*>(
               &_SingRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(SingRequest* other);
  friend void swap(SingRequest& a, SingRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline SingRequest* New() const final {
    return CreateMaybeMessage<SingRequest>(NULL);
  }

  SingRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<SingRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const SingRequest& from);
  void MergeFrom(const SingRequest& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SingRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .MyVocaloid.Note notes = 3;
  int notes_size() const;
  void clear_notes();
  static const int kNotesFieldNumber = 3;
  ::MyVocaloid::Note* mutable_notes(int index);
  ::google::protobuf::RepeatedPtrField< ::MyVocaloid::Note >*
      mutable_notes();
  const ::MyVocaloid::Note& notes(int index) const;
  ::MyVocaloid::Note* add_notes();
  const ::google::protobuf::RepeatedPtrField< ::MyVocaloid::Note >&
      notes() const;

  // string lyrics = 2;
  void clear_lyrics();
  static const int kLyricsFieldNumber = 2;
  const ::std::string& lyrics() const;
  void set_lyrics(const ::std::string& value);
  #if LANG_CXX11
  void set_lyrics(::std::string&& value);
  #endif
  void set_lyrics(const char* value);
  void set_lyrics(const char* value, size_t size);
  ::std::string* mutable_lyrics();
  ::std::string* release_lyrics();
  void set_allocated_lyrics(::std::string* lyrics);

  // int32 bpm = 1;
  void clear_bpm();
  static const int kBpmFieldNumber = 1;
  ::google::protobuf::int32 bpm() const;
  void set_bpm(::google::protobuf::int32 value);

  // int32 bank = 4;
  void clear_bank();
  static const int kBankFieldNumber = 4;
  ::google::protobuf::int32 bank() const;
  void set_bank(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:MyVocaloid.SingRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::MyVocaloid::Note > notes_;
  ::google::protobuf::internal::ArenaStringPtr lyrics_;
  ::google::protobuf::int32 bpm_;
  ::google::protobuf::int32 bank_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_protos_2fserver_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class ReplyHeader : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MyVocaloid.ReplyHeader) */ {
 public:
  ReplyHeader();
  virtual ~ReplyHeader();

  ReplyHeader(const ReplyHeader& from);

  inline ReplyHeader& operator=(const ReplyHeader& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ReplyHeader(ReplyHeader&& from) noexcept
    : ReplyHeader() {
    *this = ::std::move(from);
  }

  inline ReplyHeader& operator=(ReplyHeader&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const ReplyHeader& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ReplyHeader* internal_default_instance() {
    return reinterpret_cast<const ReplyHeader*>(
               &_ReplyHeader_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(ReplyHeader* other);
  friend void swap(ReplyHeader& a, ReplyHeader& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ReplyHeader* New() const final {
    return CreateMaybeMessage<ReplyHeader>(NULL);
  }

  ReplyHeader* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<ReplyHeader>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const ReplyHeader& from);
  void MergeFrom(const ReplyHeader& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ReplyHeader* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string message = 2;
  void clear_message();
  static const int kMessageFieldNumber = 2;
  const ::std::string& message() const;
  void set_message(const ::std::string& value);
  #if LANG_CXX11
  void set_message(::std::string&& value);
  #endif
  void set_message(const char* value);
  void set_message(const char* value, size_t size);
  ::std::string* mutable_message();
  ::std::string* release_message();
  void set_allocated_message(::std::string* message);

  // int32 result = 1;
  void clear_result();
  static const int kResultFieldNumber = 1;
  ::google::protobuf::int32 result() const;
  void set_result(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:MyVocaloid.ReplyHeader)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr message_;
  ::google::protobuf::int32 result_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_protos_2fserver_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class ReplyChunk : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MyVocaloid.ReplyChunk) */ {
 public:
  ReplyChunk();
  virtual ~ReplyChunk();

  ReplyChunk(const ReplyChunk& from);

  inline ReplyChunk& operator=(const ReplyChunk& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ReplyChunk(ReplyChunk&& from) noexcept
    : ReplyChunk() {
    *this = ::std::move(from);
  }

  inline ReplyChunk& operator=(ReplyChunk&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const ReplyChunk& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ReplyChunk* internal_default_instance() {
    return reinterpret_cast<const ReplyChunk*>(
               &_ReplyChunk_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(ReplyChunk* other);
  friend void swap(ReplyChunk& a, ReplyChunk& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ReplyChunk* New() const final {
    return CreateMaybeMessage<ReplyChunk>(NULL);
  }

  ReplyChunk* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<ReplyChunk>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const ReplyChunk& from);
  void MergeFrom(const ReplyChunk& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ReplyChunk* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bytes data = 1;
  void clear_data();
  static const int kDataFieldNumber = 1;
  const ::std::string& data() const;
  void set_data(const ::std::string& value);
  #if LANG_CXX11
  void set_data(::std::string&& value);
  #endif
  void set_data(const char* value);
  void set_data(const void* value, size_t size);
  ::std::string* mutable_data();
  ::std::string* release_data();
  void set_allocated_data(::std::string* data);

  // @@protoc_insertion_point(class_scope:MyVocaloid.ReplyChunk)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr data_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_protos_2fserver_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class SingReply : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MyVocaloid.SingReply) */ {
 public:
  SingReply();
  virtual ~SingReply();

  SingReply(const SingReply& from);

  inline SingReply& operator=(const SingReply& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  SingReply(SingReply&& from) noexcept
    : SingReply() {
    *this = ::std::move(from);
  }

  inline SingReply& operator=(SingReply&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const SingReply& default_instance();

  enum ReplyDataCase {
    kHeader = 1,
    kChunk = 2,
    REPLYDATA_NOT_SET = 0,
  };

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SingReply* internal_default_instance() {
    return reinterpret_cast<const SingReply*>(
               &_SingReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    4;

  void Swap(SingReply* other);
  friend void swap(SingReply& a, SingReply& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline SingReply* New() const final {
    return CreateMaybeMessage<SingReply>(NULL);
  }

  SingReply* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<SingReply>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const SingReply& from);
  void MergeFrom(const SingReply& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SingReply* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // .MyVocaloid.ReplyHeader header = 1;
  bool has_header() const;
  void clear_header();
  static const int kHeaderFieldNumber = 1;
  private:
  const ::MyVocaloid::ReplyHeader& _internal_header() const;
  public:
  const ::MyVocaloid::ReplyHeader& header() const;
  ::MyVocaloid::ReplyHeader* release_header();
  ::MyVocaloid::ReplyHeader* mutable_header();
  void set_allocated_header(::MyVocaloid::ReplyHeader* header);

  // .MyVocaloid.ReplyChunk chunk = 2;
  bool has_chunk() const;
  void clear_chunk();
  static const int kChunkFieldNumber = 2;
  private:
  const ::MyVocaloid::ReplyChunk& _internal_chunk() const;
  public:
  const ::MyVocaloid::ReplyChunk& chunk() const;
  ::MyVocaloid::ReplyChunk* release_chunk();
  ::MyVocaloid::ReplyChunk* mutable_chunk();
  void set_allocated_chunk(::MyVocaloid::ReplyChunk* chunk);

  void clear_ReplyData();
  ReplyDataCase ReplyData_case() const;
  // @@protoc_insertion_point(class_scope:MyVocaloid.SingReply)
 private:
  void set_has_header();
  void set_has_chunk();

  inline bool has_ReplyData() const;
  inline void clear_has_ReplyData();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  union ReplyDataUnion {
    ReplyDataUnion() {}
    ::MyVocaloid::ReplyHeader* header_;
    ::MyVocaloid::ReplyChunk* chunk_;
  } ReplyData_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::uint32 _oneof_case_[1];

  friend struct ::protobuf_protos_2fserver_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Note

// int32 note = 1;
inline void Note::clear_note() {
  note_ = 0;
}
inline ::google::protobuf::int32 Note::note() const {
  // @@protoc_insertion_point(field_get:MyVocaloid.Note.note)
  return note_;
}
inline void Note::set_note(::google::protobuf::int32 value) {
  
  note_ = value;
  // @@protoc_insertion_point(field_set:MyVocaloid.Note.note)
}

// int32 start = 2;
inline void Note::clear_start() {
  start_ = 0;
}
inline ::google::protobuf::int32 Note::start() const {
  // @@protoc_insertion_point(field_get:MyVocaloid.Note.start)
  return start_;
}
inline void Note::set_start(::google::protobuf::int32 value) {
  
  start_ = value;
  // @@protoc_insertion_point(field_set:MyVocaloid.Note.start)
}

// int32 duration = 3;
inline void Note::clear_duration() {
  duration_ = 0;
}
inline ::google::protobuf::int32 Note::duration() const {
  // @@protoc_insertion_point(field_get:MyVocaloid.Note.duration)
  return duration_;
}
inline void Note::set_duration(::google::protobuf::int32 value) {
  
  duration_ = value;
  // @@protoc_insertion_point(field_set:MyVocaloid.Note.duration)
}

// -------------------------------------------------------------------

// SingRequest

// int32 bpm = 1;
inline void SingRequest::clear_bpm() {
  bpm_ = 0;
}
inline ::google::protobuf::int32 SingRequest::bpm() const {
  // @@protoc_insertion_point(field_get:MyVocaloid.SingRequest.bpm)
  return bpm_;
}
inline void SingRequest::set_bpm(::google::protobuf::int32 value) {
  
  bpm_ = value;
  // @@protoc_insertion_point(field_set:MyVocaloid.SingRequest.bpm)
}

// string lyrics = 2;
inline void SingRequest::clear_lyrics() {
  lyrics_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& SingRequest::lyrics() const {
  // @@protoc_insertion_point(field_get:MyVocaloid.SingRequest.lyrics)
  return lyrics_.GetNoArena();
}
inline void SingRequest::set_lyrics(const ::std::string& value) {
  
  lyrics_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MyVocaloid.SingRequest.lyrics)
}
#if LANG_CXX11
inline void SingRequest::set_lyrics(::std::string&& value) {
  
  lyrics_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MyVocaloid.SingRequest.lyrics)
}
#endif
inline void SingRequest::set_lyrics(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  lyrics_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MyVocaloid.SingRequest.lyrics)
}
inline void SingRequest::set_lyrics(const char* value, size_t size) {
  
  lyrics_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MyVocaloid.SingRequest.lyrics)
}
inline ::std::string* SingRequest::mutable_lyrics() {
  
  // @@protoc_insertion_point(field_mutable:MyVocaloid.SingRequest.lyrics)
  return lyrics_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* SingRequest::release_lyrics() {
  // @@protoc_insertion_point(field_release:MyVocaloid.SingRequest.lyrics)
  
  return lyrics_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void SingRequest::set_allocated_lyrics(::std::string* lyrics) {
  if (lyrics != NULL) {
    
  } else {
    
  }
  lyrics_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), lyrics);
  // @@protoc_insertion_point(field_set_allocated:MyVocaloid.SingRequest.lyrics)
}

// repeated .MyVocaloid.Note notes = 3;
inline int SingRequest::notes_size() const {
  return notes_.size();
}
inline void SingRequest::clear_notes() {
  notes_.Clear();
}
inline ::MyVocaloid::Note* SingRequest::mutable_notes(int index) {
  // @@protoc_insertion_point(field_mutable:MyVocaloid.SingRequest.notes)
  return notes_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::MyVocaloid::Note >*
SingRequest::mutable_notes() {
  // @@protoc_insertion_point(field_mutable_list:MyVocaloid.SingRequest.notes)
  return &notes_;
}
inline const ::MyVocaloid::Note& SingRequest::notes(int index) const {
  // @@protoc_insertion_point(field_get:MyVocaloid.SingRequest.notes)
  return notes_.Get(index);
}
inline ::MyVocaloid::Note* SingRequest::add_notes() {
  // @@protoc_insertion_point(field_add:MyVocaloid.SingRequest.notes)
  return notes_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::MyVocaloid::Note >&
SingRequest::notes() const {
  // @@protoc_insertion_point(field_list:MyVocaloid.SingRequest.notes)
  return notes_;
}

// int32 bank = 4;
inline void SingRequest::clear_bank() {
  bank_ = 0;
}
inline ::google::protobuf::int32 SingRequest::bank() const {
  // @@protoc_insertion_point(field_get:MyVocaloid.SingRequest.bank)
  return bank_;
}
inline void SingRequest::set_bank(::google::protobuf::int32 value) {
  
  bank_ = value;
  // @@protoc_insertion_point(field_set:MyVocaloid.SingRequest.bank)
}

// -------------------------------------------------------------------

// ReplyHeader

// int32 result = 1;
inline void ReplyHeader::clear_result() {
  result_ = 0;
}
inline ::google::protobuf::int32 ReplyHeader::result() const {
  // @@protoc_insertion_point(field_get:MyVocaloid.ReplyHeader.result)
  return result_;
}
inline void ReplyHeader::set_result(::google::protobuf::int32 value) {
  
  result_ = value;
  // @@protoc_insertion_point(field_set:MyVocaloid.ReplyHeader.result)
}

// string message = 2;
inline void ReplyHeader::clear_message() {
  message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ReplyHeader::message() const {
  // @@protoc_insertion_point(field_get:MyVocaloid.ReplyHeader.message)
  return message_.GetNoArena();
}
inline void ReplyHeader::set_message(const ::std::string& value) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MyVocaloid.ReplyHeader.message)
}
#if LANG_CXX11
inline void ReplyHeader::set_message(::std::string&& value) {
  
  message_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MyVocaloid.ReplyHeader.message)
}
#endif
inline void ReplyHeader::set_message(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MyVocaloid.ReplyHeader.message)
}
inline void ReplyHeader::set_message(const char* value, size_t size) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MyVocaloid.ReplyHeader.message)
}
inline ::std::string* ReplyHeader::mutable_message() {
  
  // @@protoc_insertion_point(field_mutable:MyVocaloid.ReplyHeader.message)
  return message_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ReplyHeader::release_message() {
  // @@protoc_insertion_point(field_release:MyVocaloid.ReplyHeader.message)
  
  return message_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ReplyHeader::set_allocated_message(::std::string* message) {
  if (message != NULL) {
    
  } else {
    
  }
  message_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), message);
  // @@protoc_insertion_point(field_set_allocated:MyVocaloid.ReplyHeader.message)
}

// -------------------------------------------------------------------

// ReplyChunk

// bytes data = 1;
inline void ReplyChunk::clear_data() {
  data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ReplyChunk::data() const {
  // @@protoc_insertion_point(field_get:MyVocaloid.ReplyChunk.data)
  return data_.GetNoArena();
}
inline void ReplyChunk::set_data(const ::std::string& value) {
  
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MyVocaloid.ReplyChunk.data)
}
#if LANG_CXX11
inline void ReplyChunk::set_data(::std::string&& value) {
  
  data_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MyVocaloid.ReplyChunk.data)
}
#endif
inline void ReplyChunk::set_data(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MyVocaloid.ReplyChunk.data)
}
inline void ReplyChunk::set_data(const void* value, size_t size) {
  
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MyVocaloid.ReplyChunk.data)
}
inline ::std::string* ReplyChunk::mutable_data() {
  
  // @@protoc_insertion_point(field_mutable:MyVocaloid.ReplyChunk.data)
  return data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ReplyChunk::release_data() {
  // @@protoc_insertion_point(field_release:MyVocaloid.ReplyChunk.data)
  
  return data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ReplyChunk::set_allocated_data(::std::string* data) {
  if (data != NULL) {
    
  } else {
    
  }
  data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), data);
  // @@protoc_insertion_point(field_set_allocated:MyVocaloid.ReplyChunk.data)
}

// -------------------------------------------------------------------

// SingReply

// .MyVocaloid.ReplyHeader header = 1;
inline bool SingReply::has_header() const {
  return ReplyData_case() == kHeader;
}
inline void SingReply::set_has_header() {
  _oneof_case_[0] = kHeader;
}
inline void SingReply::clear_header() {
  if (has_header()) {
    delete ReplyData_.header_;
    clear_has_ReplyData();
  }
}
inline const ::MyVocaloid::ReplyHeader& SingReply::_internal_header() const {
  return *ReplyData_.header_;
}
inline ::MyVocaloid::ReplyHeader* SingReply::release_header() {
  // @@protoc_insertion_point(field_release:MyVocaloid.SingReply.header)
  if (has_header()) {
    clear_has_ReplyData();
      ::MyVocaloid::ReplyHeader* temp = ReplyData_.header_;
    ReplyData_.header_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
inline const ::MyVocaloid::ReplyHeader& SingReply::header() const {
  // @@protoc_insertion_point(field_get:MyVocaloid.SingReply.header)
  return has_header()
      ? *ReplyData_.header_
      : *reinterpret_cast< ::MyVocaloid::ReplyHeader*>(&::MyVocaloid::_ReplyHeader_default_instance_);
}
inline ::MyVocaloid::ReplyHeader* SingReply::mutable_header() {
  if (!has_header()) {
    clear_ReplyData();
    set_has_header();
    ReplyData_.header_ = CreateMaybeMessage< ::MyVocaloid::ReplyHeader >(
        GetArenaNoVirtual());
  }
  // @@protoc_insertion_point(field_mutable:MyVocaloid.SingReply.header)
  return ReplyData_.header_;
}

// .MyVocaloid.ReplyChunk chunk = 2;
inline bool SingReply::has_chunk() const {
  return ReplyData_case() == kChunk;
}
inline void SingReply::set_has_chunk() {
  _oneof_case_[0] = kChunk;
}
inline void SingReply::clear_chunk() {
  if (has_chunk()) {
    delete ReplyData_.chunk_;
    clear_has_ReplyData();
  }
}
inline const ::MyVocaloid::ReplyChunk& SingReply::_internal_chunk() const {
  return *ReplyData_.chunk_;
}
inline ::MyVocaloid::ReplyChunk* SingReply::release_chunk() {
  // @@protoc_insertion_point(field_release:MyVocaloid.SingReply.chunk)
  if (has_chunk()) {
    clear_has_ReplyData();
      ::MyVocaloid::ReplyChunk* temp = ReplyData_.chunk_;
    ReplyData_.chunk_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
inline const ::MyVocaloid::ReplyChunk& SingReply::chunk() const {
  // @@protoc_insertion_point(field_get:MyVocaloid.SingReply.chunk)
  return has_chunk()
      ? *ReplyData_.chunk_
      : *reinterpret_cast< ::MyVocaloid::ReplyChunk*>(&::MyVocaloid::_ReplyChunk_default_instance_);
}
inline ::MyVocaloid::ReplyChunk* SingReply::mutable_chunk() {
  if (!has_chunk()) {
    clear_ReplyData();
    set_has_chunk();
    ReplyData_.chunk_ = CreateMaybeMessage< ::MyVocaloid::ReplyChunk >(
        GetArenaNoVirtual());
  }
  // @@protoc_insertion_point(field_mutable:MyVocaloid.SingReply.chunk)
  return ReplyData_.chunk_;
}

inline bool SingReply::has_ReplyData() const {
  return ReplyData_case() != REPLYDATA_NOT_SET;
}
inline void SingReply::clear_has_ReplyData() {
  _oneof_case_[0] = REPLYDATA_NOT_SET;
}
inline SingReply::ReplyDataCase SingReply::ReplyData_case() const {
  return SingReply::ReplyDataCase(_oneof_case_[0]);
}
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace MyVocaloid

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_protos_2fserver_2eproto
