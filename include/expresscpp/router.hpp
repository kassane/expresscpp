#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "boost/uuid/uuid.hpp"
#include "expresscpp/layer.hpp"
#include "expresscpp/request.hpp"
#include "expresscpp/response.hpp"
#include "expresscpp/route.hpp"
#include "expresscpp/types.hpp"

namespace expresscpp {

class Router {
 public:
  Router();
  Router(std::string_view router_name);

  //! @brief handler for all routes matching this path
  void Use(std::string_view path, handler_t handler);

  //! @brief registering a router to serve path and subpaths of this path
  void Use(std::string_view path, std::shared_ptr<Router> router);

  /*!
   * Proxy `Router#Use()` to add middleware to the app router.
   * See Router#use() documentation for details.
   *
   * If the _fn_ parameter is an express app, then it will be
   * mounted at the _route_ specified.
   */
  void Use(std::string_view path, handler_wn_t handler);
  void Use(handler_wn_t handler);

  Router& Put(handler_wn_t handler);
  Router& Put(std::string_view path, handler_wn_t handler);
  Router& Get(handler_wn_t handler);
  Router& Get(std::string_view path, handler_wn_t handler);
  Router& Post(handler_wn_t handler);
  Router& Post(std::string_view path, handler_wn_t handler);
  Router& Delete(handler_wn_t handler);
  Router& Delete(std::string_view path, handler_wn_t handler);
  Router& Patch(handler_wn_t handler);
  Router& Patch(std::string_view path, handler_wn_t handler);

  void RegisterPath(std::string_view registered_path, const HttpMethod method, handler_wn_t handler);

  void HandleRequest(std::shared_ptr<Request> req, std::shared_ptr<Response> res);

  void SetParentPath(const std::string& parent_path);

  //! @brief returns a router which then can use used to serve some paths
  auto GetRouter();
  auto GetRouter(std::string_view name);

  auto GetRouters() const;

  /**
   * Create a new Route for the given path.
   *
   * Each route contains a separate middleware stack and VERB handlers.
   *
   * See the Route api documentation for details on adding handlers
   * and middleware to routes.
   *
   * @param {String} registered_path
   * @return {Route}
   */
  std::shared_ptr<Route> CreateRoute(const std::string_view registered_path);

  std::string_view GetName() const;

  std::vector<std::shared_ptr<Layer>> stack() const;

  void Next(std::shared_ptr<Request> req, std::shared_ptr<Response> res, std::shared_ptr<std::string> err = nullptr);

 private:
  void Init();

  //!
  /* @brief Enable case sensitivity.
   * Disabled by default, treating “/Foo” and “/foo” as the same.
   * @ref https://expressjs.com/en/api.html#express.router
   */
  bool caseSensitive{false};

  //!
  /* @brief Preserve the req.params values from the parent router.
   * If the parent and the child have conflicting param names,
   * the child’s value take precedence.
   * @ref https://expressjs.com/en/api.html#express.router
   */
  bool mergeParams{false};

  //!
  /* @brief Enable strict routing.
   * Disabled by default, “/foo” and “/foo/” are treated the same by the router.
   * @ref https://expressjs.com/en/api.html#express.router
   */
  bool strict{false};

  std::vector<Route> routes_;

  //! @brief uuid of the router, for debugging
  boost::uuids::uuid uuid_;

  //! @brief creation date of the router, for debugging
  std::chrono::system_clock::time_point timestamp_;

  //! @brief name of the router, mostly for debugging
  std::string_view name_{"unknown"};

  std::vector<std::shared_ptr<Layer>> stack_;

  std::string parent_path_;
};

typedef std::shared_ptr<Router> RouterPtr;

}  // namespace expresscpp
