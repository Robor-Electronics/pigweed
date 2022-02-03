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

#define PW_LOG_MODULE_NAME "TRN"

#include "pw_transfer/internal/server_context.h"

#include "pw_assert/check.h"
#include "pw_log/log.h"
#include "pw_status/try.h"
#include "pw_transfer/internal/chunk.h"
#include "pw_transfer/transfer.pwpb.h"
#include "pw_varint/varint.h"

namespace pw::transfer::internal {

Status ServerContext::StartTransfer(const NewTransferEvent& new_transfer) {
  PW_DCHECK(!active());

  PW_LOG_INFO("Starting transfer %u with handler %u",
              static_cast<unsigned>(new_transfer.transfer_id),
              static_cast<unsigned>(new_transfer.handler_id));

  type_ = new_transfer.type;
  handler_ = new_transfer.handler;

  if (const Status status = handler_->Prepare(type_); !status.ok()) {
    PW_LOG_WARN("Transfer handler %u prepare failed with status %u",
                static_cast<unsigned>(handler_->id()),
                status.code());
    return status.IsPermissionDenied() ? status : Status::DataLoss();
  }

  if (new_transfer.type == TransferType::kTransmit) {
    InitializeForTransmit(handler_->id(),
                          *new_transfer.rpc_writer,
                          handler_->reader(),
                          new_transfer.max_parameters,
                          *new_transfer.transfer_thread,
                          new_transfer.timeout,
                          new_transfer.max_retries);
  } else {
    InitializeForReceive(handler_->id(),
                         *new_transfer.rpc_writer,
                         handler_->writer(),
                         new_transfer.max_parameters,
                         *new_transfer.transfer_thread,
                         new_transfer.timeout,
                         new_transfer.max_retries);
  }

  return OkStatus();
}

Status ServerContext::DoFinish(const Status status) {
  PW_DCHECK(active());

  Handler& handler = *handler_;
  set_transfer_state(TransferState::kCompleted);

  if (type_ == TransferType::kTransmit) {
    handler.FinalizeRead(status);
    return OkStatus();
  }

  if (Status finalized = handler.FinalizeWrite(status); !finalized.ok()) {
    PW_LOG_ERROR(
        "FinalizeWrite() for transfer %u failed with status %u; aborting with "
        "DATA_LOSS",
        static_cast<unsigned>(handler.id()),
        static_cast<int>(finalized.code()));
    return Status::DataLoss();
  }

  return OkStatus();
}

}  // namespace pw::transfer::internal
