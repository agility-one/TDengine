/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// clang-format off

#define _DEFAULT_SOURCE
#include "os.h"
#include "taoserror.h"

#define TAOS_ERROR_C

typedef struct {
  int32_t     val;
  const char* str;
} STaosError;

static threadlocal int32_t tsErrno;

int32_t* taosGetErrno() { return &tsErrno; }

#ifdef TAOS_ERROR_C
#define TAOS_DEFINE_ERROR(name, msg) {.val = (name), .str = (msg)},
#else
#define TAOS_DEFINE_ERROR(name, mod, code, msg) static const int32_t name = TAOS_DEF_ERROR_CODE(mod, code);
#endif

#define TAOS_SYSTEM_ERROR(code) (0x80ff0000 | (code))
#define TAOS_SUCCEEDED(err)     ((err) >= 0)
#define TAOS_FAILED(err)        ((err) < 0)

#ifdef TAOS_ERROR_C
STaosError errors[] = {
    {.val = 0, .str = "success"},
#endif

//common & util
TAOS_DEFINE_ERROR(TSDB_CODE_ACTION_IN_PROGRESS,           "Action in progress")
TAOS_DEFINE_ERROR(TSDB_CODE_APP_ERROR,                    "Unexpected generic error")
TAOS_DEFINE_ERROR(TSDB_CODE_APP_NOT_READY,                "Database not ready")
TAOS_DEFINE_ERROR(TSDB_CODE_OUT_OF_MEMORY,                "Out of Memory")
TAOS_DEFINE_ERROR(TSDB_CODE_OUT_OF_RANGE,                 "Out of range")
TAOS_DEFINE_ERROR(TSDB_CODE_OUT_OF_SHM_MEM,               "Out of Shared memory")
TAOS_DEFINE_ERROR(TSDB_CODE_INVALID_SHM_ID,               "Invalid SHM ID")
TAOS_DEFINE_ERROR(TSDB_CODE_INVALID_PTR,                  "Invalid pointer")
TAOS_DEFINE_ERROR(TSDB_CODE_INVALID_MSG,                  "Invalid message")
TAOS_DEFINE_ERROR(TSDB_CODE_INVALID_MSG_LEN,              "Invalid message len")
TAOS_DEFINE_ERROR(TSDB_CODE_INVALID_PARA,                 "Invalid parameters")
TAOS_DEFINE_ERROR(TSDB_CODE_INVALID_CFG,                  "Invalid config option")
TAOS_DEFINE_ERROR(TSDB_CODE_INVALID_OPTION,               "Invalid option")
TAOS_DEFINE_ERROR(TSDB_CODE_INVALID_JSON_FORMAT,          "Invalid json format")
TAOS_DEFINE_ERROR(TSDB_CODE_INVALID_VERSION_NUMBER,       "Invalid version number")
TAOS_DEFINE_ERROR(TSDB_CODE_INVALID_VERSION_STRING,       "Invalid version string")
TAOS_DEFINE_ERROR(TSDB_CODE_VERSION_NOT_COMPATIBLE,       "Version not compatible")
TAOS_DEFINE_ERROR(TSDB_CODE_MEMORY_CORRUPTED,             "Memory corrupted")
TAOS_DEFINE_ERROR(TSDB_CODE_FILE_CORRUPTED,               "Data file corrupted")
TAOS_DEFINE_ERROR(TSDB_CODE_CHECKSUM_ERROR,               "Checksum error")
TAOS_DEFINE_ERROR(TSDB_CODE_COMPRESS_ERROR,               "Failed to compress msg")
TAOS_DEFINE_ERROR(TSDB_CODE_OPS_NOT_SUPPORT,              "Operation not supported")
TAOS_DEFINE_ERROR(TSDB_CODE_MSG_NOT_PROCESSED,            "Message not processed")
TAOS_DEFINE_ERROR(TSDB_CODE_CFG_NOT_FOUND,                "Config not found")
TAOS_DEFINE_ERROR(TSDB_CODE_REPEAT_INIT,                  "Repeat initialization")
TAOS_DEFINE_ERROR(TSDB_CODE_DUP_KEY,                      "Cannot add duplicate keys to hash")
TAOS_DEFINE_ERROR(TSDB_CODE_NEED_RETRY,                   "Retry needed")
TAOS_DEFINE_ERROR(TSDB_CODE_OUT_OF_RPC_MEMORY_QUEUE,      "Out of memory in rpc queue")
TAOS_DEFINE_ERROR(TSDB_CODE_INVALID_TIMESTAMP,            "Invalid timestamp format")
TAOS_DEFINE_ERROR(TSDB_CODE_MSG_DECODE_ERROR,             "Msg decode error")

TAOS_DEFINE_ERROR(TSDB_CODE_REF_NO_MEMORY,                "Ref out of memory")
TAOS_DEFINE_ERROR(TSDB_CODE_REF_FULL,                     "too many Ref Objs")
TAOS_DEFINE_ERROR(TSDB_CODE_REF_ID_REMOVED,               "Ref ID is removed")
TAOS_DEFINE_ERROR(TSDB_CODE_REF_INVALID_ID,               "Invalid Ref ID")
TAOS_DEFINE_ERROR(TSDB_CODE_REF_ALREADY_EXIST,            "Ref is already there")
TAOS_DEFINE_ERROR(TSDB_CODE_REF_NOT_EXIST,                "Ref is not there")

// rpc
TAOS_DEFINE_ERROR(TSDB_CODE_RPC_REDIRECT,                 "Redirect")
TAOS_DEFINE_ERROR(TSDB_CODE_RPC_AUTH_FAILURE,             "Authentication failure")
TAOS_DEFINE_ERROR(TSDB_CODE_RPC_NETWORK_UNAVAIL,          "Unable to establish connection")
TAOS_DEFINE_ERROR(TSDB_CODE_RPC_FQDN_ERROR,               "Unable to resolve FQDN")
TAOS_DEFINE_ERROR(TSDB_CODE_RPC_PORT_EADDRINUSE,          "Port already in use")

//client
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_OPERATION,        "Invalid operation")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_QHANDLE,          "Invalid qhandle")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_TIME_STAMP,       "Invalid combination of client/service time")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_VALUE,            "Invalid value in client")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_VERSION,          "Invalid client version")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_IE,               "Invalid client ie")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_FQDN,             "Invalid host name")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_USER_LENGTH,      "Invalid user name")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_PASS_LENGTH,      "Invalid password")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_DB_LENGTH,        "Database name too long")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_TABLE_ID_LENGTH,  "Table name too long")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_CONNECTION,       "Invalid connection")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_OUT_OF_MEMORY,            "System out of memory")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_NO_DISKSPACE,             "System out of disk space")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_QUERY_CACHE_ERASED,       "Query cache erased")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_QUERY_CANCELLED,          "Query terminated")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_SORTED_RES_TOO_MANY,      "Result set too large to be sorted")      // too many result for ordered super table projection query
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_APP_ERROR,                "Application error")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_ACTION_IN_PROGRESS,       "Action in progress")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_DISCONNECTED,             "Disconnected from service")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_NO_WRITE_AUTH,            "No write permission")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_CONN_KILLED,              "Connection killed")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_SQL_SYNTAX_ERROR,         "Syntax error in SQL")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_DB_NOT_SELECTED,          "Database not specified or available")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_TABLE_NAME,       "Table does not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_EXCEED_SQL_LIMIT,         "SQL statement too long, check maxSQLLength config")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_FILE_EMPTY,               "File is empty")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_LINE_SYNTAX_ERROR,        "Syntax error in Line")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_NO_META_CACHED,           "No table meta cached")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_DUP_COL_NAMES,            "duplicated column names")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_TAG_LENGTH,       "Invalid tag length")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_COLUMN_LENGTH,    "Invalid column length")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_DUP_TAG_NAMES,            "duplicated tag names")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_JSON,             "Invalid JSON format")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_JSON_TYPE,        "Invalid JSON data type")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_VALUE_OUT_OF_RANGE,       "Value out of range")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_INVALID_INPUT,            "Invalid tsc input")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_STMT_API_ERROR,           "Stmt API usage error")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_STMT_TBNAME_ERROR,        "Stmt table name not set")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_STMT_CLAUSE_ERROR,        "not supported stmt clause")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_QUERY_KILLED,             "Query killed")
TAOS_DEFINE_ERROR(TSDB_CODE_TSC_NO_EXEC_NODE,             "No available execution node")

