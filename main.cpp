#include "crow_all.h"
#include <memory>
#include <vector>

typedef struct {
    std::string email;
    std::string first_name;
    std::string last_name;
} user;

int main(int argc, char* argv[])
{
    crow::SimpleApp app;
    crow::mustache::set_global_base(".");
    std::vector<std::unique_ptr<user>> users;

    CROW_ROUTE(app, "/")
    ([&]() {
        crow::mustache::context ctx;
        int count = 0;
        for (const auto& u : users) {
            ctx["users"][count]["id"] = count + 1;
            ctx["users"][count]["email"] = u->email;
            ctx["users"][count]["first_name"] = u->first_name;
            ctx["users"][count]["last_name"] = u->last_name;
            count++;
        }
        auto page = crow::mustache::load("users.html");
        return page.render(ctx);
    });

    CROW_ROUTE(app, "/post").methods("POST"_method)
    ([&](const crow::request& req, crow::response& res) {
        crow::query_string params(std::string("?") + req.body);
        std::unique_ptr<user> u = std::make_unique<user>();
        u->email = params.get("email");
        u->first_name = params.get("first_name");
        u->last_name = params.get("last_name");
        users.push_back(std::move(u));
        res = crow::response(crow::FOUND);
        res.set_header("Location", "/");
        res.end();
    });

    app.port(18080).run();

    return 0;
}
