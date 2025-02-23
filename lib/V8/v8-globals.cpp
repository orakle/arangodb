////////////////////////////////////////////////////////////////////////////////
/// @brief V8 globals
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2014 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Jan Steemann
/// @author Copyright 2014, ArangoDB GmbH, Cologne, Germany
/// @author Copyright 2012-2014, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#include "v8-globals.h"

// -----------------------------------------------------------------------------
// --SECTION--                                                      public types
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief constructor
////////////////////////////////////////////////////////////////////////////////

TRI_v8_global_s::TRI_v8_global_s (v8::Isolate* isolate)
  : JSCollections(),
    JSDitches(),

    AgencyTempl(),
    ClusterInfoTempl(),
    ServerStateTempl(),
    ClusterCommTempl(),
    ArangoErrorTempl(),
    SleepAndRequeueTempl(),
    SleepAndRequeueFuncTempl(),
    GeneralCursorTempl(),
    ShapedJsonTempl(),
    VocbaseColTempl(),
    VocbaseTempl(),

    BufferTempl(),
    FastBufferConstructor(),
    ExecuteFileCallback(),

    BufferConstant(),
    DeleteConstant(),
    GetConstant(),
    HeadConstant(),
    OptionsConstant(),
    PatchConstant(),
    PostConstant(),
    PutConstant(),

    AddressKey(),
    AllowUseDatabaseKey(),
    BodyFromFileKey(),
    BodyKey(),
    ClientKey(),
    ClientTransactionIDKey(),
    CodeKey(),
    CompatibilityKey(),
    ContentTypeKey(),
    CoordTransactionIDKey(),
    DatabaseKey(),
    DoCompactKey(),
    DomainKey(),
    ErrorKey(),
    ErrorMessageKey(),
    ErrorNumKey(),
    HeadersKey(),
    HttpOnlyKey(),
    IdKey(),
    IsSystemKey(),
    IsVolatileKey(),
    JournalSizeKey(),
    KeepNullKey(),
    KeyOptionsKey(),
    LengthKey(),
    LifeTimeKey(),
    MergeObjectsKey(),
    NameKey(),
    OperationIDKey(),
    ParametersKey(),
    PathKey(),
    PrefixKey(),
    PortKey(),
    PortTypeKey(),
    ProtocolKey(),
    RequestBodyKey(),
    RequestTypeKey(),
    ResponseCodeKey(),
    SecureKey(),
    ServerKey(),
    ShardIDKey(),
    SilentKey(),
    SleepKey(),
    StatusKey(),
    SuffixKey(),
    TimeoutKey(),
    TransformationsKey(),
    UrlKey(),
    UserKey(),
    ValueKey(),
    VersionKey(),
    VersionKeyHidden(),
    WaitForSyncKey(),

    _FromKey(),
    _DbNameKey(),
    _IdKey(),
    _KeyKey(),
    _OldRevKey(),
    _RevKey(),
    _ToKey(),

    _currentRequest(),
    _currentResponse(),
    _transactionContext(nullptr),
    _queryRegistry(nullptr),
    _query(nullptr),
    _server(nullptr),
    _vocbase(nullptr),
    _allowUseDatabase(true),
    _hasDeadObjects(false),
    _applicationV8(nullptr),
    _loader(nullptr),
    _canceled(false)