// mnode-common
TAOS_DEFINE_ERROR(TSDB_CODE_MND_APP_ERROR,                "Mnode internal error")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_NOT_READY,                "Mnode not ready")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_NO_RIGHTS,                "Insufficient privilege for operation")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_USER_DISABLED,            "User is disabled")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_CONNECTION,       "Invalid message connection")

// mnode-show
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_SHOWOBJ,          "Data expired")

// mnode-profile
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_QUERY_ID,         "Invalid query id")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_STREAM_ID,        "Invalid stream id")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_CONN_ID,          "Invalid connection id")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_MNODE_IS_RUNNING,         "mnode is alreay running")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_FAILED_TO_CONFIG_SYNC,    "failed to config sync")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_FAILED_TO_START_SYNC,     "failed to start sync")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_FAILED_TO_CREATE_DIR,     "failed to create mnode dir")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_FAILED_TO_INIT_STEP,      "failed to init components")

// mnode-sdb
TAOS_DEFINE_ERROR(TSDB_CODE_SDB_APP_ERROR,                "Unexpected generic error in sdb")
TAOS_DEFINE_ERROR(TSDB_CODE_SDB_OBJ_ALREADY_THERE,        "Object already there")
TAOS_DEFINE_ERROR(TSDB_CODE_SDB_OBJ_NOT_THERE,            "Object not there")
TAOS_DEFINE_ERROR(TSDB_CODE_SDB_OBJ_CREATING,             "Object is creating")
TAOS_DEFINE_ERROR(TSDB_CODE_SDB_OBJ_DROPPING,             "Object is dropping")
TAOS_DEFINE_ERROR(TSDB_CODE_SDB_INVALID_TABLE_TYPE,       "Invalid table type")
TAOS_DEFINE_ERROR(TSDB_CODE_SDB_INVALID_KEY_TYPE,         "Invalid key type")
TAOS_DEFINE_ERROR(TSDB_CODE_SDB_INVALID_ACTION_TYPE,      "Invalid action type")
TAOS_DEFINE_ERROR(TSDB_CODE_SDB_INVALID_STATUS_TYPE,      "Invalid status type")
TAOS_DEFINE_ERROR(TSDB_CODE_SDB_INVALID_DATA_VER,         "Invalid raw data version")
TAOS_DEFINE_ERROR(TSDB_CODE_SDB_INVALID_DATA_LEN,         "Invalid raw data len")
TAOS_DEFINE_ERROR(TSDB_CODE_SDB_INVALID_DATA_CONTENT,     "Invalid raw data content")
TAOS_DEFINE_ERROR(TSDB_CODE_SDB_INVALID_WAl_VER,          "Invalid wal version")

