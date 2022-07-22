// Copyright 2022 The Pigweed Authors
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.
#pragma once

#include "pw_stream/stream.h"

namespace pw::software_update {

// A SeekableReader that needs Open/Closed state management. This abstraction
// decouples pw_software_update from pw_blob_store.
class OpenableReader {
 public:
  explicit constexpr OpenableReader(stream::SeekableReader& reader)
      : reader_(reader) {}

  virtual Status Open() = 0;
  virtual Status Close() = 0;
  virtual bool IsOpen() = 0;

  stream::SeekableReader& reader() const { return reader_; }

 private:
  stream::SeekableReader& reader_;
};

}  // namespace pw::software_update
