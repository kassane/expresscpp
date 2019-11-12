#pragma once

#include <functional>
#include <system_error>

#include "expresscpp/nextrouter.hpp"
#include "expresscpp/request.hpp"
#include "expresscpp/response.hpp"

namespace expresscpp {

typedef std::function<void(express_request_t req, express_response_t res)> express_handler_t;
typedef std::function<void(express_request_t req, express_response_t res, express_next_t next)> express_handler_wn_t;
typedef std::function<void(std::error_code ec, express_request_t req, express_response_t res, express_next_t next)>
    express_handler_wecn_t;
typedef std::function<void(const std::error_code)> ready_fn_cb_error_code_t;

typedef std::function<void()> ready_fn_cb_void_t;

}  // namespace expresscpp
