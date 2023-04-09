# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: packet.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0cpacket.proto\x12\x0fpw.rpc.internal\"\xa3\x01\n\tRpcPacket\x12)\n\x04type\x18\x01 \x01(\x0e\x32\x1b.pw.rpc.internal.PacketType\x12\x12\n\nchannel_id\x18\x02 \x01(\r\x12\x12\n\nservice_id\x18\x03 \x01(\x07\x12\x11\n\tmethod_id\x18\x04 \x01(\x07\x12\x0f\n\x07payload\x18\x05 \x01(\x0c\x12\x0e\n\x06status\x18\x06 \x01(\r\x12\x0f\n\x07\x63\x61ll_id\x18\x07 \x01(\r*\xc1\x01\n\nPacketType\x12\x0b\n\x07REQUEST\x10\x00\x12\x11\n\rCLIENT_STREAM\x10\x02\x12\x10\n\x0c\x43LIENT_ERROR\x10\x04\x12\x15\n\x11\x44\x45PRECATED_CANCEL\x10\x06\x12\x15\n\x11\x43LIENT_STREAM_END\x10\x08\x12\x0c\n\x08RESPONSE\x10\x01\x12 \n\x1c\x44\x45PRECATED_SERVER_STREAM_END\x10\x03\x12\x10\n\x0cSERVER_ERROR\x10\x05\x12\x11\n\rSERVER_STREAM\x10\x07\x42\x1d\n\x1b\x64\x65v.pigweed.pw_rpc.internalb\x06proto3')

_PACKETTYPE = DESCRIPTOR.enum_types_by_name['PacketType']
PacketType = enum_type_wrapper.EnumTypeWrapper(_PACKETTYPE)
REQUEST = 0
CLIENT_STREAM = 2
CLIENT_ERROR = 4
DEPRECATED_CANCEL = 6
CLIENT_STREAM_END = 8
RESPONSE = 1
DEPRECATED_SERVER_STREAM_END = 3
SERVER_ERROR = 5
SERVER_STREAM = 7


_RPCPACKET = DESCRIPTOR.message_types_by_name['RpcPacket']
RpcPacket = _reflection.GeneratedProtocolMessageType('RpcPacket', (_message.Message,), {
  'DESCRIPTOR' : _RPCPACKET,
  '__module__' : 'packet_pb2'
  # @@protoc_insertion_point(class_scope:pw.rpc.internal.RpcPacket)
  })
_sym_db.RegisterMessage(RpcPacket)

if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\033dev.pigweed.pw_rpc.internal'
  _PACKETTYPE._serialized_start=200
  _PACKETTYPE._serialized_end=393
  _RPCPACKET._serialized_start=34
  _RPCPACKET._serialized_end=197
# @@protoc_insertion_point(module_scope)