// mnode-dnode
TAOS_DEFINE_ERROR(TSDB_CODE_MND_DNODE_ALREADY_EXIST,      "Dnode already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_DNODE_NOT_EXIST,          "Dnode does not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TOO_MANY_DNODES,          "Too many dnodes")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_NO_ENOUGH_DNODES,         "Out of dnodes")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_CLUSTER_CFG,      "Cluster cfg inconsistent")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_CLUSTER_ID,       "Cluster id not match")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_DNODE_CFG,        "Invalid dnode cfg")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_DNODE_EP,         "Invalid dnode end point")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_DNODE_ID,         "Invalid dnode id")

// mnode-node
TAOS_DEFINE_ERROR(TSDB_CODE_MND_MNODE_ALREADY_EXIST,      "Mnode already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_MNODE_NOT_EXIST,          "Mnode not there")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_QNODE_ALREADY_EXIST,      "Qnode already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_QNODE_NOT_EXIST,          "Qnode not there")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_SNODE_ALREADY_EXIST,      "Snode already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_SNODE_NOT_EXIST,          "Snode not there")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_BNODE_ALREADY_EXIST,      "Bnode already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_BNODE_NOT_EXIST,          "Bnode not there")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TOO_FEW_MNODES,           "The replica of mnode cannot less than 1")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TOO_MANY_MNODES,          "The replica of mnode cannot exceed 3")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_CANT_DROP_LEADER,         "Cannot drop mnode which is leader")

// mnode-acct
TAOS_DEFINE_ERROR(TSDB_CODE_MND_ACCT_ALREADY_EXIST,       "Account already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_ACCT_NOT_EXIST,           "Invalid account")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TOO_MANY_ACCTS,           "Too many accounts")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_ACCT_OPTION,      "Invalid account options")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_ACCT_EXPIRED,             "Account authorization has expired")

// mnode-user
TAOS_DEFINE_ERROR(TSDB_CODE_MND_USER_ALREADY_EXIST,       "User already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_USER_NOT_EXIST,           "Invalid user")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TOO_MANY_USERS,           "Too many users")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_USER_FORMAT,      "Invalid user format")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_PASS_FORMAT,      "Invalid password format")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_NO_USER_FROM_CONN,        "Can not get user from conn")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_ALTER_OPER,       "Invalid alter operation")

// mnode-db
TAOS_DEFINE_ERROR(TSDB_CODE_MND_DB_ALREADY_EXIST,         "Database already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_DB_NOT_EXIST,             "Database not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TOO_MANY_DATABASES,       "Too many databases for account")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_DB_NOT_SELECTED,          "Database not specified or available")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_DB,               "Invalid database name")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_DB_OPTION,        "Invalid database options")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_DB_ACCT,          "Invalid database account")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_DB_OPTION_UNCHANGED,      "Database options not changed")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_DB_INDEX_NOT_EXIST,       "Index not exist")

// mnode-vgroup
TAOS_DEFINE_ERROR(TSDB_CODE_MND_VGROUP_ALREADY_IN_DNODE,  "Vgroup already in dnode")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_VGROUP_NOT_IN_DNODE,      "Vgroup not in dnode")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_VGROUP_NOT_EXIST,         "Vgroup does not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_VGROUP_UN_CHANGED,        "Vgroup distribution has not changed")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_HAS_OFFLINE_DNODE,        "Offline dnode exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_REPLICA,          "Invalid vgroup replica")

// mnode-stable
TAOS_DEFINE_ERROR(TSDB_CODE_MND_STB_ALREADY_EXIST,        "STable already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_STB_NOT_EXIST,            "STable not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_NAME_CONFLICT_WITH_TOPIC, "STable confilct with topic")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TOO_MANY_STBS,            "Too many stables")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_STB,              "Invalid stable name")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_STB_OPTION,       "Invalid stable options")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_STB_ALTER_OPTION, "Invalid stable alter options")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_STB_OPTION_UNCHNAGED,     "STable option unchanged")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_ROW_BYTES,        "Invalid row bytes")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TOO_MANY_TAGS,            "Too many tags")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TAG_ALREADY_EXIST,        "Tag already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TAG_NOT_EXIST,            "Tag does not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TOO_MANY_COLUMNS,         "Too many columns")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_COLUMN_ALREADY_EXIST,     "Column already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_COLUMN_NOT_EXIST,         "Column does not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_FIELD_CONFLICT_WITH_TOPIC,"Field used by topic")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_SINGLE_STB_MODE_DB,       "Database is single stable mode")

