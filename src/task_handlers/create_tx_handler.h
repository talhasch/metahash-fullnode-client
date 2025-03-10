#ifndef __CREATE_TX_HANDLER_H__
#define __CREATE_TX_HANDLER_H__

//#include "base_handler.h"
#include "create_tx_base_handler.h"

class create_tx_handler : public create_tx_base_handler
{
public:
    create_tx_handler(http_session_ptr session): create_tx_base_handler(session) {}
    virtual ~create_tx_handler() override {}

    virtual void execute() override;

protected:
    virtual bool prepare_params() override;
};


class create_tx_handler_v2 : public create_tx_handler
{
public:
    create_tx_handler_v2(http_session_ptr session): create_tx_handler(session) {}
    virtual ~create_tx_handler_v2() override {}

protected:
    virtual bool build_request(bool create_hash = false) override;
    virtual void make_json() override;
};

#endif // __CREATE_TX_HANDLER_H__
