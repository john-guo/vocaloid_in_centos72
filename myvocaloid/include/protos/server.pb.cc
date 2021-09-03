// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/server.proto

#include "protos/server.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

namespace protobuf_protos_2fserver_2eproto {
extern PROTOBUF_INTERNAL_EXPORT_protobuf_protos_2fserver_2eproto ::google::protobuf::internal::SCCInfo<0> scc_info_Note;
}  // namespace protobuf_protos_2fserver_2eproto
namespace MyVocaloid {
class NoteDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<Note>
      _instance;
} _Note_default_instance_;
class SingRequestDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<SingRequest>
      _instance;
} _SingRequest_default_instance_;
class SingReplyDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<SingReply>
      _instance;
} _SingReply_default_instance_;
}  // namespace MyVocaloid
namespace protobuf_protos_2fserver_2eproto {
static void InitDefaultsNote() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::MyVocaloid::_Note_default_instance_;
    new (ptr) ::MyVocaloid::Note();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::MyVocaloid::Note::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_Note =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsNote}, {}};

static void InitDefaultsSingRequest() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::MyVocaloid::_SingRequest_default_instance_;
    new (ptr) ::MyVocaloid::SingRequest();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::MyVocaloid::SingRequest::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<1> scc_info_SingRequest =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsSingRequest}, {
      &protobuf_protos_2fserver_2eproto::scc_info_Note.base,}};

static void InitDefaultsSingReply() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::MyVocaloid::_SingReply_default_instance_;
    new (ptr) ::MyVocaloid::SingReply();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::MyVocaloid::SingReply::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_SingReply =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsSingReply}, {}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_Note.base);
  ::google::protobuf::internal::InitSCC(&scc_info_SingRequest.base);
  ::google::protobuf::internal::InitSCC(&scc_info_SingReply.base);
}

::google::protobuf::Metadata file_level_metadata[3];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::MyVocaloid::Note, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::MyVocaloid::Note, note_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::MyVocaloid::Note, start_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::MyVocaloid::Note, duration_),
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::MyVocaloid::SingRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::MyVocaloid::SingRequest, bpm_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::MyVocaloid::SingRequest, lyrics_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::MyVocaloid::SingRequest, notes_),
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::MyVocaloid::SingReply, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::MyVocaloid::SingReply, data_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::MyVocaloid::Note)},
  { 8, -1, sizeof(::MyVocaloid::SingRequest)},
  { 16, -1, sizeof(::MyVocaloid::SingReply)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::MyVocaloid::_Note_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::MyVocaloid::_SingRequest_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::MyVocaloid::_SingReply_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "protos/server.proto", schemas, file_default_instances, TableStruct::offsets,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 3);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\023protos/server.proto\022\nMyVocaloid\"5\n\004Not"
      "e\022\014\n\004note\030\001 \001(\005\022\r\n\005start\030\002 \001(\005\022\020\n\010durati"
      "on\030\003 \001(\005\"K\n\013SingRequest\022\013\n\003bpm\030\001 \001(\005\022\016\n\006"
      "lyrics\030\002 \001(\t\022\037\n\005notes\030\003 \003(\0132\020.MyVocaloid"
      ".Note\"\031\n\tSingReply\022\014\n\004data\030\001 \003(\0052D\n\010Voca"
      "loid\0228\n\004Sing\022\027.MyVocaloid.SingRequest\032\025."
      "MyVocaloid.SingReply\"\000b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 270);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "protos/server.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_protos_2fserver_2eproto
namespace MyVocaloid {

// ===================================================================

void Note::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Note::kNoteFieldNumber;
const int Note::kStartFieldNumber;
const int Note::kDurationFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Note::Note()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_protos_2fserver_2eproto::scc_info_Note.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:MyVocaloid.Note)
}
Note::Note(const Note& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&note_, &from.note_,
    static_cast<size_t>(reinterpret_cast<char*>(&duration_) -
    reinterpret_cast<char*>(&note_)) + sizeof(duration_));
  // @@protoc_insertion_point(copy_constructor:MyVocaloid.Note)
}

void Note::SharedCtor() {
  ::memset(&note_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&duration_) -
      reinterpret_cast<char*>(&note_)) + sizeof(duration_));
}

Note::~Note() {
  // @@protoc_insertion_point(destructor:MyVocaloid.Note)
  SharedDtor();
}

void Note::SharedDtor() {
}

void Note::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* Note::descriptor() {
  ::protobuf_protos_2fserver_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_protos_2fserver_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const Note& Note::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_protos_2fserver_2eproto::scc_info_Note.base);
  return *internal_default_instance();
}


void Note::Clear() {
// @@protoc_insertion_point(message_clear_start:MyVocaloid.Note)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&note_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&duration_) -
      reinterpret_cast<char*>(&note_)) + sizeof(duration_));
  _internal_metadata_.Clear();
}