{
  v8::HandleScope scope(isolate);

  BufferConstant.Reset(isolate, TRI_V8_ASCII_STRING("Buffer"));
  DeleteConstant.Reset(isolate, TRI_V8_ASCII_STRING("DELETE"));
  GetConstant.Reset(isolate, TRI_V8_ASCII_STRING("GET"));
  HeadConstant.Reset(isolate, TRI_V8_ASCII_STRING("HEAD"));
  OptionsConstant.Reset(isolate, TRI_V8_ASCII_STRING("OPTIONS"));
  PatchConstant.Reset(isolate, TRI_V8_ASCII_STRING("PATCH"));
  PostConstant.Reset(isolate, TRI_V8_ASCII_STRING("POST"));
  PutConstant.Reset(isolate, TRI_V8_ASCII_STRING("PUT"));

  AddressKey.Reset(isolate, TRI_V8_ASCII_STRING("address"));
  AllowUseDatabaseKey.Reset(isolate, TRI_V8_ASCII_STRING("allowUseDatabase"));
  BodyFromFileKey.Reset(isolate, TRI_V8_ASCII_STRING("bodyFromFile"));
  BodyKey.Reset(isolate, TRI_V8_ASCII_STRING("body"));
  ClientKey.Reset(isolate, TRI_V8_ASCII_STRING("client"));
  ClientTransactionIDKey.Reset(isolate, TRI_V8_ASCII_STRING("clientTransactionID"));
  CodeKey.Reset(isolate, TRI_V8_ASCII_STRING("code"));
  CompatibilityKey.Reset(isolate, TRI_V8_ASCII_STRING("compatibility"));
  ContentTypeKey.Reset(isolate, TRI_V8_ASCII_STRING("contentType"));
  CookiesKey.Reset(isolate, TRI_V8_ASCII_STRING("cookies"));
  CoordTransactionIDKey.Reset(isolate, TRI_V8_ASCII_STRING("coordTransactionID"));
  DatabaseKey.Reset(isolate, TRI_V8_ASCII_STRING("database"));
  DoCompactKey.Reset(isolate, TRI_V8_ASCII_STRING("doCompact"));
  DomainKey.Reset(isolate, TRI_V8_ASCII_STRING("domain"));
  ErrorKey.Reset(isolate, TRI_V8_ASCII_STRING("error"));
  ErrorMessageKey.Reset(isolate, TRI_V8_ASCII_STRING("errorMessage"));
  ErrorNumKey.Reset(isolate, TRI_V8_ASCII_STRING("errorNum"));
  HeadersKey.Reset(isolate, TRI_V8_ASCII_STRING("headers"));
  HttpOnlyKey.Reset(isolate, TRI_V8_ASCII_STRING("httpOnly"));
  IdKey.Reset(isolate, TRI_V8_ASCII_STRING("id"));
  IsSystemKey.Reset(isolate, TRI_V8_ASCII_STRING("isSystem"));
  IsVolatileKey.Reset(isolate, TRI_V8_ASCII_STRING("isVolatile"));
  JournalSizeKey.Reset(isolate, TRI_V8_ASCII_STRING("journalSize"));
  KeepNullKey.Reset(isolate, TRI_V8_ASCII_STRING("keepNull"));
  KeyOptionsKey.Reset(isolate, TRI_V8_ASCII_STRING("keyOptions"));
  LengthKey.Reset(isolate, TRI_V8_ASCII_STRING("length"));
  LifeTimeKey.Reset(isolate, TRI_V8_ASCII_STRING("lifeTime"));
  MergeObjectsKey.Reset(isolate, TRI_V8_ASCII_STRING("mergeObjects"));
  NameKey.Reset(isolate, TRI_V8_ASCII_STRING("name"));
  OperationIDKey.Reset(isolate, TRI_V8_ASCII_STRING("operationID"));
  OverwriteKey.Reset(isolate, TRI_V8_ASCII_STRING("overwrite"));
  ParametersKey.Reset(isolate, TRI_V8_ASCII_STRING("parameters"));
  PathKey.Reset(isolate, TRI_V8_ASCII_STRING("path"));
  PrefixKey.Reset(isolate, TRI_V8_ASCII_STRING("prefix"));
  PortKey.Reset(isolate, TRI_V8_ASCII_STRING("port"));
  PortTypeKey.Reset(isolate, TRI_V8_ASCII_STRING("portType"));
  ProtocolKey.Reset(isolate, TRI_V8_ASCII_STRING("protocol"));
  RequestBodyKey.Reset(isolate, TRI_V8_ASCII_STRING("requestBody"));
  RequestTypeKey.Reset(isolate, TRI_V8_ASCII_STRING("requestType"));
  ResponseCodeKey.Reset(isolate, TRI_V8_ASCII_STRING("responseCode"));
  SecureKey.Reset(isolate, TRI_V8_ASCII_STRING("secure"));
  ServerKey.Reset(isolate, TRI_V8_ASCII_STRING("server"));
  ShardIDKey.Reset(isolate, TRI_V8_ASCII_STRING("shardID"));
  SilentKey.Reset(isolate, TRI_V8_ASCII_STRING("silent"));
  SleepKey.Reset(isolate, TRI_V8_ASCII_STRING("sleep"));
  StatusKey.Reset(isolate, TRI_V8_ASCII_STRING("status"));
  SuffixKey.Reset(isolate, TRI_V8_ASCII_STRING("suffix"));
  TimeoutKey.Reset(isolate, TRI_V8_ASCII_STRING("timeout"));
  TransformationsKey.Reset(isolate, TRI_V8_ASCII_STRING("transformations"));
  UrlKey.Reset(isolate, TRI_V8_ASCII_STRING("url"));
  UserKey.Reset(isolate, TRI_V8_ASCII_STRING("user"));
  ValueKey.Reset(isolate, TRI_V8_ASCII_STRING("value"));
  VersionKey.Reset(isolate, TRI_V8_ASCII_STRING("version"));
  VersionKeyHidden.Reset(isolate, TRI_V8_ASCII_STRING("*version"));
  WaitForSyncKey.Reset(isolate, TRI_V8_ASCII_STRING("waitForSync"));

  _FromKey.Reset(isolate, TRI_V8_ASCII_STRING("_from"));
  _DbNameKey.Reset(isolate, TRI_V8_ASCII_STRING("_dbName"));
  _IdKey.Reset(isolate, TRI_V8_ASCII_STRING("_id"));
  _KeyKey.Reset(isolate, TRI_V8_ASCII_STRING("_key"));
  _OldRevKey.Reset(isolate, TRI_V8_ASCII_STRING("_oldRev"));
  _RevKey.Reset(isolate, TRI_V8_ASCII_STRING("_rev"));
  _ToKey.Reset(isolate, TRI_V8_ASCII_STRING("_to"));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief destructor
////////////////////////////////////////////////////////////////////////////////

TRI_v8_global_s::~TRI_v8_global_s () {
}

// -----------------------------------------------------------------------------
// --SECTION--                                                  GLOBAL FUNCTIONS
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a global context
////////////////////////////////////////////////////////////////////////////////

TRI_v8_global_t* TRI_CreateV8Globals (v8::Isolate* isolate) {
  TRI_GET_GLOBALS();

  TRI_ASSERT(v8g == nullptr);
  v8g = new TRI_v8_global_t(isolate);
  isolate->SetData(V8DataSlot, v8g);

  return v8g;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief returns a global context
////////////////////////////////////////////////////////////////////////////////

TRI_v8_global_t* TRI_GetV8Globals (v8::Isolate* isolate) {
  TRI_GET_GLOBALS();
  if (v8g == nullptr) {
    v8g = TRI_CreateV8Globals(isolate);
  }

  TRI_ASSERT(v8g != nullptr);
  return v8g;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a method to an object
////////////////////////////////////////////////////////////////////////////////

void TRI_AddMethodVocbase (v8::Isolate* isolate,
                           v8::Handle<v8::ObjectTemplate> tpl,
                           v8::Handle<v8::String> name,
                           void(*func)(v8::FunctionCallbackInfo<v8::Value> const&),
                           bool isHidden) {
  if (isHidden) {
    // hidden method
    tpl->Set(name, v8::FunctionTemplate::New(isolate, func), v8::DontEnum);
  }
  else {
    // normal method
    tpl->Set(name, v8::FunctionTemplate::New(isolate, func));
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a global function to the given context
////////////////////////////////////////////////////////////////////////////////

void TRI_AddGlobalFunctionVocbase (v8::Isolate* isolate,
                                   v8::Handle<v8::Context> context,
                                   v8::Handle<v8::String> name,
                                   void(*func)(v8::FunctionCallbackInfo<v8::Value> const&),
                                   bool isHidden) {
  // all global functions are read-only
  if (isHidden) {
    context->Global()->ForceSet(name,
                                v8::FunctionTemplate::New(isolate, func)->GetFunction(),
                                static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontEnum));
  }
  else {
    context->Global()->ForceSet(name,
                                v8::FunctionTemplate::New(isolate, func)->GetFunction(),
                                v8::ReadOnly);
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a global function to the given context
////////////////////////////////////////////////////////////////////////////////

void TRI_AddGlobalFunctionVocbase (v8::Isolate* isolate,
                                   v8::Handle<v8::Context> context,
                                   v8::Handle<v8::String> name,
                                   v8::Handle<v8::Function> func,
                                   bool isHidden) {
  // all global functions are read-only
  if (isHidden) {
    context->Global()->ForceSet(name,
                                func,
                                static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontEnum));
  }
  else {
    context->Global()->ForceSet(name,
                                func,
                                v8::ReadOnly);
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a global read-only variable to the given context
////////////////////////////////////////////////////////////////////////////////

void TRI_AddGlobalVariableVocbase (v8::Isolate* isolate,
                                   v8::Handle<v8::Context> context,
                                   v8::Handle<v8::String> name,
                                   v8::Handle<v8::Value> value) {
  // all global variables are read-only
  context->Global()->ForceSet(name, value, v8::ReadOnly);
}

// -----------------------------------------------------------------------------
// --SECTION--                                                       END-OF-FILE
// -----------------------------------------------------------------------------

// Local Variables:
// mode: outline-minor
// outline-regexp: "/// @brief\\|/// {@inheritDoc}\\|/// @page\\|// --SECTION--\\|/// @\\}"
// End:
