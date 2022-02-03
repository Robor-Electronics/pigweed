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

#include "pw_assert/assert.h"
#include "pw_containers/intrusive_list.h"
#include "pw_result/result.h"
#include "pw_rpc/raw/server_reader_writer.h"
#include "pw_transfer/handler.h"
#include "pw_transfer/internal/context.h"

namespace pw::transfer::internal {

// Transfer context for use within the transfer service (server-side). Stores a
// pointer to a transfer handler when active to stream the transfer data.
class ServerContext final : public Context {
 public:
  constexpr ServerContext()
      : type_(TransferType::kTransmit), handler_(nullptr) {}

 private:
  // Begins a new transfer with the specified type and handler. Calls into the
  // handler's Prepare method.
  //
  // Precondition: Context is not already active.
  Status StartTransfer(const NewTransferEvent& new_transfer) override;

  // Ends the transfer with the given status, calling the handler's Finalize
  // method. No chunks are sent.
  //
  // Returns DATA_LOSS if the finalize call fails.
  //
  // Precondition: Transfer context is active.
  Status DoFinish(Status status) override;

  TransferType type_;
  Handler* handler_;
};

}  // namespace pw::transfer::internal
