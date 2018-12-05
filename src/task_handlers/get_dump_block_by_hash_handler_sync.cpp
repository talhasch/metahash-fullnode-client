#include "get_dump_block_by_hash_handler_sync.h"

#include "../SyncSingleton.h"

#include "../generate_json.h"

#include "../sync/BlockInfo.h"
#include "../sync/BlockChainReadInterface.h"

#include "check.h"

bool get_dump_block_by_hash_handler_sync::prepare_params()
{
    BGN_TRY
    {
        CHK_PRM(m_id, "id field not found")
        
        auto params = m_reader.get_params();
        CHK_PRM(params, "params field not found")
        
        CHK_PRM(m_reader.get_value(*params, "hash", hash), "hash field not found")
        CHK_PRM(!hash.empty(), "hash is empty")

        fromByte = 0;
        toByte = std::numeric_limits<size_t>::max();
        if (m_reader.get_doc().HasMember("fromByte") && m_reader.get_doc()["fromByte"].IsInt64()) {
            fromByte = m_reader.get_doc()["fromByte"].GetInt64();
        }
        if (m_reader.get_doc().HasMember("toByte") && m_reader.get_doc()["toByte"].IsInt64()) {
            toByte = m_reader.get_doc()["toByte"].GetInt64();
        }
        
        isHex = false;
        if (m_reader.get_doc().HasMember("isHex") && m_reader.get_doc()["isHex"].IsBool()) {
            isHex = m_reader.get_doc()["isHex"].GetBool();
        }
        
        return true;
    }
    END_TRY_RET(false)
}

void get_dump_block_by_hash_handler_sync::executeImpl() {
BGN_TRY {
    CHK_PRM(syncSingleton() != nullptr, "Sync not set");
    const torrent_node_lib::Sync &sync = *syncSingleton();
    
    try {
        const torrent_node_lib::BlockHeader bh = sync.getBlockchain().getBlock(hash);
        CHECK(bh.blockNumber.has_value(), "block " + hash + " not found");
        const std::string res = sync.getBlockDump(bh, fromByte, toByte, isHex);
        
        CHECK(!res.empty(), "block " + hash + " not found");
        if (isHex) {
            genBlockDumpJson(res, false, m_writer.getDoc());
        } else {
            //return res;
        }
    } catch (const common::exception &e) {
        genErrorResponse(-32603, e, m_writer.getDoc());
    } catch (const std::exception &e) {
        genErrorResponse(-32603, e.what(), m_writer.getDoc());
    } catch (...) {
        genErrorResponse(-32603, "Unknown error", m_writer.getDoc());
    }
} END_TRY_RET();
}
