#ifndef TEXT_CONTENT
#define TEXT_CONTENT

#include <iostream>
#include <sstream>
#include <vector>

namespace util::text_content {
    using std::cout;
    using std::endl;
    using std::string;
    using std::stringstream;
    using std::vector;

    const string GITIGNORE = R"(
    build
    test
    )";

    const string README_MD = R"(
    # Project name

    This project was made using `cbt`

    ## Setup

    Discuss your setup here

    ## Code of contribution

    Discuss rules of engagement here
    )";

    const string SAMPLE_HPP = R"(
    #ifndef SAMPLE
    #define SAMPLE

    namespace sample {
        int sum(const int a, const int b);
    }

    #endif
    )";

    const string MAIN_CPP = R"(
    #include <iostream>

    #include "sample.hpp"

    int main(const int argc, char *argv[], char *envp[]) {
        std::vector<std::string> args(argv, argv + argc);
        std::map<std::string, std::string> env;

        while (*envp) {
            const std::string env_variable = std::string(*envp++);
            const int position_of_equal_to_symbol = env_variable.find("=");

            const std::string key = env_variable.substr(0, position_of_equal_to_symbol);
            const std::string value = env_variable.substr(position_of_equal_to_symbol + 1);

            env[key] = value;
        }
        
        std::cout << "args[0]: " << args[0] << std::endl;
        std::cout << "env[\"HOME\"]: " << env["HOME"] << std::endl;

        std::cout << "Sum of 2 and 3 is: " << sample::sum(2, 3) << std::endl;

        return EXIT_SUCCESS;
    }
    )";

    const string SAMPLE_CPP = R"(
    #include "sample.hpp"

    namespace sample {
        int sum(const int a, const int b) {
            return a + b;
        }
    }
    )";

    string __remove_raw_literal_indentations(const string raw_literal) {
        string line, final_string;
        stringstream stream(raw_literal);
        vector<string> lines;

        while (getline(stream, line)) {
            // cout << "Line:" << line << " -> " << line.size() << endl;
            lines.push_back(line);
        }

        lines.erase(lines.begin());
        lines.pop_back();

        for (auto& nline: lines) {
            final_string += (nline.size() > 4 ? nline.substr(4) : nline) + "\n";
        }

        return final_string;
    }

    string get_predefined_text_content(const string file_name) {
        if (file_name.compare("/.gitignore") == 0) {
            return __remove_raw_literal_indentations(GITIGNORE);
        } else if (file_name.compare("/README.md") == 0) {
            return __remove_raw_literal_indentations(README_MD);
        } else if (file_name.compare("/headers/sample.hpp") == 0) {
            return __remove_raw_literal_indentations(SAMPLE_HPP);
        } else if (file_name.compare("/src/main.cpp") == 0) {
            return __remove_raw_literal_indentations(MAIN_CPP);
        } else if (file_name.compare("/src/sample.cpp") == 0) {
            return __remove_raw_literal_indentations(SAMPLE_CPP);
        } else {
            return "";
        }
    }
}

#endif