// mnode-infoSchema
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_SYS_TABLENAME,    "Invalid system table name")

// mnode-func
TAOS_DEFINE_ERROR(TSDB_CODE_MND_FUNC_ALREADY_EXIST,       "Func already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_FUNC_NOT_EXIST,           "Func not exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_FUNC,             "Invalid func")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_FUNC_NAME,        "Invalid func name")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_FUNC_COMMENT,     "Invalid func comment")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_FUNC_CODE,        "Invalid func code")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_FUNC_BUFSIZE,     "Invalid func bufSize")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_FUNC_RETRIEVE,    "Invalid func retrieve msg")

// mnode-trans
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TRANS_ALREADY_EXIST,      "Transaction already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TRANS_NOT_EXIST,          "Transaction not exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TRANS_INVALID_STAGE,      "Invalid stage to kill")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TRANS_CONFLICT,           "Conflict transaction not completed")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TRANS_UNKNOW_ERROR,       "Unknown transaction error")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TRANS_CLOG_IS_NULL,       "Transaction commitlog is null")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TRANS_NETWORK_UNAVAILL,   "Unable to establish connection While execute transaction")

// mnode-mq
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TOPIC_ALREADY_EXIST,      "Topic already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TOPIC_NOT_EXIST,          "Topic not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TOO_MANY_TOPICS,          "Too many Topics")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_TOPIC,            "Invalid topic")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_TOPIC_QUERY,      "Topic with invalid query")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_TOPIC_OPTION,     "Topic with invalid option")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_CONSUMER_NOT_EXIST,       "Consumer not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TOPIC_OPTION_UNCHNAGED,   "Consumer unchanged")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_SUBSCRIBE_NOT_EXIST,      "Subcribe not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_OFFSET_NOT_EXIST,         "Offset not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_CONSUMER_NOT_READY,       "Consumer not ready")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_TOPIC_SUBSCRIBED,         "Topic subscribed cannot be dropped")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_CGROUP_USED,              "Consumer group being used by some consumer")

// mnode-stream
TAOS_DEFINE_ERROR(TSDB_CODE_MND_STREAM_ALREADY_EXIST,     "Stream already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_STREAM_NOT_EXIST,         "Stream not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_STREAM_OPTION,    "Invalid stream option")

// mnode-sma
TAOS_DEFINE_ERROR(TSDB_CODE_MND_SMA_ALREADY_EXIST,        "SMA already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_SMA_NOT_EXIST,            "SMA does not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_MND_INVALID_SMA_OPTION,       "Invalid sma option")

// dnode
TAOS_DEFINE_ERROR(TSDB_CODE_NODE_REDIRECT,                "Node need redirect")
TAOS_DEFINE_ERROR(TSDB_CODE_NODE_OFFLINE,                 "Node is offline")
TAOS_DEFINE_ERROR(TSDB_CODE_NODE_ALREADY_DEPLOYED,        "Node already deployed")
TAOS_DEFINE_ERROR(TSDB_CODE_NODE_NOT_DEPLOYED,            "Node not deployed")

// vnode
TAOS_DEFINE_ERROR(TSDB_CODE_VND_ACTION_IN_PROGRESS,       "Action in progress")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_MSG_NOT_PROCESSED,        "Message not processed")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_ACTION_NEED_REPROCESSED,  "Action need to be reprocessed")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_INVALID_VGROUP_ID,        "Invalid Vgroup ID")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_INIT_FAILED,              "Vnode initialization failed")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_NO_DISKSPACE,             "System out of disk space")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_NO_DISK_PERMISSIONS,      "No write permission for disk files")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_NO_SUCH_FILE_OR_DIR,      "Missing data file")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_OUT_OF_MEMORY,            "Out of memory")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_APP_ERROR,                "Unexpected generic error in vnode")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_INVALID_CFG_FILE,         "Invalid config file")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_INVALID_TERM_FILE,        "Invalid term file")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_IS_FLOWCTRL,              "Database memory is full")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_IS_DROPPING,              "Database is dropping")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_IS_UPDATING,              "Database is updating")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_IS_CLOSING,               "Database is closing")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_NOT_SYNCED,               "Database suspended")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_NO_WRITE_AUTH,            "Database write operation denied")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_IS_SYNCING,               "Database is syncing")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_INVALID_TSDB_STATE,       "Invalid tsdb state")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_TB_NOT_EXIST,             "Table not exists")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_SMA_NOT_EXIST,            "SMA not exists")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_HASH_MISMATCH,            "Hash value mismatch")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_TABLE_NOT_EXIST,          "Table does not exists")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_INVALID_TABLE_ACTION,     "Invalid table action")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_COL_ALREADY_EXISTS,       "Table column already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_TABLE_COL_NOT_EXISTS,     "Table column not exists")
TAOS_DEFINE_ERROR(TSDB_CODE_VND_READ_END,                 "Read end")


