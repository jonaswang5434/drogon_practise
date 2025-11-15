#paragama once
#include <string>
#include <drogon/HttpRequest.h>
#include <json/json.h>

namespace myapp
{
    struct User
    {
        std::string userName;
        std::string email;
        std::string address;
    };
}

namespace drogon
{
    template <>
    inline myapp::User fromRequest(const HttpRequest &req)
    {
        auto json = req.getJsonObject();
        myapp::User user;

        if (json)
        {
            user.userName = (*json)["name"].asString();
            user.email = (*json)["email"].asString();
            user.address = (*json)["address"].asString();
        }
        return user;
    }

}