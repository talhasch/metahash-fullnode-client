#ifndef FETCH_BALANCE_HANDLER_SYNC_H_
#define FETCH_BALANCE_HANDLER_SYNC_H_

#include "sync_handler.h"

class fetch_balance_handler_sync : public base_sync_handler, public Perform<fetch_balance_handler_sync> {
public:
    
    fetch_balance_handler_sync(http_session_ptr session): base_sync_handler(settings::server::tor, session) {
        std::stringstream ss;
        ss << __FUNCTION__;
        m_duration.set_message(ss.str());
    }
    
    virtual ~fetch_balance_handler_sync() override {}
    
    virtual bool prepare_params() override;
    
    virtual void executeImpl() override;
    
private:
    
    std::string address;
};

#endif // FETCH_BALANCE_HANDLER_SYNC_H_