// tsdb
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_INVALID_TABLE_ID,         "Invalid table ID")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_INVALID_TABLE_TYPE,       "Invalid table type")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_IVD_TB_SCHEMA_VERSION,    "Invalid table schema version")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_TABLE_ALREADY_EXIST,      "Table already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_TABLE_NOT_EXIST,          "Table not exists")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_STB_ALREADY_EXIST,        "Stable already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_STB_NOT_EXIST,            "Stable not exists")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_INVALID_CONFIG,           "Invalid configuration")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_INIT_FAILED,              "Tsdb init failed")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_NO_DISKSPACE,             "No diskspace for tsdb")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_NO_DISK_PERMISSIONS,      "No permission for disk files")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_FILE_CORRUPTED,           "Data file(s) corrupted")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_OUT_OF_MEMORY,            "Out of memory")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_TAG_VER_OUT_OF_DATE,      "Tag too old")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_TIMESTAMP_OUT_OF_RANGE,   "Timestamp data out of range")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_SUBMIT_MSG_MSSED_UP,      "Submit message is messed up")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_INVALID_ACTION,           "Invalid operation")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_INVALID_CREATE_TB_MSG,    "Invalid creation of table")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_NO_TABLE_DATA_IN_MEM,     "No table data in memory skiplist")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_FILE_ALREADY_EXISTS,      "File already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_TABLE_RECONFIGURE,        "Need to reconfigure table")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_IVD_CREATE_TABLE_INFO,    "Invalid information to create table")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_NO_AVAIL_DISK,            "No available disk")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_MESSED_MSG,               "TSDB messed message")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_IVLD_TAG_VAL,             "TSDB invalid tag value")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_NO_CACHE_LAST_ROW,        "TSDB no cache last row data")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_TABLE_RECREATED,          "Table re-created")
TAOS_DEFINE_ERROR(TSDB_CODE_TDB_TDB_ENV_OPEN_ERROR,       "TDB env open error")


// query
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_INVALID_QHANDLE,          "Invalid handle")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_INVALID_MSG,              "Invalid message")    // failed to validate the sql expression msg by vnode
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_NO_DISKSPACE,             "No diskspace for query")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_OUT_OF_MEMORY,            "System out of memory")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_APP_ERROR,                "Unexpected generic error in query")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_DUP_JOIN_KEY,             "Duplicated join key")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_EXCEED_TAGS_LIMIT,        "Tag conditon too many")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_NOT_READY,                "Query not ready")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_HAS_RSP,                  "Query should response")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_IN_EXEC,                  "Multiple retrieval of this query")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_TOO_MANY_TIMEWINDOW,      "Too many time window in query")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_NOT_ENOUGH_BUFFER,        "Query buffer limit has reached")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_INCONSISTAN,              "File inconsistance in replica")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_INVALID_TIME_CONDITION,   "One valid time range condition expected")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_SYS_ERROR,                "System error")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_INVALID_INPUT,            "invalid input")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_SCH_NOT_EXIST,            "Scheduler not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_TASK_NOT_EXIST,           "Task not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_TASK_ALREADY_EXIST,       "Task already exist")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_TASK_CTX_NOT_EXIST,       "Task context not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_TASK_CANCELLED,           "Task cancelled")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_TASK_DROPPED,             "Task dropped")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_TASK_CANCELLING,          "Task cancelling")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_TASK_DROPPING,            "Task dropping")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_DUPLICATTED_OPERATION,    "Duplicatted operation")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_TASK_MSG_ERROR,           "Task message error")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_JOB_FREED,                "Job already freed")
TAOS_DEFINE_ERROR(TSDB_CODE_QRY_TASK_STATUS_ERROR,        "Task status error")

// grant
TAOS_DEFINE_ERROR(TSDB_CODE_GRANT_EXPIRED,                "License expired")
TAOS_DEFINE_ERROR(TSDB_CODE_GRANT_DNODE_LIMITED,          "DNode creation limited by licence")
TAOS_DEFINE_ERROR(TSDB_CODE_GRANT_ACCT_LIMITED,           "Account creation limited by license")
TAOS_DEFINE_ERROR(TSDB_CODE_GRANT_TIMESERIES_LIMITED,     "Table creation limited by license")
TAOS_DEFINE_ERROR(TSDB_CODE_GRANT_DB_LIMITED,             "DB creation limited by license")
TAOS_DEFINE_ERROR(TSDB_CODE_GRANT_USER_LIMITED,           "User creation limited by license")
TAOS_DEFINE_ERROR(TSDB_CODE_GRANT_CONN_LIMITED,           "Conn creation limited by license")
TAOS_DEFINE_ERROR(TSDB_CODE_GRANT_STREAM_LIMITED,         "Stream creation limited by license")
TAOS_DEFINE_ERROR(TSDB_CODE_GRANT_SPEED_LIMITED,          "Write speed limited by license")
TAOS_DEFINE_ERROR(TSDB_CODE_GRANT_STORAGE_LIMITED,        "Storage capacity limited by license")
TAOS_DEFINE_ERROR(TSDB_CODE_GRANT_QUERYTIME_LIMITED,      "Query time limited by license")
TAOS_DEFINE_ERROR(TSDB_CODE_GRANT_CPU_LIMITED,            "CPU cores limited by license")