bool Note::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:MyVocaloid.Note)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 note = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &note_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 start = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &start_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 duration = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(24u /* 24 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &duration_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:MyVocaloid.Note)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:MyVocaloid.Note)
  return false;
#undef DO_
}

void Note::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:MyVocaloid.Note)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 note = 1;
  if (this->note() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->note(), output);
  }

  // int32 start = 2;
  if (this->start() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->start(), output);
  }

  // int32 duration = 3;
  if (this->duration() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->duration(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:MyVocaloid.Note)
}

::google::protobuf::uint8* Note::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:MyVocaloid.Note)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 note = 1;
  if (this->note() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->note(), target);
  }

  // int32 start = 2;
  if (this->start() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->start(), target);
  }

  // int32 duration = 3;
  if (this->duration() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->duration(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MyVocaloid.Note)
  return target;
}

size_t Note::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:MyVocaloid.Note)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // int32 note = 1;
  if (this->note() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->note());
  }

  // int32 start = 2;
  if (this->start() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->start());
  }

  // int32 duration = 3;
  if (this->duration() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->duration());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Note::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:MyVocaloid.Note)
  GOOGLE_DCHECK_NE(&from, this);
  const Note* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Note>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:MyVocaloid.Note)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:MyVocaloid.Note)
    MergeFrom(*source);
  }
}

void Note::MergeFrom(const Note& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:MyVocaloid.Note)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.note() != 0) {
    set_note(from.note());
  }
  if (from.start() != 0) {
    set_start(from.start());
  }
  if (from.duration() != 0) {
    set_duration(from.duration());
  }
}

void Note::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:MyVocaloid.Note)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Note::CopyFrom(const Note& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:MyVocaloid.Note)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Note::IsInitialized() const {
  return true;
}

void Note::Swap(Note* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Note::InternalSwap(Note* other) {
  using std::swap;
  swap(note_, other->note_);
  swap(start_, other->start_);
  swap(duration_, other->duration_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata Note::GetMetadata() const {
  protobuf_protos_2fserver_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_protos_2fserver_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void SingRequest::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int SingRequest::kBpmFieldNumber;
const int SingRequest::kLyricsFieldNumber;
const int SingRequest::kNotesFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

SingRequest::SingRequest()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_protos_2fserver_2eproto::scc_info_SingRequest.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:MyVocaloid.SingRequest)
}
SingRequest::SingRequest(const SingRequest& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      notes_(from.notes_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  lyrics_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.lyrics().size() > 0) {
    lyrics_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.lyrics_);
  }
  bpm_ = from.bpm_;
  // @@protoc_insertion_point(copy_constructor:MyVocaloid.SingRequest)
}

void SingRequest::SharedCtor() {
  lyrics_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  bpm_ = 0;
}

SingRequest::~SingRequest() {
  // @@protoc_insertion_point(destructor:MyVocaloid.SingRequest)
  SharedDtor();
}

void SingRequest::SharedDtor() {
  lyrics_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void SingRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* SingRequest::descriptor() {
  ::protobuf_protos_2fserver_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_protos_2fserver_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const SingRequest& SingRequest::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_protos_2fserver_2eproto::scc_info_SingRequest.base);
  return *internal_default_instance();
}


void SingRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:MyVocaloid.SingRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  notes_.Clear();
  lyrics_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  bpm_ = 0;
  _internal_metadata_.Clear();
}

bool SingRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:MyVocaloid.SingRequest)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 bpm = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &bpm_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string lyrics = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_lyrics()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->lyrics().data(), static_cast<int>(this->lyrics().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "MyVocaloid.SingRequest.lyrics"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .MyVocaloid.Note notes = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u /* 26 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
                input, add_notes()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:MyVocaloid.SingRequest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:MyVocaloid.SingRequest)
  return false;
#undef DO_
}

void SingRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:MyVocaloid.SingRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 bpm = 1;
  if (this->bpm() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->bpm(), output);
  }

  // string lyrics = 2;
  if (this->lyrics().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->lyrics().data(), static_cast<int>(this->lyrics().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "MyVocaloid.SingRequest.lyrics");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->lyrics(), output);
  }

  // repeated .MyVocaloid.Note notes = 3;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->notes_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3,
      this->notes(static_cast<int>(i)),
      output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:MyVocaloid.SingRequest)
}

::google::protobuf::uint8* SingRequest::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:MyVocaloid.SingRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 bpm = 1;
  if (this->bpm() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->bpm(), target);
  }

  // string lyrics = 2;
  if (this->lyrics().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->lyrics().data(), static_cast<int>(this->lyrics().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "MyVocaloid.SingRequest.lyrics");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->lyrics(), target);
  }

  // repeated .MyVocaloid.Note notes = 3;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->notes_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        3, this->notes(static_cast<int>(i)), deterministic, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MyVocaloid.SingRequest)
  return target;
}

size_t SingRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:MyVocaloid.SingRequest)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // repeated .MyVocaloid.Note notes = 3;
  {
    unsigned int count = static_cast<unsigned int>(this->notes_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSize(
          this->notes(static_cast<int>(i)));
    }
  }

  // string lyrics = 2;
  if (this->lyrics().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->lyrics());
  }

  // int32 bpm = 1;
  if (this->bpm() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->bpm());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void SingRequest::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:MyVocaloid.SingRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const SingRequest* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const SingRequest>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:MyVocaloid.SingRequest)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:MyVocaloid.SingRequest)
    MergeFrom(*source);
  }
}

void SingRequest::MergeFrom(const SingRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:MyVocaloid.SingRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  notes_.MergeFrom(from.notes_);
  if (from.lyrics().size() > 0) {

    lyrics_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.lyrics_);
  }
  if (from.bpm() != 0) {
    set_bpm(from.bpm());
  }
}

void SingRequest::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:MyVocaloid.SingRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SingRequest::CopyFrom(const SingRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:MyVocaloid.SingRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SingRequest::IsInitialized() const {
  return true;
}

void SingRequest::Swap(SingRequest* other) {
  if (other == this) return;
  InternalSwap(other);
}
void SingRequest::InternalSwap(SingRequest* other) {
  using std::swap;
  CastToBase(&notes_)->InternalSwap(CastToBase(&other->notes_));
  lyrics_.Swap(&other->lyrics_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(bpm_, other->bpm_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata SingRequest::GetMetadata() const {
  protobuf_protos_2fserver_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_protos_2fserver_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void SingReply::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int SingReply::kDataFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

SingReply::SingReply()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_protos_2fserver_2eproto::scc_info_SingReply.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:MyVocaloid.SingReply)
}
SingReply::SingReply(const SingReply& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      data_(from.data_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:MyVocaloid.SingReply)
}

void SingReply::SharedCtor() {
}

SingReply::~SingReply() {
  // @@protoc_insertion_point(destructor:MyVocaloid.SingReply)
  SharedDtor();
}

void SingReply::SharedDtor() {
}

void SingReply::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* SingReply::descriptor() {
  ::protobuf_protos_2fserver_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_protos_2fserver_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const SingReply& SingReply::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_protos_2fserver_2eproto::scc_info_SingReply.base);
  return *internal_default_instance();
}


void SingReply::Clear() {
// @@protoc_insertion_point(message_clear_start:MyVocaloid.SingReply)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  data_.Clear();
  _internal_metadata_.Clear();
}

bool SingReply::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:MyVocaloid.SingReply)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated int32 data = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, this->mutable_data())));
        } else if (
            static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitiveNoInline<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 1, 10u, input, this->mutable_data())));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:MyVocaloid.SingReply)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:MyVocaloid.SingReply)
  return false;
#undef DO_
}

void SingReply::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:MyVocaloid.SingReply)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated int32 data = 1;
  if (this->data_size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteTag(1, ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, output);
    output->WriteVarint32(static_cast< ::google::protobuf::uint32>(
        _data_cached_byte_size_));
  }
  for (int i = 0, n = this->data_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32NoTag(
      this->data(i), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:MyVocaloid.SingReply)
}

::google::protobuf::uint8* SingReply::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:MyVocaloid.SingReply)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated int32 data = 1;
  if (this->data_size() > 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
      1,
      ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
      target);
    target = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
        static_cast< ::google::protobuf::int32>(
            _data_cached_byte_size_), target);
    target = ::google::protobuf::internal::WireFormatLite::
      WriteInt32NoTagToArray(this->data_, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MyVocaloid.SingReply)
  return target;
}

size_t SingReply::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:MyVocaloid.SingReply)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // repeated int32 data = 1;
  {
    size_t data_size = ::google::protobuf::internal::WireFormatLite::
      Int32Size(this->data_);
    if (data_size > 0) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
            static_cast< ::google::protobuf::int32>(data_size));
    }
    int cached_size = ::google::protobuf::internal::ToCachedSize(data_size);
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _data_cached_byte_size_ = cached_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    total_size += data_size;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void SingReply::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:MyVocaloid.SingReply)
  GOOGLE_DCHECK_NE(&from, this);
  const SingReply* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const SingReply>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:MyVocaloid.SingReply)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:MyVocaloid.SingReply)
    MergeFrom(*source);
  }
}

void SingReply::MergeFrom(const SingReply& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:MyVocaloid.SingReply)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  data_.MergeFrom(from.data_);
}

void SingReply::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:MyVocaloid.SingReply)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SingReply::CopyFrom(const SingReply& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:MyVocaloid.SingReply)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SingReply::IsInitialized() const {
  return true;
}

void SingReply::Swap(SingReply* other) {
  if (other == this) return;
  InternalSwap(other);
}
void SingReply::InternalSwap(SingReply* other) {
  using std::swap;
  data_.InternalSwap(&other->data_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata SingReply::GetMetadata() const {
  protobuf_protos_2fserver_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_protos_2fserver_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace MyVocaloid
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::MyVocaloid::Note* Arena::CreateMaybeMessage< ::MyVocaloid::Note >(Arena* arena) {
  return Arena::CreateInternal< ::MyVocaloid::Note >(arena);
}
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::MyVocaloid::SingRequest* Arena::CreateMaybeMessage< ::MyVocaloid::SingRequest >(Arena* arena) {
  return Arena::CreateInternal< ::MyVocaloid::SingRequest >(arena);
}
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::MyVocaloid::SingReply* Arena::CreateMaybeMessage< ::MyVocaloid::SingReply >(Arena* arena) {
  return Arena::CreateInternal< ::MyVocaloid::SingReply >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)