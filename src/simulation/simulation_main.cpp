#include "../include/openai/openai.hpp"

using namespace std;

int main() {

    openai::start(); // Will use the api key provided by `OPENAI_API_KEY` environment variable
    // openai::start("your_API_key", "optional_organization"); // Or you can handle it yourself

    auto& openai = openai::instance();
    auto completion = openai::_detail::CategoryChat(openai).create(R"({
        "model": "gpt-4",
        "messages": [{"role": "user","content": "Say this is a test!"}
        ],
        "temperature": 0
    })"_json); // Using user-defined (raw) string literals
    std::cout << "Response is:\n" << completion["choices"][0]["message"]["content"] << '\n'; 
}