// sync
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_INVALID_CONFIG,           "Invalid Sync Configuration")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_NOT_ENABLED,              "Sync module not enabled")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_INVALID_VERSION,          "Invalid Sync version")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_CONFIRM_EXPIRED,          "Sync confirm expired")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_TOO_MANY_FWDINFO,         "Too many sync fwd infos")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_MISMATCHED_PROTOCOL,      "Mismatched protocol")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_MISMATCHED_CLUSTERID,     "Mismatched clusterId")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_MISMATCHED_SIGNATURE,     "Mismatched signature")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_INVALID_CHECKSUM,         "Invalid msg checksum")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_INVALID_MSGLEN,           "Invalid msg length")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_INVALID_MSGTYPE,          "Invalid msg type")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_IS_LEADER,                "Sync is leader")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_NOT_LEADER,               "Sync not leader")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_ONE_REPLICA,              "Sync one replica")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_NOT_IN_NEW_CONFIG,        "Sync not in new config")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_NEW_CONFIG_ERROR,         "Sync new config error")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_RECONFIG_NOT_READY,       "Sync not ready for reconfig")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_PROPOSE_NOT_READY,        "Sync not ready for propose")
TAOS_DEFINE_ERROR(TSDB_CODE_SYN_INTERNAL_ERROR,           "Sync internal error")

// wal
TAOS_DEFINE_ERROR(TSDB_CODE_WAL_APP_ERROR,                "Unexpected generic error in wal")
TAOS_DEFINE_ERROR(TSDB_CODE_WAL_FILE_CORRUPTED,           "WAL file is corrupted")
TAOS_DEFINE_ERROR(TSDB_CODE_WAL_SIZE_LIMIT,               "WAL size exceeds limit")
TAOS_DEFINE_ERROR(TSDB_CODE_WAL_INVALID_VER,              "WAL use invalid version")
TAOS_DEFINE_ERROR(TSDB_CODE_WAL_LOG_NOT_EXIST,            "WAL log not exist")

