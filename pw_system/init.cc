// Copyright 2021 The Pigweed Authors
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

#include "pw_system/init.h"

#include "pw_log/log.h"
#include "pw_rpc/echo_service_nanopb.h"
#include "pw_system/thread_options.h"
#include "pw_system_private/log.h"
#include "pw_system_private/rpc.h"
#include "pw_thread/detached_thread.h"

namespace pw::system {
namespace {
rpc::EchoService echo_service;
}  // namespace

void Init() {
  PW_LOG_INFO("System init");

  // Setup logging.
  const Status status = GetLogThread().OpenUnrequestedLogStream(
      kDefaultChannelId, GetRpcServer(), GetLogService());
  if (!status.ok()) {
    PW_LOG_ERROR("Error opening OpenUnrequestedLogStream %s", status.str());
  }

  PW_LOG_INFO("Registering RPC services");
  GetRpcServer().RegisterService(echo_service);
  GetRpcServer().RegisterService(GetLogService());

  PW_LOG_INFO("Starting threads");
  // Start threads.
  thread::DetachedThread(system::LogThreadOptions(), GetLogThread());
  thread::DetachedThread(system::RpcThreadOptions(), GetRpcDispatchThread());
}

}  // namespace pw::system