// tfs
TAOS_DEFINE_ERROR(TSDB_CODE_FS_APP_ERROR,                 "tfs out of memory")
TAOS_DEFINE_ERROR(TSDB_CODE_FS_INVLD_CFG,                 "tfs invalid mount config")
TAOS_DEFINE_ERROR(TSDB_CODE_FS_TOO_MANY_MOUNT,            "tfs too many mount")
TAOS_DEFINE_ERROR(TSDB_CODE_FS_DUP_PRIMARY,               "tfs duplicate primary mount")
TAOS_DEFINE_ERROR(TSDB_CODE_FS_NO_PRIMARY_DISK,           "tfs no primary mount")
TAOS_DEFINE_ERROR(TSDB_CODE_FS_NO_MOUNT_AT_TIER,          "tfs no mount at tier")
TAOS_DEFINE_ERROR(TSDB_CODE_FS_FILE_ALREADY_EXISTS,       "tfs file already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_FS_INVLD_LEVEL,               "tfs invalid level")
TAOS_DEFINE_ERROR(TSDB_CODE_FS_NO_VALID_DISK,             "tfs no valid disk")

// catalog
TAOS_DEFINE_ERROR(TSDB_CODE_CTG_INTERNAL_ERROR,           "catalog internal error")
TAOS_DEFINE_ERROR(TSDB_CODE_CTG_INVALID_INPUT,            "invalid catalog input parameters")
TAOS_DEFINE_ERROR(TSDB_CODE_CTG_NOT_READY,                "catalog is not ready")
TAOS_DEFINE_ERROR(TSDB_CODE_CTG_MEM_ERROR,                "catalog memory error")
TAOS_DEFINE_ERROR(TSDB_CODE_CTG_SYS_ERROR,                "catalog system error")
TAOS_DEFINE_ERROR(TSDB_CODE_CTG_DB_DROPPED,               "Database is dropped")
TAOS_DEFINE_ERROR(TSDB_CODE_CTG_OUT_OF_SERVICE,           "catalog is out of service")
TAOS_DEFINE_ERROR(TSDB_CODE_CTG_VG_META_MISMATCH,         "table meta and vgroup mismatch")

//scheduler
TAOS_DEFINE_ERROR(TSDB_CODE_SCH_STATUS_ERROR,             "scheduler status error")
TAOS_DEFINE_ERROR(TSDB_CODE_SCH_INTERNAL_ERROR,           "scheduler internal error")
TAOS_DEFINE_ERROR(TSDB_CODE_SCH_TIMEOUT_ERROR,            "Task timeout")
TAOS_DEFINE_ERROR(TSDB_CODE_SCH_JOB_IS_DROPPING,          "Job is dropping")
TAOS_DEFINE_ERROR(TSDB_CODE_QW_MSG_ERROR,                 "Invalid msg order")

// parser
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_PERMISSION_DENIED,         "Permission denied")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INTERNAL_ERROR,            "Parser internal error")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_SYNTAX_ERROR,              "syntax error near")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INCOMPLETE_SQL,            "Incomplete SQL statement")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_COLUMN,            "Invalid column name")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_TABLE_NOT_EXIST,           "Table does not exist")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_AMBIGUOUS_COLUMN,          "Column ambiguously defined")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_WRONG_VALUE_TYPE,          "Invalid value type")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_ILLEGAL_USE_AGG_FUNCTION,  "There mustn't be aggregation")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_WRONG_NUMBER_OF_SELECT,    "ORDER BY item must be the number of a SELECT-list expression")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_GROUPBY_LACK_EXPRESSION,   "Not a GROUP BY expression")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_NOT_SELECTED_EXPRESSION,   "Not SELECTed expression")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_NOT_SINGLE_GROUP,          "Not a single-group group function")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_TAGS_NOT_MATCHED,          "Tags number not matched")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_TAG_NAME,          "Invalid tag name")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_NAME_OR_PASSWD_TOO_LONG,   "Name or password too long")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_PASSWD_EMPTY,              "Password can not be empty")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_PORT,              "Port should be an integer that is less than 65535 and greater than 0")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_ENDPOINT,          "Endpoint should be in the format of 'fqdn:port'")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_EXPRIE_STATEMENT,          "This statement is no longer supported")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INTER_VALUE_TOO_SMALL,     "Interval too small")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_DB_NOT_SPECIFIED,          "Database not specified")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_IDENTIFIER_NAME,   "Invalid identifier name")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_CORRESPONDING_STABLE_ERR,  "Corresponding super table not in this db")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_RANGE_OPTION,      "Invalid option")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_STR_OPTION,        "Invalid option")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_ENUM_OPTION,       "Invalid option")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_KEEP_NUM,          "Invalid number of keep options")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_KEEP_ORDER,        "Invalid keep value, should be keep0 <= keep1 <= keep2")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_KEEP_VALUE,        "Invalid option keep")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_COMMENT_OPTION,    "Invalid option comment")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_F_RANGE_OPTION,    "Invalid option")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_ROLLUP_OPTION,     "Invalid option rollup: only one function is allowed")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_RETENTIONS_OPTION, "Invalid option retentions")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_GROUPBY_WINDOW_COEXIST,    "GROUP BY and WINDOW-clause can't be used together")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_OPTION_UNIT,       "Invalid option unit: only m, h, d allowed")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_KEEP_UNIT,         "Invalid option keep unit: only m, h, d allowed")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_AGG_FUNC_NESTING,          "Aggregate functions do not support nesting")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_STATE_WIN_TYPE,    "Only support STATE_WINDOW on integer/bool/varchar column")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_STATE_WIN_COL,     "Not support STATE_WINDOW on tag column")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_STATE_WIN_TABLE,   "STATE_WINDOW not support for super table query")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INTER_SESSION_GAP,         "SESSION gap should be fixed time window, and greater than 0")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INTER_SESSION_COL,         "Only support SESSION on primary timestamp column")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INTER_OFFSET_NEGATIVE,     "Interval offset cannot be negative")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INTER_OFFSET_UNIT,         "Cannot use 'year' as offset when interval is 'month'")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INTER_OFFSET_TOO_BIG,      "Interval offset should be shorter than interval")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INTER_SLIDING_UNIT,        "Does not support sliding when interval is natural month/year")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INTER_SLIDING_TOO_BIG,     "sliding value no larger than the interval value")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INTER_SLIDING_TOO_SMALL,   "sliding value can not less than 1% of interval value")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_ONLY_ONE_JSON_TAG,         "Only one tag if there is a json tag")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INCORRECT_NUM_OF_COL,      "Query block has incorrect number of result columns")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INCORRECT_TIMESTAMP_VAL,   "Incorrect TIMESTAMP value")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_DAYS_VALUE,        "Invalid days value, should be keep2 >= keep1 >= keep0 >= days")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_OFFSET_LESS_ZERO,          "soffset/offset can not be less than 0")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_SLIMIT_LEAK_PARTITION_BY,  "slimit/soffset only available for PARTITION BY query")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_TOPIC_QUERY,        "Invalid topic query")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_DROP_STABLE,        "Cannot drop super table in batch")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_FILL_TIME_RANGE,    "Start(end) time of query range required or time range too large")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_DUPLICATED_COLUMN,          "Duplicated column names")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_TAGS_LENGTH,        "Tags length exceeds max length")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_ROW_LENGTH,         "Row length exceeds max length")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_COLUMNS_NUM,        "Illegal number of columns")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_TOO_MANY_COLUMNS,           "Too many columns")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_FIRST_COLUMN,       "First column must be timestamp")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_VAR_COLUMN_LEN,     "Invalid binary/nchar column length")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_TAGS_NUM,           "Invalid number of tag columns")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_INTERNAL_PK,        "Invalid _c0 or _rowts expression")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_TIMELINE_FUNC,      "Invalid timeline function")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_PASSWD,             "Invalid password")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_ALTER_TABLE,        "Invalid alter table statement")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_CANNOT_DROP_PRIMARY_KEY,    "Primary timestamp column cannot be dropped")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_MODIFY_COL,         "Only binary/nchar column length could be modified")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_TBNAME,             "Invalid tbname pseudo column")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_FUNCTION_NAME,      "Invalid function name")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_COMMENT_TOO_LONG,           "Comment too long")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_NOT_ALLOWED_FUNC,           "Some functions are allowed only in the SELECT list of a query. "
                                                            "And, cannot be mixed with other non scalar functions or columns.")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_NOT_ALLOWED_WIN_QUERY,      "Window query not supported, since the result of subquery not include valid timestamp column")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_DROP_COL,           "No columns can be dropped")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_COL_JSON,           "Only tag can be json type")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_VALUE_TOO_LONG,             "Value too long for column/tag")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_DELETE_WHERE,       "The DELETE statement must have a definite time window range")
TAOS_DEFINE_ERROR(TSDB_CODE_PAR_INVALID_REDISTRIBUTE_VG,    "The REDISTRIBUTE VGROUP statement only support 1 to 3 dnodes")

//planner
TAOS_DEFINE_ERROR(TSDB_CODE_PLAN_INTERNAL_ERROR,            "Planner internal error")

//udf
TAOS_DEFINE_ERROR(TSDB_CODE_UDF_STOPPING,                   "udf is stopping")
TAOS_DEFINE_ERROR(TSDB_CODE_UDF_PIPE_READ_ERR,              "udf pipe read error")
TAOS_DEFINE_ERROR(TSDB_CODE_UDF_PIPE_CONNECT_ERR,           "udf pipe connect error")
TAOS_DEFINE_ERROR(TSDB_CODE_UDF_PIPE_NO_PIPE,               "udf no pipe")
TAOS_DEFINE_ERROR(TSDB_CODE_UDF_LOAD_UDF_FAILURE,           "udf load failure")
TAOS_DEFINE_ERROR(TSDB_CODE_UDF_INVALID_STATE,              "udf invalid state")
TAOS_DEFINE_ERROR(TSDB_CODE_UDF_INVALID_INPUT,              "udf invalid function input")
TAOS_DEFINE_ERROR(TSDB_CODE_UDF_NO_FUNC_HANDLE,             "udf no function handle")
TAOS_DEFINE_ERROR(TSDB_CODE_UDF_INVALID_BUFSIZE,            "udf invalid bufsize")
TAOS_DEFINE_ERROR(TSDB_CODE_UDF_INVALID_OUTPUT_TYPE,        "udf invalid output type")

//schemaless
TAOS_DEFINE_ERROR(TSDB_CODE_SML_INVALID_PROTOCOL_TYPE,      "Invalid line protocol type")
TAOS_DEFINE_ERROR(TSDB_CODE_SML_INVALID_PRECISION_TYPE,     "Invalid timestamp precision type")
TAOS_DEFINE_ERROR(TSDB_CODE_SML_INVALID_DATA,               "Invalid data type")
TAOS_DEFINE_ERROR(TSDB_CODE_SML_INVALID_DB_CONF,            "Invalid schemaless db config")

//tsma
TAOS_DEFINE_ERROR(TSDB_CODE_TSMA_ALREADY_EXIST,             "Tsma already exists")
TAOS_DEFINE_ERROR(TSDB_CODE_TSMA_NO_INDEX_IN_META,          "No tsma index in meta")
TAOS_DEFINE_ERROR(TSDB_CODE_TSMA_INVALID_ENV,               "Invalid tsma env")
TAOS_DEFINE_ERROR(TSDB_CODE_TSMA_INVALID_STAT,              "Invalid tsma state")
TAOS_DEFINE_ERROR(TSDB_CODE_TSMA_INVALID_PTR,               "Invalid tsma pointer")
TAOS_DEFINE_ERROR(TSDB_CODE_TSMA_INVALID_PARA,              "Invalid tsma parameters")
TAOS_DEFINE_ERROR(TSDB_CODE_TSMA_NO_INDEX_IN_CACHE,         "No tsma index in cache")


//rsma
TAOS_DEFINE_ERROR(TSDB_CODE_RSMA_INVALID_ENV,               "Invalid rsma env")
TAOS_DEFINE_ERROR(TSDB_CODE_RSMA_INVALID_STAT,              "Invalid rsma state")

//tq
TAOS_DEFINE_ERROR(TSDB_CODE_TQ_NO_COMMITTED_OFFSET,         "No committed offset")


TAOS_DEFINE_ERROR(TSDB_CODE_INDEX_REBUILDING,               "Index is rebuilding")

TAOS_DEFINE_ERROR(TSDB_CODE_TMQ_INVALID_MSG,                "Invalid message")

#ifdef TAOS_ERROR_C
};
#endif

static int32_t taosCompareTaosError(const void* a, const void* b) {
  const STaosError* x = (const STaosError*)a;
  const STaosError* y = (const STaosError*)b;
  if (x->val < y->val) {
    return -1;
  }
  if (x->val > y->val) {
    return 1;
  }
  return 0;
}

static TdThreadOnce tsErrorInit = PTHREAD_ONCE_INIT;

static void tsSortError(void) {
  qsort(errors, sizeof(errors) / sizeof(errors[0]), sizeof(errors[0]), taosCompareTaosError);
}

const char* tstrerror(int32_t err) {
  taosThreadOnce(&tsErrorInit, tsSortError);

  // this is a system errno
  if ((err & 0x00ff0000) == 0x00ff0000) {
    return strerror(err & 0x0000ffff);
  }

  int32_t s = 0;
  int32_t e = sizeof(errors) / sizeof(errors[0]);

  while (s < e) {
    int32_t mid = (s + e) / 2;
    int32_t val = errors[mid].val;
    if (err > val) {
      s = mid + 1;
    } else if (err < val) {
      e = mid;
    } else if (err == val) {
      return errors[mid].str;
    } else {
      break;
    }
  }

  return "";
}

const char* terrstr() { return tstrerror(terrno); }
